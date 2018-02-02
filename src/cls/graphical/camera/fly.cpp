/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera/fly.hpp"



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
             *  Construct a fly camera for the graphical window.
             *
             *  @param  t_pos           Initial position of the camera.
             *  @param  t_aspect_ratio  Aspect ratio of the camera.
             *  @param  t_speed         Translational speed multiplier of the camera.
             *  @param  t_fov           Camera's field of view in degrees.
             */
            Fly::Fly(const glm::vec3& t_pos, const float t_aspect_ratio, float t_speed, float t_fov) :
                Camera(t_pos, t_aspect_ratio, t_speed, t_fov),
                m_azi(atan2f(n_dir[Y], n_dir[X])),
                m_dec(acosf(n_dir[Z] / sqrtf(math::square(n_dir[X]) + math::square(n_dir[Y]) + math::square(n_dir[Z]))))
            {
            }


            //  == METHODS ==
            //  -- Movement --
            /**
             *  Fly the camera around the scene using window input.
             *
             *  @param  t_translate Translation to be applied to the camera.
             *  @param  t_rotate    Translation to be applied to the camera.
             */
            void Fly::move(const glm::vec3& t_translate, const glm::vec2& t_rotate)
            {
                n_dir[X] = sinf(m_dec) * cosf(m_azi);
                n_dir[Y] = sinf(m_dec) * sinf(m_azi);
                n_dir[Z] = cosf(m_dec);

                glm::vec3 right(glm::normalize(glm::cross(n_dir, UP_DIR)));
                glm::vec3 up(glm::normalize(glm::cross(right, n_dir)));

                n_pos += ((t_translate[0] * n_dir) + (t_translate[1] * right) + (t_translate[2] * up)) * n_speed;

                m_azi += t_rotate[0];
                m_dec -= t_rotate[1];

                if (m_dec < 0.0f)
                {
                    m_dec = 0.01f;
                }
                else if (m_dec > 3.141f)
                {
                    m_dec = 3.141f;
                }

                n_view = glm::lookAt(n_pos, n_pos + n_dir, UP_DIR);
            }




        } // namespace camera
    } // namespace graphical
} // namespace arc
