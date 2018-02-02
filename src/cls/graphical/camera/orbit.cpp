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
            Orbit::Orbit(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_speed, const float t_fov) :
                Camera(t_pos, t_aspect_ratio, t_speed, t_fov),
                m_azi(atan2f(n_pos[Y], n_pos[X])),
                m_dec(acosf(n_pos[Z] / sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z])))),
                m_rho(sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z]))),
                m_azi_spin(0.0f)
            {
            }



            //  == METHODS ==
            //  -- Movement --
            /**
             *  Orbit the camera around the scene using window input.
             *
             *  @param  t_translate Translation to be applied to the camera.
             *  @param  t_rotate    Translation to be applied to the camera.
             */
            void Orbit::move(const glm::vec3& t_translate, const glm::vec2& t_rotate)
            {
                m_azi_spin += (t_rotate[0] * 0.01f);

                m_azi += t_translate[1] + m_azi_spin;
                m_dec += t_translate[0];
                m_rho -= t_translate[2];

                if (m_dec < 0.0f)
                {
                    m_dec = 0.01f;
                }
                else if (m_dec > 3.141f)
                {
                    m_dec = 3.141f;
                }

                n_pos[X] = m_rho * sinf(m_dec) * cosf(m_azi);
                n_pos[Y] = m_rho * sinf(m_dec) * sinf(m_azi);
                n_pos[Z] = m_rho * cosf(m_dec);

                n_dir = -glm::normalize(n_pos);

                n_view = glm::lookAt(n_pos, n_pos + n_dir, UP_DIR);
            }



        } // namespace camera
    } // namespace graphical
} // namespace arc
