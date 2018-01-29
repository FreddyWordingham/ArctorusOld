/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP



//  == INCLUDES ==
//  -- System --
#include <GL/glew.h>
#include <GLFW/glfw3.h>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == SETTINGS ==
        //  -- Window --
        constexpr const int WIDTH  = 800;           //! Width of the window in pixels.
        constexpr const int HEIGHT = 600;           //! Height of the window in pixels.
        constexpr const char* TITLE = "Arctorus";   //! Window title.
        constexpr const int AA_SAMPLES = 4;         //! Number of anti-aliasing samples.



        //  == CLASS ==
        /**
         *  Graphical scene class.
         *  Used to display graphical simulation data.
         */
        class Scene
        {
            //  == FIELDS ==
          private:
            //  -- Window Handle --
            GLFWwindow* m_window;   //! Handle to the main graphical window.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Scene();

            //  -- Destructors --
            ~Scene();

          private:
            //  -- Initialisation --
            GLFWwindow* init_window() const;


            //  == METHODS ==
          public:
            //  -- Input --
            bool should_close() const;
            bool handle_input();

            //  -- Render --
            void render() const;
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
