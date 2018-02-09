/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_MATERIAL_HPP
#define ARCTORUS_SRC_CLS_PHYS_MATERIAL_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/interpolator/linear.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == CLASS ==
        /**
         *  Material class used to store optical properties.
         */
        class Material
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const double m_min_bound;   //! Minimum bound of the interpolation range.
            const double m_max_bound;   //! Maximum bound of the interpolation range.

            //  -- Optical Properties --
            const interpolator::Linear m_ref_index;     //! Refractive index.
            const interpolator::Linear m_interaction;   //! Interaction coefficient. mu_t = mu_a + mu_s.
            const interpolator::Linear m_albedo;        //! Single scattering albedo. a = mu_a / mu_t.
            const interpolator::Linear m_anisotropy;    //! Anisotropy factor.


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
#endif // ARCTORUS_SRC_CLS_PHYS_MATERIAL_HPP
