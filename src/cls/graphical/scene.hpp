/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP



//  == INCLUDES ==
//  -- System --
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//  -- Classes --
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/graphical/camera.hpp"
#include "cls/graphical/prop.hpp"
#include "cls/graphical/prop/light.hpp"
#include "cls/graphical/shader/ambient.hpp"
#include "cls/graphical/shader/diffuse.hpp"
#include "cls/graphical/shader/normal.hpp"
#include "cls/graphical/shader/path.hpp"
#include "cls/graphical/shader/skybox.hpp"
#include "cls/tree/cell.hpp"



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
        constexpr const float INIT_CAM_POS_X = +0.0e-3f;    //! Initial x-axis displacement of the camera.
        constexpr const float INIT_CAM_POS_Y = -5.0e-3f;    //! Initial y-axis displacement of the camera.
        constexpr const float INIT_CAM_POS_Z = +5.0e-3f;    //! Initial z-axis displacement of the camera.

        //  -- Lighting --
        constexpr const float INIT_SUN_POS_X             = +3.0f;   //! Initial x-axis displacement of the global illuminator.
        constexpr const float INIT_SUN_POS_Y             = +0.0f;   //! Initial y-axis displacement of the global illuminator.
        constexpr const float INIT_SUN_POS_Z             = +3.0f;   //! Initial z-axis displacement of the global illuminator.
        constexpr const float SUN_SIZE                   = 0.25f;   //! Size of the sun.
        constexpr const float LIGHT_AMB_POW              = 0.5f;    //! Ambient lighting of rendered light sources.
        constexpr const float ENTITY_AMB_POW             = 0.1f;    //! Ambient lighting of rendered entities.
        constexpr const float CCD_AMB_POW                = 0.6f;    //! Ambient lighting of rendered ccds.
        constexpr const float SPECTROMETER_AMB_POW       = 0.6f;    //! Ambient lighting of rendered spectrometers.
        constexpr const float LIGHT_NORMAL_LENGTH_MULT   = 1e-3f;   //! Multiplier to apply to drawn light normals.
        constexpr const float ENTITY_NORMAL_LENGTH       = 0.5e-3f; //! Length to draw entity normals.
        constexpr const float CCD_NORMAL_LENGTH          = 0.5e-3f; //! Length to draw ccd normals.
        constexpr const float SPECTROMETER_NORMAL_LENGTH = 0.5e-3f; //! Length to draw spectrometer normals.

        //  -- Rendering --
        constexpr const float  PHOTON_TRAVEL_SPEED    = 1e-11f; //! Photon travel speed when rendering path data.
        constexpr const double LIGHT_START_HUE        = 30.0;   //! Light prop start hue.
        constexpr const double LIGHT_END_HUE          = 60.0;   //! Light prop end hue.
        constexpr const double ENTITY_START_HUE       = 300.0;  //! Entity prop start hue.
        constexpr const double ENTITY_END_HUE         = 330.0;  //! Entity prop end hue.
        constexpr const double CCD_START_HUE          = 120.0;  //! Ccd prop start hue.
        constexpr const double CCD_END_HUE            = 150.0;  //! Ccd prop end hue.
        constexpr const double SPECTROMETER_START_HUE = 165.0;  //! Spectrometer prop start hue.
        constexpr const double SPECTROMETER_END_HUE   = 195.0;  //! Spectrometer prop end hue.



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
            const GLuint m_cubemap;     //! Handle to the loaded cubemap texture.
            const Prop   m_cube_box;    //! Prop holding the cubemap box.

            //  -- Cameras --
            std::unique_ptr<Camera> m_primary_cam;      //! Primary camera used to view the scene.
            std::unique_ptr<Camera> m_secondary_cam;    //! Secondary camera to be swapped with the primary camera.

            //  -- Illumination --
            glm::vec3  m_sun_pos;   //! Position of the global illuminator object.
            const Prop m_sun;       //! Drawable sun illuminator object.

            //  -- Props --
            std::vector<Prop>        m_entity;          //! Vector of entity props.
            std::vector<prop::Light> m_light;           //! Vector of light source props.
            std::vector<Prop>        m_ccd;             //! Vector of ccd props.
            std::vector<Prop>        m_spectrometer;    //! Vector of spectrometer props.
            std::vector<Prop>        m_phot;            //! Vector of photon packet path props.
            std::vector<Prop>        m_grid;            //! Vector of grid props.
            std::vector<Prop>        m_cell;            //! Vector of cell props.

            //  -- Toggles --
            bool m_toggle_filled_tris   = true;     //! When true render triangles as filled.
            bool m_toggle_light_normal  = false;    //! When true render light prop normals.
            bool m_toggle_photon_render = true;     //! When true render photon paths.
            bool m_toggle_cell_render   = false;    //! When true render the grid cells.

            //  -- Rendering --
            float m_render_time = 0.0f; //! Photon rendering time.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Scene(const Scene& /*unused*/) = delete;
            Scene(const Scene&& /*unused*/) = delete;
            Scene();

            //  -- Destructors --
            ~Scene();

          private:
            //  -- Initialisation --
            GLFWwindow* init_window() const;
            GLuint init_cubemap() const;


            //  == OPERATORS ==
          public:
            //  -- Copy --
            Scene& operator=(const Scene& /*unused*/) = delete;
            Scene& operator=(const Scene&& /*unused*/) = delete;


            //  == METHODS ==
          public:
            //  -- Render --
            void render() const;

            //  -- Additions --
            void add_light_vector(const std::vector<equip::Light>& t_light);
            void add_entity_vector(const std::vector<equip::Entity>& t_ent);
            void add_ccd_vector(const std::vector<detector::Ccd>& t_ccd);
            void add_spectrometer_vector(const std::vector<detector::Spectrometer>& t_spectrometer);
            void add_photon_vector(const std::vector<std::vector<point::Photon>>& t_phot);
            void add_tree(const std::unique_ptr<tree::Cell>& t_tree);

            //  -- Control --
            bool should_close() const;
            void handle_input();

          private:
            //  -- Additions --
            void add_entity(const equip::Entity& t_ent, const glm::vec4& t_col);
            void add_light(const equip::Light& t_light, const glm::vec4& t_col);
            void add_ccd(const detector::Ccd& t_ccd, const glm::vec4& t_col);
            void add_spectrometer(const detector::Spectrometer& t_spectrometer, const glm::vec4& t_col);
            void add_photon(const std::vector<point::Photon>& t_phot, const glm::vec4& t_col);
            void add_cell(const std::unique_ptr<tree::Cell>& t_cell, const double t_max_energy_density);

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
            void draw_entities() const;
            void draw_lights() const;
            void draw_ccds() const;
            void draw_spectrometers() const;
            void draw_phots() const;
            void draw_grid() const;
            void draw_sun() const;
            void draw_skybox() const;

            //  -- Utility --
            glm::vec3 hsv_to_rgb(float t_hue, float t_sat, float t_value) const;
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP



//  == MODULE END ==
#endif
