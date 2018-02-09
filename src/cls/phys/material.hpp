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



        //  == CLASS ==
        /**
         *  Material class used to store optical properties.
         */
        class Material
        {
            //  == ENUMERATIONS ==
          private:
            //  -- Format --
            /**
             *  Layout of the data columns within a material data table file.
             */
            enum mat_column_order
            {
                WAVELENGTH,     //! Index of the wavelength data column.
                REF_INDEX,      //! Index of the refractive index data column.
                ABS_LENGTH,     //! Index of the absorption length data column.
                SCAT_LENGTH,    //! Index of the scattering length data column.
                ANISOTROPY      //! Index of the anisotropy data column.
            };


            //  == FIELDS ==
          private:
            //  -- Bounds --
            const double m_min_bound;   //! Minimum bound of the interpolation range.
            const double m_max_bound;   //! Maximum bound of the interpolation range.

            //  -- Optical Properties --
            const interpolator::Linear m_ref_index;     //! Refractive index.
            const interpolator::Linear m_albedo;        //! Single scattering albedo. a = mu_a / mu_t.
            const interpolator::Linear m_interaction;   //! Interaction coefficient. mu_t = mu_a + mu_s.
            const interpolator::Linear m_anisotropy;    //! Anisotropy factor.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Material(const std::vector<double>& t_wavelength, const std::vector<double>& t_ref_index,
                     const std::vector<double>& t_abs_length, const std::vector<double>& t_scat_length,
                     const std::vector<double>& t_anisotropy);

          private:
            //  -- Initialisation --
            interpolator::Linear init_albedo(const std::vector<double>& t_wavelength, const std::vector<double>& t_abs_length,
                                             const std::vector<double>& t_scat_length) const;
            interpolator::Linear init_interation(const std::vector<double>& t_wavelength,
                                                 const std::vector<double>& t_abs_length,
                                                 const std::vector<double>& t_scat_length) const;


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_MATERIAL_HPP
