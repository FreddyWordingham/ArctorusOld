/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/scene.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



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
            m_window(init_window())
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
            /*if (glfwGetKey(m_window, control::QUIT) == GLFW_PRESS)
            {
                return (true);
            }*/

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
//            swap_camera();
//            move_camera(time_delta);
        }



    } // namespace graphical
} // namespace arc
