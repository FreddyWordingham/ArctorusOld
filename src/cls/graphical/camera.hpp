/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP



//  == INCLUDES ==
//  -- System --
#include <glm/glm.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == SETTINGS ==
        //  -- Defaults --
        constexpr const float DEFAULT_SPEED = 1.0f;     //! Default speed multiplier for the camera.
        constexpr const float DEFAULT_FOV   = 90.0f;    //! Default field of view for the camera.

        //  -- Camera Properties --
        constexpr const float UP_DIR_X       = 0.0f;    //! Camera up direction x component.
        constexpr const float UP_DIR_Y       = 0.0f;    //! Camera up direction y component.
        constexpr const float UP_DIR_Z       = 1.0f;    //! Camera up direction z component.
        constexpr const float NEAR_CULL_DIST = 1E-3f;   //! Near culling distance.
        constexpr const float FAR_CULL_DIST  = 1E+3f;   //! Far culling distance.



        //  == CLASS ==
        /**
         *  An abstract base class for cameras used to view scene data.
         */
        class Camera
        {
            //  == FIELDS ==
          protected:
            //  -- Positioning --
            glm::vec3 n_pos;    //! Position of the camera.
            glm::vec3 n_dir;    //! Direction of the camera.

            //  -- View --
            glm::mat4 n_model;  //! Model transformation matrix.
            glm::mat4 n_view;   //! View transformation matrix.
            glm::mat4 n_proj;   //! Projection transformation matrix.

            //  -- Properties --
            float n_speed;  //! Camera translation speed.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Camera(const Camera& /*unused*/) = delete;
            Camera(const Camera&& /*unused*/) = delete;
            Camera(const glm::vec3& t_pos, float t_aspect_ratio, float t_speed = DEFAULT_SPEED, float t_fov = DEFAULT_FOV);

          public:
            //  -- Destructors --
            virtual ~Camera() = default;


            //  == OPERATORS ==
          public:
            //  -- Copy --
            Camera& operator=(const Camera& /*unused*/) = delete;
            Camera& operator=(const Camera&& /*unused*/) = delete;


            //  == METHODS ==
          public:
            //  -- Getters --
            glm::vec3 get_pos() const { return (n_pos); }
            glm::vec3 get_dir() const { return (n_dir); }
            glm::mat4 get_view() const { return (n_view); }
            glm::mat4 get_proj() const { return (n_proj); }
            glm::mat4 get_mvp() const { return (n_proj * n_view * n_model); }

            //  -- Movement --
            virtual void move(const glm::vec3& t_translate, const glm::vec2& t_rotate) = 0;
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP



//  == MODULE END ==
#endif
