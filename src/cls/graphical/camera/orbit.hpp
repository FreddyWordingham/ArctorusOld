/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP



//  == BASE CLASS ==
#include "cls/graphical/camera.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace camera
        {



            //  == CLASS ==
            /**
             *  A specialised camera with orbit controls.
             */
            class Orbit : public Camera
            {
                //  == FIELDS ==
              private:
                //  -- Orientation --
                float m_azi;    //! Rotation of the camera around the global z-axis.
                float m_dec;    //! Declination of the camera from the global z-axis.
                float m_rho;    //! Distance of the camera from the origin z-axis.


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



        } // namespace camera
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_ORBIT_HPP
