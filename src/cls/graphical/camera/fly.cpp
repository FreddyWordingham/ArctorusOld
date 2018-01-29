/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera/fly.hpp"



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
             *  Construct a fly camera.
             *
             *  @param  t_pos           Initial position of the camera.
             *  @param  t_aspect_ratio  Aspect ratio of the camera.
             *  @param  t_fov           Camera's field of view in degrees.
             *
             *  @pre    t_fov must greater than zero and less than 180.
             */
            Fly::Fly(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_fov) :
                Camera(t_pos, t_aspect_ratio, t_fov),
                m_azi(atan2f(n_dir[Y], n_dir[X])),
                m_dec(acosf(n_dir[Z] / sqrtf(math::square(n_dir[X]) + math::square(n_dir[Y]) + math::square(n_dir[Z]))))
            {
                assert((t_fov > 0.0) && (t_fov < 180.0));
            }



            //  -- Initialisation --



        } // namespace camera
    } // namespace graphical
} // namespace arc
