/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/scene.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/transform.hpp>

//  -- Library --
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

//  -- General --
#include "gen/config.hpp"
#include "gen/control.hpp"
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/graphical/camera/fly.hpp"
#include "cls/graphical/camera/orbit.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a three-dimensional scene.
         */
        Scene::Scene() :
            m_window(init_window()),
            m_cubemap(init_cubemap()),
            m_cube_box(Prop(Prop::shape::SKYBOX, {1.0, 0.0, 1.0, 1.0}, 10.0)),
            m_primary_cam(std::make_unique<camera::Orbit>(glm::vec3({INIT_CAM_POS_X, INIT_CAM_POS_Y, INIT_CAM_POS_Z}),
                                                          static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_secondary_cam(std::make_unique<camera::Fly>(glm::vec3({INIT_CAM_POS_X, INIT_CAM_POS_Y, INIT_CAM_POS_Z}),
                                                          static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_sun_pos(glm::vec3({INIT_SUN_POS_X, INIT_SUN_POS_Y, INIT_SUN_POS_Z})),
            m_sun(Prop(Prop::shape::CUBE, {1.0, 1.0, 0.0, 1.0}, SUN_SIZE))
        {
        }


        //  -- Destructors --
        /**
         *  Destruct the scene object.
         *  Terminate the glfw operations.
         */
        Scene::~Scene()
        {
            glfwTerminate();
        }


        //  -- Initialisation --
        /**
         *  Initialise the scene window handle.
         *
         *  @return The constructed scene window handle.
         */
        GLFWwindow* Scene::init_window() const
        {
            // Check that glfw can be initialised.
            if (glfwInit() == 0)
            {
                ERROR("Unable to construct graphical::Scene object.", "Glfw could not be initialised.");
            }

            // Window settings.
            glfwWindowHint(GLFW_SAMPLES, AA_SAMPLES);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // Create the window handle.
            GLFWwindow* r_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);

            // Check that the handle was successfully created.
            if (r_window == nullptr)
            {
                ERROR("Unable to construct graphical::Scene object.", "Glfw could not be initialised.");
            }

            // Make this the current window context.
            glfwMakeContextCurrent(r_window);
            glewExperimental = GL_TRUE;

            // Check that glew can be initialised.
            if (glewInit() != GLEW_OK)
            {
                ERROR("Unable to construct graphical::Window object.", "Glew could not be initialised.");
            }

            // Set the key input mode.
            glfwSetInputMode(r_window, GLFW_STICKY_KEYS, GL_TRUE);

            // Set background colour.
            glClearColor(CLEAR_COLOUR_RED, CLEAR_COLOUR_GREEN, CLEAR_COLOUR_BLUE, CLEAR_COLOUR_ALPHA);

            // Enable the depth buffer.
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            // Enable transparency.
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            return (r_window);
        }

        /**
         *  Initialise the cubemap texture.
         *
         *  @return A handle to the loaded cubemap texture.
         */
        GLuint Scene::init_cubemap() const
        {
            // Individual image names.
            std::vector<std::string> faces({"right", "left", "top", "bottom", "front", "back"});

            // Create and bind texture id.
            GLuint r_texture_id;
            glGenTextures(1, &r_texture_id);
            glBindTexture(GL_TEXTURE_CUBE_MAP, r_texture_id);

            // Load each face texture.
            int               width, height, num_channels;
            for (unsigned int i = 0; i < faces.size(); i++)
            {
                unsigned char* data = stbi_load(
                    (std::string(config::ARCTORUS_DIR) + SKYBOX_DIR + faces[i] + SKYBOX_FILE_EXT).c_str(), &width, &height,
                    &num_channels, 0);
                if (data == nullptr)
                {
                    WARN("Unable to load cubemap face.",
                         "Cubemap image: '" << (std::string(config::ARCTORUS_DIR) + SKYBOX_DIR + faces[i] + SKYBOX_FILE_EXT)
                                            << "', could not be loaded.");
                    stbi_image_free(data);
                }
                else
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                 data);
                    stbi_image_free(data);
                }
            }

            // Set texture settings.
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            return (r_texture_id);
        }



        //  == METHODS ==
        //  -- Additions --
        /**
         *  Add a render-able entity prop to the scene.
         *
         *  @param  t_mesh  Entity mesh to be added to the scene.
         *  @param  t_col   Colour to render the entity with.
         */
        void Scene::add_entity(const geom::Mesh& t_mesh, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_mesh.get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_mesh.get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex({static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[X]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[Y]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[Z])},
                                              {static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[X]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[Y]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the entity into the list of render-able props.
            m_light.emplace_back(Prop(vertices, t_col));
        }

        /**
         *  Add a render-able light prop to the scene.
         *
         *  @param  t_mesh  Light source mesh to be added to the scene.
         *  @param  t_power Power of the light source.
         *  @param  t_col   Colour to render the light with.
         */
        void Scene::add_light(const geom::Mesh& t_mesh, const float t_power, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_mesh.get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_mesh.get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex({static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[X]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[Y]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_pos()[Z])},
                                              {static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[X]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[Y]),
                                               static_cast<float>(t_mesh.get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the light prop into the list of render-able light props.
            m_light.emplace_back(prop::Light(vertices, t_col, t_power));
        }

        /**
         *  Add a renderable photon packet path prop to the scene.
         *
         *  @param  t_phot  Photon packet path prop to be added.
         */
        void Scene::add_photon(const std::vector<point::Photon>& t_phot)
        {
            m_phot.emplace_back(Prop(t_phot, glm::vec4({1.0, 0.0, 0.0, 1.0})));
        }


        //  -- Render --
        /**
         *  Render control function.
         *  Call sub-functions to render objects within the scene.
         */
        void Scene::render() const
        {
            // Clear the buffer.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Setup the shaders.
            setup_skybox_shader();
            setup_ambient_shader();
            setup_diffuse_shader();
            setup_normal_shader();
            setup_photon_shader();

            // Draw props.
            draw_skybox();
            draw_entities();
            draw_lights();
            draw_sun();
            draw_phots();

            // Swap the buffers.
            glfwSwapBuffers(m_window);
        }


        //  -- Control --
        /**
         *  Check if the window should close.
         *  This is triggered by either the escape key being pressed, or the red cross being clicked.
         *
         *  @return True if the window should close.
         */
        bool Scene::should_close() const
        {
            return ((glfwGetKey(m_window, control::QUIT) == GLFW_PRESS) || (glfwWindowShouldClose(m_window) != 0));
        }

        /**
         *  Poll the window events and call specialised functions to handle sets of controls.
         */
        void Scene::handle_input()
        {
            // Calculate elapsed time since last update.
            static auto last_time  = static_cast<float>(glfwGetTime());
            auto        cur_time   = static_cast<float>(glfwGetTime());
            float       time_delta = cur_time - last_time;
            last_time = cur_time;

            // Poll the window events.
            glfwPollEvents();

            // Control the camera.
            swap_camera();
            move_camera(time_delta);

            // Control the sun.
            move_sun(time_delta);

            // Control toggles.
            toggle();

            // Propagate photons.
            propagate_photons(time_delta);
        }

        /**
         *  Swap the primary and secondary cameras if the camera swap key has been pressed.
         */
        void Scene::swap_camera()
        {
            static int old_state = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::SWAP_CAM) != old_state)
            {
                old_state = glfwGetKey(m_window, control::SWAP_CAM);

                if (old_state == GLFW_PRESS)
                {
                    std::swap(m_primary_cam, m_secondary_cam);
                }
            }
        }

        /**
         *  Control the movement of the camera.
         *
         *  @param  t_time_delta    Time elapsed since the last rendering.
         */
        void Scene::move_camera(const float t_time_delta)
        {
            glm::vec3 translate;
            glm::vec2 rotate;
            float     speed_multiplier = 1.0f;

            if (glfwGetKey(m_window, control::DECREASE_CAM_SPEED) == GLFW_PRESS)
            {
                speed_multiplier /= 10.0f;
            }
            if (glfwGetKey(m_window, control::INCREASE_CAM_SPEED) == GLFW_PRESS)
            {
                speed_multiplier *= 10.0f;
            }

            if (glfwGetKey(m_window, control::TRANS_CAM_FORWARD) == GLFW_PRESS)
            {
                translate[0] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_CAM_BACKWARD) == GLFW_PRESS)
            {
                translate[0] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_CAM_LEFT) == GLFW_PRESS)
            {
                translate[1] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_CAM_RIGHT) == GLFW_PRESS)
            {
                translate[1] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_CAM_UP) == GLFW_PRESS)
            {
                translate[2] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_CAM_DOWN) == GLFW_PRESS)
            {
                translate[2] -= speed_multiplier * t_time_delta;
            }

            if (glfwGetKey(m_window, control::ROT_CAM_LEFT) == GLFW_PRESS)
            {
                rotate[0] += t_time_delta;
            }
            if (glfwGetKey(m_window, control::ROT_CAM_RIGHT) == GLFW_PRESS)
            {
                rotate[0] -= t_time_delta;
            }
            if (glfwGetKey(m_window, control::ROT_CAM_UP) == GLFW_PRESS)
            {
                rotate[1] += t_time_delta;
            }
            if (glfwGetKey(m_window, control::ROT_CAM_DOWN) == GLFW_PRESS)
            {
                rotate[1] -= t_time_delta;
            }

            m_primary_cam->move(translate, rotate);
        }

        /**
         *  Control the movement of the sun global illuminator object.
         *
         *  @param  t_time_delta    Time elapsed since the last rendering.
         */
        void Scene::move_sun(const float t_time_delta)
        {
            float speed_multiplier = 1.0f;

            if (glfwGetKey(m_window, control::DECREASE_CAM_SPEED) == GLFW_PRESS)
            {
                speed_multiplier /= 10.0f;
            }
            if (glfwGetKey(m_window, control::INCREASE_CAM_SPEED) == GLFW_PRESS)
            {
                speed_multiplier *= 10.0f;
            }

            if (glfwGetKey(m_window, control::TRANS_SUN_FORWARD) == GLFW_PRESS)
            {
                m_sun_pos[X] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_SUN_BACKWARD) == GLFW_PRESS)
            {
                m_sun_pos[X] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_SUN_LEFT) == GLFW_PRESS)
            {
                m_sun_pos[Y] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_SUN_RIGHT) == GLFW_PRESS)
            {
                m_sun_pos[Y] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_SUN_UP) == GLFW_PRESS)
            {
                m_sun_pos[Z] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::TRANS_SUN_DOWN) == GLFW_PRESS)
            {
                m_sun_pos[Z] -= speed_multiplier * t_time_delta;
            }
        }

        /**
         *  Control the toggle values.
         */
        void Scene::toggle()
        {
            // Filled triangle rendering.
            static int old_state_toggle_filled_tris = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::TOGGLE_FILLED_TRIS) != old_state_toggle_filled_tris)
            {
                old_state_toggle_filled_tris = glfwGetKey(m_window, control::TOGGLE_FILLED_TRIS);

                if (old_state_toggle_filled_tris == GLFW_PRESS)
                {
                    m_toggle_filled_tris = !m_toggle_filled_tris;
                }
            }

            // Light normal rendering.
            static int old_state_toggle_light_normal = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::TOGGLE_LIGHT_NORMAL) != old_state_toggle_light_normal)
            {
                old_state_toggle_light_normal = glfwGetKey(m_window, control::TOGGLE_LIGHT_NORMAL);

                if (old_state_toggle_light_normal == GLFW_PRESS)
                {
                    m_toggle_light_normal = !m_toggle_light_normal;
                }
            }
        }

        /**
         *  Initiate or halt the rendering of photon packet paths.
         *
         *  @param  t_time_delta    Time elapsed since the last rendering.
         */
        void Scene::propagate_photons(float t_time_delta)
        {
            static int old_state_propagate_photons = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::INIT_PHOTON_TRANSPORT) != old_state_propagate_photons)
            {
                old_state_propagate_photons = glfwGetKey(m_window, control::INIT_PHOTON_TRANSPORT);

                if (old_state_propagate_photons == GLFW_PRESS)
                {
                    if (m_render_dist > 0.0f)
                    {
                        m_render_dist = 0.0f;
                    }
                    else
                    {
                        m_render_dist = 0.01f;
                    }
                }
            }

            // Increase render distance if dynamic rendering is active.
            if (m_render_dist > 0.0f)
            {
                m_render_dist += t_time_delta;
            }
        }


        //  -- Shader Setup --
        /**
         *  Setup the skybox shader ready for rendering.
         */
        void Scene::setup_skybox_shader() const
        {
            glUseProgram(m_skybox_shader.get_handle());

            glm::mat4 view = glm::mat4(glm::mat3(m_primary_cam->get_view()));

            glUniformMatrix4fv(m_skybox_shader.get_view_uni(), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(m_skybox_shader.get_proj_uni(), 1, GL_FALSE, &m_primary_cam->get_proj()[0][0]);
        }

        /**
         *  Setup the ambient shader ready for rendering.
         */
        void Scene::setup_ambient_shader() const
        {
            glUseProgram(m_ambient_shader.get_handle());

            glUniformMatrix4fv(m_ambient_shader.get_mvp_uni(), 1, GL_FALSE, &m_primary_cam->get_mvp()[0][0]);
        }

        /**
         *  Setup the diffuse shader ready for rendering.
         */
        void Scene::setup_diffuse_shader() const
        {
            glUseProgram(m_diffuse_shader.get_handle());

            glUniformMatrix4fv(m_diffuse_shader.get_mvp_uni(), 1, GL_FALSE, &m_primary_cam->get_mvp()[0][0]);
            glUniformMatrix4fv(m_diffuse_shader.get_view_uni(), 1, GL_FALSE, &m_primary_cam->get_view()[0][0]);
            glUniform3f(m_diffuse_shader.get_sun_pos_uni(), m_sun_pos[X], m_sun_pos[Y], m_sun_pos[Z]);
        }

        /**
         *  Setup the normal shader ready for rendering.
         */
        void Scene::setup_normal_shader() const
        {
            glUseProgram(m_normal_shader.get_handle());

            glUniformMatrix4fv(m_normal_shader.get_mvp_uni(), 1, GL_FALSE, &m_primary_cam->get_mvp()[0][0]);
        }

        /**
         *  Setup the photon shader ready for rendering.
         */
        void Scene::setup_photon_shader() const
        {
            glUseProgram(m_path_shader.get_handle());

            glUniformMatrix4fv(m_path_shader.get_mvp_uni(), 1, GL_FALSE, &m_primary_cam->get_mvp()[0][0]);
            glUniform1f(m_path_shader.get_render_dist_uni(), m_render_dist);
        }


        //  -- Drawing --
        /**
         *  Draw the scene's entities.
         */
        void Scene::draw_entities() const
        {
            // Draw diffusely lit prop mesh.
            glUseProgram(m_diffuse_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

            glUniform1f(m_diffuse_shader.get_amb_pow_uni(), ENTITIY_AMB_POW);

            for (size_t i = 0; i < m_entity.size(); ++i)
            {
                glUniform4f(m_diffuse_shader.get_col_uni(), m_entity[i].get_col()[R], m_entity[i].get_col()[G],
                            m_entity[i].get_col()[B], m_entity[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_entity[i].get_vao());

                glDrawArrays(GL_TRIANGLES, 0, m_entity[i].get_num_vert());

                glBindVertexArray(0);
            }

            // Draw normals if toggle is on.
            if (m_toggle_light_normal)
            {
                glUseProgram(m_normal_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                for (size_t i = 0; i < m_entity.size(); ++i)
                {
                    glUniform4f(m_normal_shader.get_col_uni(), m_entity[i].get_col()[R], m_entity[i].get_col()[G],
                                m_entity[i].get_col()[B], m_entity[i].get_col()[A]);
                    glUniform1f(m_normal_shader.get_light_power_uni(), ENTITY_NORMAL_LENGTH);

                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_entity[i].get_vao());

                    glDrawArrays(GL_POINTS, 0, m_entity[i].get_num_vert());

                    glBindVertexArray(0);
                }
            }
        }

        /**
         *  Draw the scene's light sources.
         */
        void Scene::draw_lights() const
        {
            // Draw diffusely lit prop mesh.
            glUseProgram(m_diffuse_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

            glUniform1f(m_diffuse_shader.get_amb_pow_uni(), LIGHT_AMB_POW);

            for (size_t i = 0; i < m_light.size(); ++i)
            {
                glUniform4f(m_diffuse_shader.get_col_uni(), m_light[i].get_col()[R], m_light[i].get_col()[G],
                            m_light[i].get_col()[B], m_light[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_light[i].get_vao());

                glDrawArrays(GL_TRIANGLES, 0, m_light[i].get_num_vert());

                glBindVertexArray(0);
            }

            // Draw normals if toggle is on.
            if (m_toggle_light_normal)
            {
                glUseProgram(m_normal_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                for (size_t i = 0; i < m_light.size(); ++i)
                {
                    glUniform4f(m_normal_shader.get_col_uni(), m_light[i].get_col()[R], m_light[i].get_col()[G],
                                m_light[i].get_col()[B], m_light[i].get_col()[A]);
                    glUniform1f(m_normal_shader.get_light_power_uni(), m_light[i].get_power());

                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_light[i].get_vao());

                    glDrawArrays(GL_POINTS, 0, m_light[i].get_num_vert());

                    glBindVertexArray(0);
                }
            }
        }

        /**
         *  Draw the scene's photon packet paths.
         */
        void Scene::draw_phots() const
        {
            glUseProgram(m_path_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

            for (size_t i = 0; i < m_phot.size(); ++i)
            {
                glUniform4f(m_path_shader.get_col_uni(), m_phot[i].get_col()[R], m_phot[i].get_col()[G], m_phot[i].get_col()[B],
                            m_phot[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_phot[i].get_vao());

                glDrawArrays(GL_LINE_STRIP, 0, m_phot[i].get_num_vert());

                glBindVertexArray(0);
            }
        }

        /**
         *  Draw the global illuminator object.
         */
        void Scene::draw_sun() const
        {
            glm::mat4 mvp = m_primary_cam->get_mvp() * glm::translate(m_sun_pos);

            glUseProgram(m_ambient_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glUniformMatrix4fv(m_ambient_shader.get_mvp_uni(), 1, GL_FALSE, &mvp[0][0]);
            glUniform4f(m_ambient_shader.get_col_uni(), m_sun.get_col()[R], m_sun.get_col()[G], m_sun.get_col()[B],
                        m_sun.get_col()[A]);

            glEnableVertexAttribArray(0);

            glBindVertexArray(m_sun.get_vao());

            glDrawArrays(GL_TRIANGLES, 0, m_sun.get_num_vert());

            glBindVertexArray(0);
        }

        /**
         *  Draw the skybox.
         */
        void Scene::draw_skybox() const
        {
            // Load the shader.
            glUseProgram(m_skybox_shader.get_handle());

            // Set drawing mode.
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // Pass the cubemap.
            glBindVertexArray(m_cube_box.get_vao());
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap);

            // Draw the skybox.
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glBindVertexArray(0);
        }



    } // namespace graphical
} // namespace arc
