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
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP



//  == BASE CLASS ==
#include "cls/graphical/camera.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/glm.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace camera
        {



            //  == CLASS ==
            /**
             *  A specialised camera with orbit controls.
             */
            class Orbit : public Camera
            {
                //  == FIELDS ==
              private:
                //  -- Orientation --
                float m_azi;    //! Rotation of the camera around the global z-axis.
                float m_dec;    //! Declination of the camera from the global z-axis.
                float m_rho;    //! Distance of the camera from the origin z-axis.

                //  -- Movement --
                float m_azi_spin;   //! Rate of continuous rotation of the camera around the global z-axis.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Orbit(const glm::vec3& t_pos, float t_aspect_ratio, float t_speed = DEFAULT_SPEED, float t_fov = DEFAULT_FOV);


                //  == METHODS ==
              public:
                //  -- Movement --
                void move(const glm::vec3& t_translate, const glm::vec2& t_rotate) override;
            };



        } // namespace camera
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP



//  == MODULE END ==
#endif
