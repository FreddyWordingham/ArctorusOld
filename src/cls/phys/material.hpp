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
#include "cls/data/table.hpp"
#include "cls/interpolator/linear.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == SETTINGS ==
        //  -- Column Titles --
        constexpr const char* WAVELENGTH_TITLE  = "w"; //! Title string identifying the wavelength data column.
        constexpr const char* REF_INDEX_TITLE   = "n"; //! Title string identifying the refractive index data column.
        constexpr const char* ABS_LENGTH_TITLE  = "a"; //! Title string identifying the absorption length data column.
        constexpr const char* SCAT_LENGTH_TITLE = "s"; //! Title string identifying the scattering length data column.
        constexpr const char* ANISOTROPY_TITLE  = "g"; //! Title string identifying the anisotropy data column.



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
            explicit Material(const data::Table& t_table);

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
