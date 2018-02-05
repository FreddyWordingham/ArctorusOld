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
#include "cls/geom/mesh.hpp"
#include "cls/graphical/camera.hpp"
#include "cls/graphical/prop.hpp"
#include "cls/graphical/prop/light.hpp"
#include "cls/graphical/shader/ambient.hpp"
#include "cls/graphical/shader/diffuse.hpp"
#include "cls/graphical/shader/normal.hpp"
#include "cls/graphical/shader/path.hpp"
#include "cls/graphical/shader/skybox.hpp"



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
        constexpr const float CLEAR_COLOUR_RED   = 1.0f;    //! Window red clear colour.
        constexpr const float CLEAR_COLOUR_GREEN = 0.0f;    //! Window green clear colour.
        constexpr const float CLEAR_COLOUR_BLUE  = 1.0f;    //! Window blue clear colour.
        constexpr const float CLEAR_COLOUR_ALPHA = 1.0f;    //! Window alpha clear colour.

        //  -- Skybox --
        constexpr const char* SKYBOX_DIR      = "res/skybox/nebula/";   //! Directory containing skybox images.
        constexpr const char* SKYBOX_FILE_EXT = ".tga";                 //! File extension used by skybox images.

        //  -- Camera --
        constexpr const float INIT_CAM_POS_X = +0.0f;   //! Initial x-axis displacement of the camera.
        constexpr const float INIT_CAM_POS_Y = -5.0f;   //! Initial y-axis displacement of the camera.
        constexpr const float INIT_CAM_POS_Z = +5.0f;   //! Initial z-axis displacement of the camera.

        //  -- Lighting --
        constexpr const float INIT_SUN_POS_X = +3.0f;   //! Initial x-axis displacement of the global illuminator.
        constexpr const float INIT_SUN_POS_Y = +0.0f;   //! Initial y-axis displacement of the global illuminator.
        constexpr const float INIT_SUN_POS_Z = +3.0f;   //! Initial z-axis displacement of the global illuminator.
        constexpr const float SUN_SIZE       = 0.25f;   //! Size of the sun.
        constexpr const float LIGHT_AMB_POW  = 0.5f;    //! Ambient lighting of rendered light sources.



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
            shader::Skybox  m_skybox_shader;    //! Skybox shader.
            shader::Ambient m_ambient_shader;   //! Ambient lighting shader.
            shader::Diffuse m_diffuse_shader;   //! Diffuse lighting shader.
            shader::Normal  m_normal_shader;    //! Normal shader.
            shader::Path    m_path_shader;      //! Path shader.

            //  -- Cubemap --
            const GLuint m_cubemap; //! Handle to the loaded cubemap texture.
            const Prop   m_cube_box;  //! Prop holding the cubemap box.

            //  -- Cameras --
            std::unique_ptr<Camera> m_primary_cam;      //! Primary camera used to view the scene.
            std::unique_ptr<Camera> m_secondary_cam;    //! Secondary camera to be swapped with the primary camera.

            //  -- Illumination --
            glm::vec3  m_sun_pos;   //! Position of the global illuminator object.
            const Prop m_sun;       //! Drawable sun illuminator object.

            //  -- Props --
            std::vector<Prop>        m_entity;  //! Vector of entity props.
            std::vector<prop::Light> m_light;   //! Vector of light source props.
            std::vector<Prop>        m_phot;    //! Vector of photon packet path props.

            //  -- Toggles --
            bool m_toggle_filled_tris  = true;  //! When true render triangles as filled.
            bool m_toggle_light_normal = false; //! When true render light prop normals.

            //  -- Rendering --
            float m_render_dist = 0.0f; //! Photon rendering distance.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Scene();

            //  -- Destructors --
            ~Scene();

          private:
            //  -- Initialisation --
            GLFWwindow* init_window() const;
            GLuint init_cubemap() const;


            //  == METHODS ==
          public:
            //  -- Additions --
            void add_entity(const geom::Mesh& t_mesh, const glm::vec4& t_col);
            void add_light(const geom::Mesh& t_mesh, float t_power, const glm::vec4& t_col);
            void add_photon(const std::vector<point::Photon>& t_phot);

            //  -- Render --
            void render() const;

            //  -- Control --
            bool should_close() const;
            void handle_input();

          private:
            //  -- Control --
            void swap_camera();
            void move_camera(float t_time_delta);
            void move_sun(float t_time_delta);
            void toggle();
            void propagate_photons(float t_time_delta);

            //  -- Shader Setup --
            void setup_skybox_shader() const;
            void setup_ambient_shader() const;
            void setup_diffuse_shader() const;
            void setup_normal_shader() const;
            void setup_photon_shader() const;

            //  -- Drawing --
            void draw_lights() const;
            void draw_phots() const;
            void draw_sun() const;
            void draw_skybox() const;
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
