/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP



//  == BASE CLASS ==
#include "cls/graphical/camera.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace camera
        {



            //  == CLASS ==
            /**
             *  A specialised camera with fly controls.
             */
            class Fly : public Camera
            {
                //  == FIELDS ==
              private:
                //  -- Orientation --
                float m_azi;    //! Rotation of the camera around its local z-axis.
                float m_dec;    //! Declination of the camera form its local z-axis.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --



                //  == METHODS ==
              private:
            };



        } // namespace camera
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP
