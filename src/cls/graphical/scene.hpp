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
#include "cls/geom/mesh.hpp"
#include "cls/graphical/camera.hpp"
#include "cls/graphical/prop.hpp"
#include "cls/graphical/shader/ambient.hpp"
#include "cls/graphical/shader/diffuse.hpp"
#include "cls/math/vec.hpp"



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
            std::unique_ptr<Camera> m_primary_cam;      //! Primary camera used to view the scene.
            std::unique_ptr<Camera> m_secondary_cam;    //! Secondary camera to be swapped with the primary camera.

            //  -- Shaders --
            shader::Ambient m_ambient_shader;   //! Ambient lighting shader.
            shader::Diffuse m_diffuse_shader;   //! Diffuse lighting shader.

            //  -- Props --
            std::vector<Prop> m_spotlight;  //! Vector of spotlight props.
            std::vector<Prop> m_entity;     //! Vector of entity props.


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

            //  -- Additions --
            void add_light(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_rad, double t_aperture,
                           double t_power);
            void add_entity(const geom::Mesh& t_mesh);

            //  -- Render --
            void render() const;

          private:
            //  -- Render --
            void setup_ambient_shader() const;
            void draw_spotlights() const;

            //  -- Control --
            void swap_camera();
            void move_camera(float t_time_delta);
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
