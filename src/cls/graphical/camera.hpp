/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



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
        //  -- Camera Properties --
        constexpr const glm::vec3 UP_DIR({0.0f, 0.0f, 1.0f});   //! Camera up direction.
        constexpr const float     NEAR_CULL_DIST = 1E-3f;       //! Near culling distance.
        constexpr const float     FAR_CULL_DIST  = 1E-3f;       //! Far culling distance.



        //  == CLASS ==
        /**
         *  An abstract base class for cameras which are used to view a 3D rendered scene.
         */
        class Camera
        {
            //  == FIELDS ==
          private:
            //  -- Positioning --
            glm::vec3 n_pos;    //! Position of the camera.
            glm::vec3 n_dir;    //! Direction of the camera.

            //  -- View --
            glm::mat4 n_model;  //! Model transformation matrix.
            glm::mat4 n_view;   //! View transformation matrix.
            glm::mat4 n_proj;   //! Projection transformation matrix.



            //  == INSTANTIATION ==
          protected:
            //  -- Constructors --
            Camera(const glm::vec3& t_pos, float t_aspect_ratio, float t_fov = 45.0f);

          public:
            //  -- Destructors --
            virtual ~Camera() = default;


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP
