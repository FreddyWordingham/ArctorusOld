/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/scene.hpp"



//  == INCLUDES ==
//  -- System --

//  -- General --
#include "gen/control.hpp"
#include "gen/log.hpp"
#include "gen/rng.hpp"

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
         *  Construct a graphical scene.
         */
        Scene::Scene() :
            m_window(init_window()),
            m_primary_cam(
                std::make_unique<camera::Orbit>(INIT_CAM_POS, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_secondary_cam(
                std::make_unique<camera::Fly>(INIT_CAM_POS, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_ambient_shader(file::read(AMBIENT_VERT_SHADER, false), file::read(AMBIENT_FRAG_SHADER, false))
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

            return (r_window);
        }



        //  == METHODS ==
        //  -- Input --
        /**
         *  Check if the window should close.
         *  This is triggered by either the escape key being pressed, or the red cross being clicked.
         *
         *  @return True if the window should close.
         */
        bool Scene::should_close() const
        {
            // Esc key has been pressed.
            if (glfwGetKey(m_window, control::QUIT) == GLFW_PRESS)
            {
                return (true);
            }

            return (glfwWindowShouldClose(m_window) != 0);
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
        }


        //  -- Additions --
        /**
         *  Add a light to the scene.
         *
         *  @param  t_pos       Position of the light source.
         *  @param  t_rot       Rotations applied to the light source.
         *  @param  t_rad       Radius of the light source.
         *  @param  t_aperture  Numerical aperture of the light source.
         *  @param  t_power     power of the light source.
         */
        void Scene::add_light(const math::Vec<3>& t_pos, const math::Vec<3>& t_rot, const double t_rad, const double t_aperture,
                              const double t_power)
        {
            m_spotlight.push_back(create_spotlight_prop(
                {{static_cast<float>(t_pos[X]), static_cast<float>(t_pos[Y]), static_cast<float>(t_pos[Z])}},
                {{static_cast<float>(t_rot[X]), static_cast<float>(t_rot[Y]), static_cast<float>(t_rot[Z])}},
                static_cast<float>(t_rad), static_cast<float>(t_aperture), static_cast<float>(t_power),
                {rng::random(0.0, 1.0), rng::random(0.0, 1.0), rng::random(0.0, 1.0)}));
        }


        //  -- Render --
        /**
         *  Render control function.
         *  Call sub-functions to render the objects within scene.
         */
        void Scene::render() const
        {
            // Clear the buffer.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Setup the shaders.
            setup_ambient_shader();

//            glEnable(GL_DEPTH_TEST);
            //          glDepthFunc(GL_LESS);

            // Drawing.
            draw_spotlights();

            // Swap to the new buffer.
            glfwSwapBuffers(m_window);
        }

        /**
         *  Setup the ambient shader ready for rendering.
         */
        void Scene::setup_ambient_shader() const
        {
            glUseProgram(m_ambient_shader.get_handle());

            glUniformMatrix4fv(m_ambient_shader.get_mvp(), 1, GL_FALSE, &m_primary_cam->get_mvp()[0][0]);
        }

        /**
         *  Draw the spotlights within a scene.
         */
        void Scene::draw_spotlights() const
        {
            // Use the ambient shader.
            glUseProgram(m_ambient_shader.get_handle());

            // Set drawing mode.
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // Draw each spotlight.
            for (size_t i = 0; i < m_spotlight.size(); ++i)
            {
                glUniform3f(m_ambient_shader.get_prop_col(), m_spotlight[i].get_col()[R], m_spotlight[i].get_col()[G],
                            m_spotlight[i].get_col()[B]);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_spotlight[i].get_vao());

                glDrawArrays(GL_LINES, 0, m_spotlight[i].get_num_vert());

                glBindVertexArray(0);
            }
        }


        //  -- Control --
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

            // Speed multipliers.
            if (glfwGetKey(m_window, control::DECREASE_SPEED) == GLFW_PRESS)
            {
                speed_multiplier /= 10.0f;
            }
            if (glfwGetKey(m_window, control::INCREASE_SPEED) == GLFW_PRESS)
            {
                speed_multiplier *= 10.0f;
            }

            // Translation.
            if (glfwGetKey(m_window, control::MOVE_CAM_FORWARD) == GLFW_PRESS)
            {
                translate[0] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::MOVE_CAM_BACKWARD) == GLFW_PRESS)
            {
                translate[0] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::MOVE_CAM_LEFT) == GLFW_PRESS)
            {
                translate[1] -= speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::MOVE_CAM_RIGHT) == GLFW_PRESS)
            {
                translate[1] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::MOVE_CAM_UP) == GLFW_PRESS)
            {
                translate[2] += speed_multiplier * t_time_delta;
            }
            if (glfwGetKey(m_window, control::MOVE_CAM_DOWN) == GLFW_PRESS)
            {
                translate[2] -= speed_multiplier * t_time_delta;
            }

            // Rotation.
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



    } // namespace graphical
} // namespace arc
