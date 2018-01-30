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
             *  Fly the camera around the scene using window input.
             *
             *  @param  t_trans Translation to be applied to the camera.
             *  @param  t_rot   Translation to be applied to the camera.
             */
            void Orbit::move(const glm::vec3& t_trans, const glm::vec2& t_rot)
            {
                n_dir[X] = sinf(m_dec) * cosf(m_azi);
                n_dir[Y] = sinf(m_dec) * sinf(m_azi);
                n_dir[Z] = cosf(m_dec);

                glm::vec3 right(glm::normalize(glm::cross(n_dir, UP_DIR)));
                glm::vec3 up(glm::normalize(glm::cross(right, n_dir)));

                n_pos += (t_trans[0] * n_dir) + (t_trans[1] * right) + (t_trans[2] * up);

                m_azi += t_rot[0];
                m_dec -= t_rot[1];

                if (m_dec < 0.0f)
                {
                    m_dec = 0.01f;
                }
                else if (m_dec > 3.14f)
                {
                    m_dec = 3.141f;
                }

                n_view = glm::lookAt(n_pos, n_pos + n_dir, UP_DIR);
            }



        } // namespace camera
    } // namespace graphical
} // namespace arc
