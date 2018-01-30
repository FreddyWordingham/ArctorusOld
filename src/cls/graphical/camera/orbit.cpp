/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   30/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera/orbit.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/transform.hpp>

//  -- General --
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
             *  @param  t_fov           Camera's field of view in degrees.
             */
            Orbit::Orbit(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_fov) :
                Camera(t_pos, t_aspect_ratio, t_fov),
                m_azi(atan2f(n_pos[Y], n_pos[X])),
                m_dec(acosf(n_pos[Z] / sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z])))),
                m_rho(sqrtf(math::square(n_pos[X]) + math::square(n_pos[Y]) + math::square(n_pos[Z]))),
                m_spin_rate(0.0f)
            {
            }



            //  == METHODS ==
            //  -- Control --
            /**
             *  Orbit the camera around the scene using window input.
             *
             *  @param  t_trans Translation to be applied to the camera.
             *  @param  t_rot   Translation to be applied to the camera.
             */
            void Orbit::move(const glm::vec3& t_trans, const glm::vec2& t_rot)
            {
                m_spin_rate += (t_rot[0] * 0.01f);

                m_azi += t_trans[1] + m_spin_rate;
                m_dec += t_trans[0];
                m_rho -= t_trans[2];

                if (m_dec < 0.0f)
                {
                    m_dec = 0.01f;
                }
                else if (m_dec > 3.14f)
                {
                    m_dec = 3.14f;
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
