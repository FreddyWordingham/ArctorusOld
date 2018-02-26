/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == HEADER ==
#include "cls/graphical/scene.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/transform.hpp>

//  -- Library --
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

//  -- General --
#include "gen/control.hpp"

//  -- Utility --
#include "utl/colourmap.hpp"

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
            m_cube_box(Prop(Prop::originShape::SKYBOX, {1.0, 0.0, 1.0, 1.0}, 10.0)),
            m_primary_cam(std::make_unique<camera::Orbit>(glm::vec3({INIT_CAM_POS_X, INIT_CAM_POS_Y, INIT_CAM_POS_Z}),
                                                          static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_secondary_cam(std::make_unique<camera::Fly>(glm::vec3({INIT_CAM_POS_X, INIT_CAM_POS_Y, INIT_CAM_POS_Z}),
                                                          static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_sun_pos(glm::vec3({INIT_SUN_POS_X, INIT_SUN_POS_Y, INIT_SUN_POS_Z})),
            m_sun(Prop(Prop::originShape::SUN, {1.0, 1.0, 0.0, 1.0}, SUN_SIZE))
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

            // Enable back-face culling.
//            glEnable(GL_CULL_FACE);

            // Enable transparency.
//            glEnable(GL_BLEND);
//            glBlendFunc(GL_SRC_ALPHA,GL_ONE);

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
         *  Add a vector of render-able light props to the scene.
         *
         *  @param  t_light Vector of lights to be added to the scene.
         *
         *  @pre    LIGHT_START_HUE must be less than LIGHT_END_HUE.
         */
        void Scene::add_light_vector(const std::vector<equip::Light>& t_light)
        {
            static_assert(LIGHT_START_HUE < LIGHT_END_HUE);

            // Return if there are no lights.
            if (t_light.empty())
            {
                return;
            }

            // Calculate the hue delta.
            const double hue_delta = (t_light.size() == 1) ? 0.0 : ((LIGHT_END_HUE - LIGHT_START_HUE) / (t_light.size() - 1));

            // Add the light props to the scene.
            for (size_t i = 0; i < t_light.size(); ++i)
            {
                const auto hue = static_cast<float>(math::deg_to_rad(LIGHT_START_HUE + (i * hue_delta)));

                add_light(t_light[i], glm::vec4(hsv_to_rgb(hue, 1.0f, 1.0f), 1.0));
            }
        }

        /**
         *  Add a vector of render-able entity props to the scene.
         *
         *  @param  t_entity    Vector of entities to be added to the scene.
         *
         *  @pre    ENTITY_START_HUE must be less than ENTITY_END_HUE.
         */
        void Scene::add_entity_vector(const std::vector<equip::Entity>& t_entity)
        {
            static_assert(ENTITY_START_HUE < ENTITY_END_HUE);

            // Return if there are no entities.
            if (t_entity.empty())
            {
                return;
            }

            // Calculate the hue delta.
            const double hue_delta = (t_entity.size() == 1) ? 0.0 : ((ENTITY_END_HUE - ENTITY_START_HUE) / (t_entity
                .size() - 1));

            // Add the entity props to the scene.
            for (size_t i = 0; i < t_entity.size(); ++i)
            {
                const auto hue = static_cast<float>(math::deg_to_rad(ENTITY_START_HUE + (i * hue_delta)));

                add_entity(t_entity[i], glm::vec4(hsv_to_rgb(hue, 1.0f, 1.0f), 0.5));
            }
        }

        /**
         *  Add a vector of render-able ccd props to the scene.
         *
         *  @param  t_ccd   Vector of ccds to be added to the scene.
         *
         *  @pre    CCD_START_HUE must be less than CCD_END_HUE.
         */
        void Scene::add_ccd_vector(const std::vector<detector::Ccd>& t_ccd)
        {
            static_assert(CCD_START_HUE < CCD_END_HUE);

            // Return if there are no entities.
            if (t_ccd.empty())
            {
                return;
            }

            // Calculate the hue delta.
            const double hue_delta = (t_ccd.size() == 1) ? 0.0 : ((CCD_END_HUE - CCD_START_HUE) / (t_ccd.size() - 1));

            // Add the entity props to the scene.
            for (size_t i = 0; i < t_ccd.size(); ++i)
            {
                const auto hue = static_cast<float>(math::deg_to_rad(CCD_START_HUE + (i * hue_delta)));

                add_ccd(t_ccd[i], glm::vec4(hsv_to_rgb(hue, 1.0f, 1.0f), 0.5));
            }
        }

        /**
         *  Add a vector of render-able spectrometer props to the scene.
         *
         *  @param  t_spectrometer  Vector of spectrometers to be added to the scene.
         *
         *  @pre    SPECTROMETER_START_HUE must be less than SPECTROMETER_END_HUE.
         */
        void Scene::add_spectrometer_vector(const std::vector<detector::Spectrometer>& t_spectrometer)
        {
            static_assert(SPECTROMETER_START_HUE < SPECTROMETER_END_HUE);

            // Return if there are no entities.
            if (t_spectrometer.empty())
            {
                return;
            }

            // Calculate the hue delta.
            const double hue_delta = (t_spectrometer.size() == 1) ? 0.0
                                                                  : ((SPECTROMETER_END_HUE - SPECTROMETER_START_HUE) / (t_spectrometer
                    .size() - 1));

            // Add the entity props to the scene.
            for (size_t i = 0; i < t_spectrometer.size(); ++i)
            {
                const auto hue = static_cast<float>(math::deg_to_rad(SPECTROMETER_START_HUE + (i * hue_delta)));

                add_spectrometer(t_spectrometer[i], glm::vec4(hsv_to_rgb(hue, 1.0f, 1.0f), 0.5));
            }
        }

        /**
         *  Add a vector of render-able photon path props to the scene.
         *
         *  @param  t_phot  Vector of photon paths to be added to the scene.
         *
         *  @pre    PHOTON_START_HUE must be less than PHOTON_END_HUE.
         */
        void Scene::add_photon_vector(const std::vector<std::vector<point::Photon>>& t_phot)
        {
            // Return if there are no photon paths.
            if (t_phot.empty())
            {
                return;
            }

            // Add the photon path props to the scene.
            for (size_t i = 0; i < t_phot.size(); ++i)
            {
                add_photon(t_phot[i], glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            }
        }

        /**
         *  Add a render-able grid mesh to the scene.
         *
         *  @param  t_grid  Grid to be added to the scene.
         */
        void Scene::add_grid(const mesh::Grid& t_grid)
        {
            // Add main grid bounds.
            m_grid.emplace_back(Prop(Prop::boundedShape::BOX, {1.0, 1.0, 1.0, 1.0},
                                     {static_cast<float>(t_grid.get_min_bound()[X]),
                                      static_cast<float>(t_grid.get_min_bound()[Y]),
                                      static_cast<float>(t_grid.get_min_bound()[Z])},
                                     {static_cast<float>(t_grid.get_max_bound()[X]),
                                      static_cast<float>(t_grid.get_max_bound()[Y]),
                                      static_cast<float>(t_grid.get_max_bound()[Z])}));

            // Determine maximum grid cell energy density.
            double max_energy_density = t_grid.get_max_energy_density();
            VAL(max_energy_density);

            // Add grid cells.
            for (size_t i = 0; i < t_grid.get_num_cells(X); ++i)
            {
                for (size_t j = 0; j < t_grid.get_num_cells(Y); ++j)
                {
                    for (size_t k = 0; k < t_grid.get_num_cells(Z); ++k)
                    {
                        const double energy_density = t_grid.get_cell(i, j, k).get_energy_density();

                        if (energy_density > 0.0)
                        {
                            // Get the cell.
                            const auto cell = t_grid.get_cell(i, j, k);

                            // Calculate the cell colour.
                            const std::array<double, 3> col = utl::colourmap::transform_rainbow(
                                energy_density / max_energy_density);

                            // Add the cell prop.
                            add_cell(cell.get_min_bound(), cell.get_max_bound(), 0.01,
                                     {glm::vec3(col[R], col[G], col[B]), 1.0});
                        }
                    }
                }
            }
        }

        /**
         *  Add a render-able entity prop to the scene.
         *
         *  @param  t_ent   Entity be added to the scene.
         *  @param  t_col   Colour to render the prop.
         */
        void Scene::add_entity(const equip::Entity& t_ent, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_ent.get_mesh().get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_ent.get_mesh().get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex({static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_pos()[X]),
                                               static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_pos()[Y]),
                                               static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_pos()[Z])},
                                              {static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_norm()[X]),
                                               static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_norm()[Y]),
                                               static_cast<float>(t_ent.get_mesh().get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the entity into the list of render-able props.
            m_entity.emplace_back(Prop(vertices, t_col));
        }

        /**
         *  Add a render-able light prop to the scene.
         *
         *  @param  t_light Light to be added to the scene.
         *  @param  t_col   Colour to render the prop.
         */
        void Scene::add_light(const equip::Light& t_light, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_light.get_mesh().get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_light.get_mesh().get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex({static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_pos()[X]),
                                               static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_pos()[Y]),
                                               static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_pos()[Z])},
                                              {static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_norm()[X]),
                                               static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_norm()[Y]),
                                               static_cast<float>(t_light.get_mesh().get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the light prop into the list of render-able light props.
            m_light.emplace_back(prop::Light(vertices, static_cast<float>(t_light.get_power()), t_col));
        }

        /**
         *  Add a render-able ccd prop to the scene.
         *
         *  @param  t_ccd   Ccd to be added to the scene.
         *  @param  t_col   Colour to render the prop.
         */
        void Scene::add_ccd(const detector::Ccd& t_ccd, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_ccd.get_mesh().get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_ccd.get_mesh().get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex({static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_pos()[X]),
                                               static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_pos()[Y]),
                                               static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_pos()[Z])},
                                              {static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_norm()[X]),
                                               static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_norm()[Y]),
                                               static_cast<float>(t_ccd.get_mesh().get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the ccd prop into the list of render-able ccd props.
            m_ccd.emplace_back(Prop(vertices, t_col));
        }

        /**
         *  Add a render-able spectrometer prop to the scene.
         *
         *  @param  t_spectrometer  Spectrometer to be added to the scene.
         *  @param  t_col           Colour to render the prop.
         */
        void Scene::add_spectrometer(const detector::Spectrometer& t_spectrometer, const glm::vec4& t_col)
        {
            // Create vector of vertices.
            std::vector<Vertex> vertices;
            vertices.reserve(t_spectrometer.get_mesh().get_num_tri() * 3);

            // Add vertices into list from mesh.
            for (size_t i = 0; i < t_spectrometer.get_mesh().get_num_tri(); ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    vertices.push_back(Vertex(
                        {static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_pos()[X]),
                         static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_pos()[Y]),
                         static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_pos()[Z])},
                        {static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_norm()[X]),
                         static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_norm()[Y]),
                         static_cast<float>(t_spectrometer.get_mesh().get_tri(i).get_vert(j).get_norm()[Z])}));
                }
            }

            // Add the light prop into the list of render-able light props.
            m_spectrometer.emplace_back(Prop(vertices, t_col));
        }

        /**
         *  Add a renderable photon packet path prop to the scene.
         *
         *  @param  t_phot  Photon packet path prop to be added.
         *  @param  t_col   Colour to render the prop.
         */
        void Scene::add_photon(const std::vector<point::Photon>& t_phot, const glm::vec4& t_col)
        {
            m_phot.emplace_back(Prop(t_phot, t_col));
        }

        /**
         *  Add a render-able cell prop to the scene.
         *
         *  @param  t_min       Minimum bound of the cell.
         *  @param  t_max       Minimum bound of the cell.
         *  @param  t_padding   Padding to apply to cell bounds.
         *  @param  t_col       Colour of the cell prop.
         */
        void Scene::add_cell(const math::Vec<3>& t_min, const math::Vec<3>& t_max, const double t_padding,
                             const glm::vec4& t_col)
        {
            m_cell.emplace_back(
                Prop(Prop::boundedShape::BOX, t_col, {t_min[X] + t_padding, t_min[Y] + t_padding, t_min[Z] + t_padding},
                     {t_max[X] - t_padding, t_max[Y] - t_padding, t_max[Z] - t_padding}));
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
            draw_ccds();
            draw_spectrometers();
            draw_grid();
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

            // Photon path rendering.
            static int old_state_toggle_photon_render = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::TOGGLE_PHOTON_RENDER) != old_state_toggle_photon_render)
            {
                old_state_toggle_photon_render = glfwGetKey(m_window, control::TOGGLE_PHOTON_RENDER);

                if (old_state_toggle_photon_render == GLFW_PRESS)
                {
                    m_toggle_photon_render = !m_toggle_photon_render;
                }
            }

            // Grid rendering.
            static int old_state_toggle_cell_render = GLFW_RELEASE;

            if (glfwGetKey(m_window, control::TOGGLE_CELL_RENDER) != old_state_toggle_cell_render)
            {
                old_state_toggle_cell_render = glfwGetKey(m_window, control::TOGGLE_CELL_RENDER);

                if (old_state_toggle_cell_render == GLFW_PRESS)
                {
                    m_toggle_cell_render = !m_toggle_cell_render;
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
                    if (m_render_time > 0.0f)
                    {
                        m_render_time = 0.0f;
                    }
                    else
                    {
                        m_render_time = t_time_delta * PHOTON_TRAVEL_SPEED;
                    }
                }
            }

            // Increase render time if dynamic rendering is active.
            if (m_render_time > 0.0f)
            {
                m_render_time += t_time_delta * PHOTON_TRAVEL_SPEED;
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
            glUniform1f(m_path_shader.get_time_uni(), m_render_time);
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
         *  Draw the scene's ccds.
         */
        void Scene::draw_ccds() const
        {
            // Draw diffusely lit prop mesh.
            glUseProgram(m_diffuse_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

            glUniform1f(m_diffuse_shader.get_amb_pow_uni(), CCD_AMB_POW);

            for (size_t i = 0; i < m_ccd.size(); ++i)
            {
                glUniform4f(m_diffuse_shader.get_col_uni(), m_ccd[i].get_col()[R], m_ccd[i].get_col()[G], m_ccd[i].get_col()[B],
                            m_ccd[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_ccd[i].get_vao());

                glDrawArrays(GL_TRIANGLES, 0, m_ccd[i].get_num_vert());

                glBindVertexArray(0);
            }

            // Draw normals if toggle is on.
            if (m_toggle_light_normal)
            {
                glUseProgram(m_normal_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                for (size_t i = 0; i < m_ccd.size(); ++i)
                {
                    glUniform4f(m_normal_shader.get_col_uni(), m_ccd[i].get_col()[R], m_ccd[i].get_col()[G],
                                m_ccd[i].get_col()[B], m_ccd[i].get_col()[A]);
                    glUniform1f(m_normal_shader.get_light_power_uni(), CCD_NORMAL_LENGTH);

                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_ccd[i].get_vao());

                    glDrawArrays(GL_POINTS, 0, m_ccd[i].get_num_vert());

                    glBindVertexArray(0);
                }
            }
        }

        /**
         *  Draw the scene's spectrometers.
         */
        void Scene::draw_spectrometers() const
        {
            // Draw diffusely lit prop mesh.
            glUseProgram(m_diffuse_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

            glUniform1f(m_diffuse_shader.get_amb_pow_uni(), SPECTROMETER_AMB_POW);

            for (size_t i = 0; i < m_spectrometer.size(); ++i)
            {
                glUniform4f(m_diffuse_shader.get_col_uni(), m_spectrometer[i].get_col()[R], m_spectrometer[i].get_col()[G],
                            m_spectrometer[i].get_col()[B], m_spectrometer[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_spectrometer[i].get_vao());

                glDrawArrays(GL_TRIANGLES, 0, m_spectrometer[i].get_num_vert());

                glBindVertexArray(0);
            }

            // Draw normals if toggle is on.
            if (m_toggle_light_normal)
            {
                glUseProgram(m_normal_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                for (size_t i = 0; i < m_spectrometer.size(); ++i)
                {
                    glUniform4f(m_normal_shader.get_col_uni(), m_spectrometer[i].get_col()[R], m_spectrometer[i].get_col()[G],
                                m_spectrometer[i].get_col()[B], m_spectrometer[i].get_col()[A]);
                    glUniform1f(m_normal_shader.get_light_power_uni(), SPECTROMETER_NORMAL_LENGTH);

                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_spectrometer[i].get_vao());

                    glDrawArrays(GL_POINTS, 0, m_spectrometer[i].get_num_vert());

                    glBindVertexArray(0);
                }
            }
        }

        /**
         *  Draw the scene's photon packet paths.
         */
        void Scene::draw_phots() const
        {
            if (m_toggle_photon_render)
            {
                glUseProgram(m_path_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, m_toggle_filled_tris ? GL_FILL : GL_LINE);

                for (size_t i = 0; i < m_phot.size(); ++i)
                {
                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_phot[i].get_vao());

                    glDrawArrays(GL_LINE_STRIP, 0, m_phot[i].get_num_vert());

                    glBindVertexArray(0);
                }
            }
        }

        /**
         *  Draw the scene's cells.
         */
        void Scene::draw_grid() const
        {
            glUseProgram(m_ambient_shader.get_handle());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            for (size_t i = 0; i < m_grid.size(); ++i)
            {
                glUniform4f(m_ambient_shader.get_col_uni(), m_grid[i].get_col()[R], m_grid[i].get_col()[G],
                            m_grid[i].get_col()[B], m_grid[i].get_col()[A]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_grid[i].get_vao());

                glDrawArrays(GL_LINES, 0, m_grid[i].get_num_vert());

                glBindVertexArray(0);
            }

            // If cell rendering is toggle on, draw the cells.
            if (m_toggle_cell_render)
            {
                glUseProgram(m_diffuse_shader.get_handle());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                for (size_t i = 0; i < m_cell.size(); ++i)
                {
                    glUniform4f(m_diffuse_shader.get_col_uni(), m_cell[i].get_col()[R], m_cell[i].get_col()[G],
                                m_cell[i].get_col()[B], m_cell[i].get_col()[A]);

                    glEnableVertexAttribArray(0);

                    glBindVertexArray(m_cell[i].get_vao());

                    glDrawArrays(GL_LINES, 0, m_cell[i].get_num_vert());

                    glBindVertexArray(0);
                }
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


        //  -- Utility --
        /**
         *  Convert a hsv colour to an rgb colour vector.
         *
         *  @param  t_hue       Hue of the colour.
         *  @param  t_sat       Saturation of the colour.
         *  @param  t_value     Brightness of the colour.
         *
         *  @pre    t_hue must be between zero and two pi.
         *  @pre    t_sat must be between zero and one.
         *  @pre    t_value must be between zero and one.
         *
         *  @post   red must be between zero and one.
         *  @post   green must be between zero and one.
         *  @post   blue must be between zero and one.
         *
         *  @return The rgb equivalent of the given hsv colour.
         */
        glm::vec3 Scene::hsv_to_rgb(const float t_hue, const float t_sat, const float t_value) const
        {
            assert((t_hue >= 0.0f) && (t_hue < static_cast<float>(2.0 * M_PI)));
            assert((t_sat >= 0.0f) && (t_sat <= 1.0f));
            assert((t_value >= 0.0f) && (t_value <= 1.0f));

            // Calculate conversion values.
            const auto  sector = static_cast<int>(t_hue / static_cast<float>(M_PI / 3.0));
            const float ff     = (t_hue / static_cast<float>(M_PI / 3.0)) - sector;
            const float p      = t_value * (1.0f - t_sat);
            const float q      = t_value * (1.0f - (t_sat * ff));
            const float t      = t_value * (1.0f - (t_sat * (1.0f - ff)));

            // Calculate the rgb values.
            float red, blue, green;
            switch (sector)
            {
                case 0:
                    red   = t_value;
                    green = t;
                    blue  = p;
                    break;
                case 1:
                    red   = q;
                    green = t_value;
                    blue  = p;
                    break;
                case 2:
                    red   = p;
                    green = t_value;
                    blue  = t;
                    break;
                case 3:
                    red   = p;
                    green = q;
                    blue  = t_value;
                    break;
                case 4:
                    red   = t;
                    green = p;
                    blue  = t_value;
                    break;
                case 5:
                    red   = t_value;
                    green = p;
                    blue  = q;
                    break;
                default: ERROR("Unable to convert hsv to rgb colour.", "Colour sector is invalid.");
            }

            assert((red >= 0.0f) && (red <= 1.0f));
            assert((green >= 0.0f) && (green <= 1.0f));
            assert((blue >= 0.0f) && (blue <= 1.0f));

            return (glm::vec3(red, green, blue));
        }



    } // namespace graphical
} // namespace arc



//  == MODULE END ==
#endif
