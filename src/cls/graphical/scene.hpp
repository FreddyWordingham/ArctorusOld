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
#include <memory>

//  -- Classes --
#include "cls/graphical/camera.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == SETTINGS ==
        //  -- Window --
        constexpr const int WIDTH  = 800;                   //! Width of the window in pixels.
        constexpr const int HEIGHT = 600;                   //! Height of the window in pixels.
        constexpr const char* TITLE = "Arctorus";           //! Window title.
        constexpr const int   AA_SAMPLES         = 4;       //! Number of anti-aliasing samples.
        constexpr const float CLEAR_COLOUR_RED   = 0.0f;    //! Window red clear colour.
        constexpr const float CLEAR_COLOUR_GREEN = 0.0f;    //! Window green clear colour.
        constexpr const float CLEAR_COLOUR_BLUE  = 0.0f;    //! Window blue clear colour.
        constexpr const float CLEAR_COLOUR_ALPHA = 0.0f;    //! Window alpha clear colour.

        //  -- Camera --
        constexpr const glm::vec3 INIT_CAM_POS({+10.0f, +10.0f, +10.0f});   //! Initial position of the camera.

        //  -- Shaders --
        constexpr const char* AMBIENT_VERT_SHADER = "res/shaders/ambient.vert"; //! Path to ambient vertex shader.
        constexpr const char* AMBIENT_FRAG_SHADER = "res/shaders/ambient.frag"; //! Path to ambient fragment shader.
        constexpr const char* DIFFUSE_VERT_SHADER = "res/shaders/diffuse.vert"; //! Path to diffuse vertex shader.
        constexpr const char* DIFFUSE_FRAG_SHADER = "res/shaders/diffuse.frag"; //! Path to diffuse fragment shader.



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

            //  -- Cameras --
            std::unique_ptr<Camera> m_primary_cam;  //! Primary camera used to view the scene.


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
            void handle_input();

            //  -- Render --
            void render() const;

        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
