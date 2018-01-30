/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/camera.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/transform.hpp>

#include "gen/log.hpp"

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
         *  @param  t_fov           Camera's field of view in degrees.
         */
        Camera::Camera(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_fov) :
            n_pos(t_pos),
            n_dir(-glm::normalize(n_pos)),
            n_model(glm::mat4(1.0f)),
            n_view(glm::lookAt(n_pos, n_pos + n_dir, UP_DIR)),
            n_proj(glm::perspective(glm::radians(t_fov), t_aspect_ratio, NEAR_CULL_DIST, FAR_CULL_DIST))
        {
            VAL(t_fov);
            VAL(t_aspect_ratio);
            VAL(NEAR_CULL_DIST);
            VAL(FAR_CULL_DIST);
        }



    } // namespace graphical
} // namespace arc
