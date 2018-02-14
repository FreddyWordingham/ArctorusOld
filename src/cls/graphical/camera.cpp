/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/transform.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a new camera at a given position, with a given aspect ratio and field of view.
         *
         *  @param  t_pos           Initial position of the camera.
         *  @param  t_aspect_ratio  Aspect ratio of the camera.
         *  @param  t_speed         Translational speed multiplier of the camera.
         *  @param  t_fov           Camera's field of view in degrees.
         */
        Camera::Camera(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_speed, const float t_fov) :
            n_pos(t_pos),
            n_dir(-glm::normalize(t_pos)),
            n_model(glm::mat4(1.0f)),
            n_view(glm::lookAt(n_pos, n_pos + n_dir, glm::vec3(UP_DIR_X, UP_DIR_Y, UP_DIR_Z))),
            n_proj(glm::perspective(glm::radians(t_fov), t_aspect_ratio, NEAR_CULL_DIST, FAR_CULL_DIST)),
            n_speed(t_speed)
        {
        }



    } // namespace graphical
} // namespace arc
