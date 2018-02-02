/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP



//  == INCLUDES ==
//  -- System --
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//  -- Classes --
#include "cls/graphical/camera.hpp"
#include "cls/graphical/shader/ambient.hpp"
#include "cls/graphical/prop.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == SETTINGS ==
        //  -- Window --
        constexpr const int WIDTH  = 1600;                  //! Width of the window in pixels.
        constexpr const int HEIGHT = 1200;                  //! Height of the window in pixels.
        constexpr const char* TITLE = "Arctorus";           //! Window title.
        constexpr const int   AA_SAMPLES         = 4;       //! Number of anti-aliasing samples.
        constexpr const float CLEAR_COLOUR_RED   = 0.2f;    //! Window red clear colour.
        constexpr const float CLEAR_COLOUR_GREEN = 0.2f;    //! Window green clear colour.
        constexpr const float CLEAR_COLOUR_BLUE  = 0.2f;    //! Window blue clear colour.
        constexpr const float CLEAR_COLOUR_ALPHA = 0.2f;    //! Window alpha clear colour.

        //  -- Camera --
        constexpr const glm::vec3 INIT_CAM_POS({+10.0f, +10.0f, +10.0f});   //! Initial position of the camera.

        //  -- Shaders --
        constexpr const char* AMBIENT_GEOM_SHADER = "res/shaders/normal.geom"; //! Path to ambient geometry shader.
        constexpr const char* AMBIENT_VERT_SHADER = "res/shaders/normal.vert"; //! Path to ambient vertex shader.
        constexpr const char* AMBIENT_FRAG_SHADER = "res/shaders/normal.frag"; //! Path to ambient fragment shader.
        constexpr const char* DIFFUSE_VERT_SHADER = "res/shaders/diffuse.vert"; //! Path to diffuse vertex shader.
        constexpr const char* DIFFUSE_FRAG_SHADER = "res/shaders/diffuse.frag"; //! Path to diffuse fragment shader.

        //  -- Lighting --
        constexpr const glm::vec3 INIT_SUN_POS({-0.0f, -0.0f, +0.0f});      //! Initial position of the global illuminator.
        constexpr const float     SUN_SIZE        = 0.1f;                   //! Size of the sun.


        //  == CLASS ==
        /**
         *  Graphical window class.
         *  Used to visualise three-dimensional simulation data.
         */
        class Scene
        {
            //  == FIELDS ==
          private:
            //  -- Window Handle --
            GLFWwindow* m_window;   //! Handle to the main graphical window.

            //  -- Shaders --
            shader::Ambient m_ambient_shader;   //! Ambient lighting shader.

            //  -- Cameras --
            std::unique_ptr<Camera> m_primary_cam;      //! Primary camera used to view the scene.
            std::unique_ptr<Camera> m_secondary_cam;    //! Secondary camera to be swapped with the primary camera.

            //  -- Illumination --
            glm::vec3  m_sun_pos;   //! Position of the global illuminator object.
            const Prop m_sun;       //! Drawable sun illuminator object.


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
            //  -- Render --
            void render() const;

            //  -- Control --
            bool should_close() const;
            void handle_input();

          private:
            //  -- Control --
            void swap_camera();
            void move_camera(const float t_time_delta);

            //  -- Shader Setup --
            void setup_ambient_shader() const;

            //  -- Drawing --
            void draw_sun() const;
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
