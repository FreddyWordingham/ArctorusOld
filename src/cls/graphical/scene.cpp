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

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/graphical/camera/fly.hpp"



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
            m_primary_cam(std::make_unique<camera::Fly>(INIT_CAM_POS, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))),
            m_ambient_shader(file::read(AMBIENT_VERT_SHADER, false), file::read(AMBIENT_FRAG_SHADER, false))
        {
            m_spotlight.push_back(Prop(Prop::shape::CUBE, glm::vec3({1.0, 0.0, 1.0}), 0.5));
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
            move_camera(time_delta);
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

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

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


        //  -- Movement --
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


        //  -- Drawing --
        /**
         *  Draw the spotlights within a scene.
         */
        void Scene::draw_spotlights() const
        {
            // Use the ambient shader.
            glUseProgram(m_ambient_shader.get_handle());

            // Set drawing mode.
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // Draw each spotlight.
            for (size_t i = 0; i < m_spotlight.size(); ++i)
            {
                glUniform3f(m_ambient_shader.get_prop_col(), 1.0f, 1.0f, 0.0f);

                glEnableVertexAttribArray(0);

                glBindVertexArray(m_spotlight[i].get_vao());

                glDrawArrays(GL_TRIANGLES, 0, m_spotlight[i].get_num_vert());

                glBindVertexArray(0);
            }
        }



    } // namespace graphical
} // namespace arc
