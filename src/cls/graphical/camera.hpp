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
        //  -- Defaults --
        constexpr const float CAM_SPEED          = 1.0f;    //! Default speed multiplier for the camera.
        constexpr const float CAM_FOV            = 45.0f;   //! Default field of view for the camera.

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


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_HPP
