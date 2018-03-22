/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/phys/material.hpp"



//  == INCLUDES ==
#include<iostream>
//  -- Utility --
#include "utl/vector.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a material from a set of optical property vectors.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_ref_index     Vector of corresponding refractive indices.
         *  @param  t_abs_coef      Vector of corresponding absorption coefficients.
         *  @param  t_scat_coef     Vector of corresponding scattering coefficients.
         *  @param  t_anisotropy    Vector of corresponding anisotropy values.
         *  @param  t_raman_coef    Vector of corresponding Raman scattering coefficients.
         *
         *  @post   t_wavelength vector must be in ascending order.
         *  @post   t_wavelength size must match t_ref_index size.
         *  @post   t_wavelength size must match t_abs_coef size.
         *  @post   t_wavelength size must match t_scat_coef size.
         *  @post   t_wavelength size must match t_anisotropy size.
         *  @post   t_ref_index must always be greater than zero.
         *  @post   t_abs_coef must always be greater than, or equal to, zero.
         *  @post   t_scat_coef must always be greater than zero.
         *  @post   t_anisotropy must always be greater than, or equal to, minus one.
         *  @post   t_anisotropy must always be less than, or equal to, one.
         *  @post   m_min_bound must be greater than zero.
         *  @post   m_min_bound must be smaller than m_max_bound.
         *  @post   t_raman_coef must always be greater than, or equal to, zero.
         */
        Material::Material(const std::vector<double>& t_wavelength, const std::vector<double>& t_ref_index,
                           const std::vector<double>& t_abs_coef, const std::vector<double>& t_scat_coef,
                           const std::vector<double>& t_anisotropy, const std::vector<double>& t_raman_coef) :
            m_min_bound(t_wavelength.front()),
            m_max_bound(t_wavelength.back()),
            m_ref_index(t_wavelength, t_ref_index),
            m_albedo(init_albedo(t_wavelength, t_abs_coef, t_scat_coef, t_raman_coef)),
            m_interaction(init_interation(t_wavelength, t_abs_coef, t_scat_coef, t_raman_coef)),
            m_anisotropy(t_wavelength, t_anisotropy)
        {
            assert(utl::is_ascending(t_wavelength));
            assert(t_wavelength.size() == t_ref_index.size());
            assert(t_wavelength.size() == t_abs_coef.size());
            assert(t_wavelength.size() == t_scat_coef.size());
            assert(t_wavelength.size() == t_anisotropy.size());
            assert(utl::is_always_greater_than(t_ref_index, 0.0));
            assert(utl::is_always_greater_than_or_equal_to(t_abs_coef, 0.0));
            assert(utl::is_always_greater_than_or_equal_to(t_scat_coef, 0.0));
            assert(utl::is_always_greater_than_or_equal_to(t_anisotropy, -1.0));
            assert(utl::is_always_less_than_or_equal_to(t_anisotropy, 1.0));
            assert(m_min_bound > 0.0);
            assert(m_min_bound < m_max_bound);
            assert(utl::is_always_greater_than_or_equal_to(t_raman_coef, 0.0));
        }

        /**
         *  Construct a material from a set of a table of optical properties.
         *
         *  @param  t_tab   Table of optical properties.
         *
         *  @post   WAVELENGTH index column must have the correct title.
         *  @post   REF_INDEX index column must have the correct title.
         *  @post   ABS_COEF index column must have the correct title.
         *  @post   SCAT_COEF index column must have the correct title.
         *  @post   ANISOTROPY index column must have the correct title.
         */
        Material::Material(const data::Table& t_tab) :
            Material(t_tab[WAVELENGTH].get_data(), t_tab[REF_INDEX].get_data(), t_tab[ABS_COEF].get_data(),
                     t_tab[SCAT_COEF].get_data(), t_tab[ANISOTROPY].get_data(), t_tab[RAMAN_COEF].get_data())
        {
            assert(t_tab[WAVELENGTH].get_title() == "w");
            assert(t_tab[REF_INDEX].get_title() == "n");
            assert(t_tab[ABS_COEF].get_title() == "a");
            assert(t_tab[SCAT_COEF].get_title() == "s");
            assert(t_tab[ANISOTROPY].get_title() == "g");
            assert(t_tab[RAMAN_COEF].get_title() == "r");
        }

        /**
         *  Construct a material from a serialised material object.
         *
         *  @param  t_serial    Serialised form of a material object.
         */
        Material::Material(const std::string& t_serial) :
            Material(data::Table(t_serial))
        {
        }


        //  -- Initialisation --
        /**
         *  Construct the interaction interpolator by calculating the interaction coefficients from the absorption and
         *  scattering length coefficients.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_abs_coef      Vector of corresponding absorption coefficients.
         *  @param  t_scat_coef     Vector of corresponding scattering coefficients.
         *  @param  t_raman_coef    Vector of corresponding Raman scattering coefficients.
         *
         *  @post   t_wavelength size must match t_abs_coef size.
         *  @post   t_wavelength size must match t_scat_coef size.
         *  @post   t_wavelength size must match t_raman_coef size.
         *
         *  @return The initialised interaction linear interpolator.
         */
        interpolator::Linear Material::init_interation(const std::vector<double>& t_wavelength,
                                                       const std::vector<double>& t_abs_coef,
                                                       const std::vector<double>& t_scat_coef,
                                                       const std::vector<double>& t_raman_coef) const
        {
            assert(t_wavelength.size() == t_abs_coef.size());
            assert(t_wavelength.size() == t_scat_coef.size());
            assert(t_wavelength.size() == t_raman_coef.size());

            // Create interaction value vector.
            std::vector<double> interaction(t_wavelength.size());

            // Calculate the interaction coefficient values.
            for (size_t i = 0; i < t_wavelength.size(); ++i)
            {
                interaction[i] = t_abs_coef[i] + t_scat_coef[i] + t_raman_coef[i];
            }

            return (interpolator::Linear(t_wavelength, interaction));
        }

        /**
         *  Construct the albedo interpolator by calculating the albedo from the absorption and scattering coefficients.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_abs_coef      Vector of corresponding absorption coefficients.
         *  @param  t_scat_coef     Vector of corresponding scattering coefficients.
         *  @param  t_raman_coef    Vector of corresponding Raman scattering coefficients.
         *
         *  @post   t_wavelength size must match t_abs_coef size.
         *  @post   t_wavelength size must match t_scat_coef size.
         *  @post   t_wavelength size must match t_raman_coef size.
         *
         *  @return The initialised interaction linear interpolator.
         */
        interpolator::Linear Material::init_albedo(const std::vector<double>& t_wavelength,
                                                   const std::vector<double>& t_abs_coef,
                                                   const std::vector<double>& t_scat_coef,
                                                   const std::vector<double>& t_raman_coef) const
        {
            assert(t_wavelength.size() == t_abs_coef.size());
            assert(t_wavelength.size() == t_scat_coef.size());
            assert(t_wavelength.size() == t_raman_coef.size());

            // Create albedo value vector.
            std::vector<double> albedo(t_wavelength.size());

            // Calculate the albedo values.
            for (size_t i = 0; i < t_wavelength.size(); ++i)
            {
                albedo[i] = 1.0 - (t_abs_coef[i] / (t_abs_coef[i] + t_scat_coef[i] + t_raman_coef[i]));
            }

            return (interpolator::Linear(t_wavelength, albedo));
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get the refractive index of the material for the given wavelength.
         *
         *  @param  t_wavelength    Wavelength to determine the refractive index for.
         *
         *  @pre    t_wavelength must be greater than, or equal to, the m_min_bound.
         *  @pre    t_wavelength must be less than, or equal to, the m_max_bound.
         *
         *  @return The refractive index for the given wavelength.
         */
        double Material::get_ref_index(const double t_wavelength) const
        {
            assert(t_wavelength >= m_min_bound);
            assert(t_wavelength <= m_max_bound);

            return (m_ref_index(t_wavelength));
        }

        /**
         *  Get the single scattering albedo of the material for the given wavelength.
         *
         *  @param  t_wavelength    Wavelength to determine the single scattering albedo for.
         *
         *  @pre    t_wavelength must be greater than, or equal to, the m_min_bound.
         *  @pre    t_wavelength must be less than, or equal to, the m_max_bound.
         *
         *  @return The single scattering albedo for the given wavelength.
         */
        double Material::get_albedo(const double t_wavelength) const
        {
            assert(t_wavelength >= m_min_bound);
            assert(t_wavelength <= m_max_bound);

            return (m_albedo(t_wavelength));
        }

        /**
         *  Get the interaction length coefficient of the material for the given wavelength.
         *
         *  @param  t_wavelength    Wavelength to determine the interaction length coefficient for.
         *
         *  @pre    t_wavelength must be greater than, or equal to, the m_min_bound.
         *  @pre    t_wavelength must be less than, or equal to, the m_max_bound.
         *
         *  @return The interaction length coefficient for the given wavelength.
         */
        double Material::get_interaction(const double t_wavelength) const
        {
            assert(t_wavelength >= m_min_bound);
            assert(t_wavelength <= m_max_bound);

            return (m_interaction(t_wavelength));
        }

        /**
         *  Get the anisotropy value of the material for the given wavelength.
         *
         *  @param  t_wavelength    Wavelength to determine the anisotropy value for.
         *
         *  @pre    t_wavelength must be greater than, or equal to, the m_min_bound.
         *  @pre    t_wavelength must be less than, or equal to, the m_max_bound.
         *
         *  @return The anisotropy value for the given wavelength.
         */
        double Material::get_anisotropy(const double t_wavelength) const
        {
            assert(t_wavelength >= m_min_bound);
            assert(t_wavelength <= m_max_bound);

            return (m_anisotropy(t_wavelength));
        }



    } // namespace phys
} // namespace arc
