/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   30/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_CAMERA_ORBIT_HPP
#define ARCTORUS_SRC_CLS_CAMERA_ORBIT_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace camera
    {



        //  == CLASS ==
        /**
         *  A specialised camera with orbit controls.
         */
        class Orbit
        {
            //  == FIELDS ==
          private:
            //  -- Orientation --
            float m_azi;    //! Rotation of the camera around the global z-axis.
            float m_dec;    //! Declination of the camera form the global z-axis.
            float m_rho;    //! Distance of the camera from the origin.

            //  -- Travel --
            float m_spin_rate;  //! Rate of continuous rotation of the camera about the global z-axis.


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
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_CAMERA_ORBIT_HPP
