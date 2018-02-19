/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP
#define ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == CLASS ==
        /**
         *  Photon packet class.
         */
        class Photon
        {
            //  == FIELDS ==
          private:
            //  -- Spatial --
            math::Vec<3> n_pos;     //! Position of the particle.
            math::Vec<3> n_dir;     //! Direction of travel.
            double       n_weight;  //! Statistical weight of the particle.

            //  -- Optical --
            const double m_wavelength;  //! Wavelength of the photon packet.
            double       m_ref_index;         //! Current refractive index.
            double       m_albedo;            //! Current albedo.
            double       m_interaction;       //! Current interaction coefficient.
            double       m_anisotropy;        //! Current anisotropy value.


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



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP
