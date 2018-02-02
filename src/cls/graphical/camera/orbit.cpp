/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera/orbit.hpp"



//  == INCLUDES ==
//  -- System --
#include "gen/enum.hpp"
#include "gen/math.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace camera
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct an orbit camera for the graphical window.
             *
             *  @param  t_pos           Initial position of the camera.
             *  @param  t_aspect_ratio  Aspect ratio of the camera.
             *  @param  t_speed         Translational speed multiplier of the camera.
             *  @param  t_fov           Camera's field of view in degrees.
             */
            Orbit::Orbit(const glm::vec3& t_pos, const float t_aspect_ratio, float t_speed, float t_fov) :
                Camera(t_pos, t_aspect_ratio, t_speed, t_fov),
                m_azi(atan2f(n_pos[Y], n_pos[X])),
                m_dec(acosf(n_pos[Z] / sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z])))),
                m_rho(sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z]))),
                m_azi_spin(0.0f)
            {
            }



        } // namespace camera
    } // namespace graphical
} // namespace arc
