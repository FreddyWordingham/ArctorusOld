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
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
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
            glClearColor(0.7f, 0.1f, 0.5f, 1.0f);

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
/*            if (glfwGetKey(m_window, control::QUIT) == GLFW_PRESS)
            {
                return (true);
            }*/

            if (glfwWindowShouldClose(m_window) != 0)
            {
                return (true);
            }

            return (false);
        }


        //  -- Render --
        /**
         *  Render control function.
         *  Call sub-functions to render the objects within scene.
         */
        void Scene::render() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBegin(GL_POLYGON);
            glColor3f(0.50, 1.0, 0.0);
            glVertex2f(-1.0, -1.0);

            glVertex2f(-1.0, 10.0);

            glColor3f(01.01, 0.50, 1.0);
            glVertex2f(10.0, 10.0);

            glVertex2f(10.0, -1.0);

            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(1.0, 1.0);

            glVertex2f(7.0, 7.0);
            glEnd();

            glFlush();
        }



    } // namespace graphical
} // namespace arc
