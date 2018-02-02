/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  An abstract base class for cameras used to veiw scene data.
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

            //  -- Properties --
            float n_speed;  //! Camera translation speed.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Camera(const glm::vec3& t_pos, const float t_aspect_ratio, const float t_speed = 1.0, const float t_fov = 90.0f);


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP
