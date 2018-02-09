/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/phys/material.hpp"



//  == INCLUDES ==
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
         *  @param  t_abs_length    Vector of corresponding absorption lengths.
         *  @param  t_scat_length   Vector of corresponding scattering lengths.
         *  @param  t_anisotropy    Vector of corresponding anisotropy values.
         *
         *  @post   t_wavelength size must match t_ref_index size.
         *  @post   t_wavelength size must match t_abs_length size.
         *  @post   t_wavelength size must match t_scat_length size.
         *  @post   t_wavelength size must match t_anisotropy size.
         *  @post   t_ref_index must always be greater than zero.
         *  @post   t_abs_length must always be greater than zero.
         *  @post   t_scat_length must always be greater than zero.
         *  @post   t_anisotropy must always be greater than, or equal to, minus one.
         *  @post   t_anisotropy must always be less than, or equal to, one.
         */
        Material::Material(const std::vector<double>& t_wavelength, const std::vector<double>& t_ref_index,
                           const std::vector<double>& t_abs_length, const std::vector<double>& t_scat_length,
                           const std::vector<double>& t_anisotropy) :
            m_min_bound(t_wavelength.front()),
            m_max_bound(t_wavelength.back()),
            m_ref_index(t_wavelength, t_ref_index),
            m_albedo(init_albedo(t_wavelength, t_abs_length, t_scat_length)),
            m_interaction(init_interation(t_wavelength, t_abs_length, t_scat_length)),
            m_anisotropy(t_wavelength, t_anisotropy)
        {
            assert(t_wavelength.size() == t_ref_index.size());
            assert(t_wavelength.size() == t_abs_length.size());
            assert(t_wavelength.size() == t_scat_length.size());
            assert(t_wavelength.size() == t_anisotropy.size());
            assert(utl::is_always_greater_than(t_ref_index, 0.0));
            assert(utl::is_always_greater_than(t_abs_length, 0.0));
            assert(utl::is_always_greater_than(t_scat_length, 0.0));
            assert(utl::is_always_greater_than_or_equal_to(t_anisotropy, -1.0));
            assert(utl::is_always_less_than_or_equal_to(t_anisotropy, 1.0));
        }

        /**
         *  Construct a material from a set of optical property vectors.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_ref_index     Vector of corresponding refractive indices.
         *  @param  t_abs_length    Vector of corresponding absorption lengths.
         *  @param  t_scat_length   Vector of corresponding scattering lengths.
         *  @param  t_anisotropy    Vector of corresponding anisotropy values.
         *
         *  @post   t_wavelength index column must have the correct title.
         *  @post   t_ref_index index column must have the correct title.
         *  @post   t_abs_length index column must have the correct title.
         *  @post   t_scat_length index column must have the correct title.
         *  @post   t_anisotropy index column must have the correct title.
         */
        Material::Material(const data::Table& t_tab) :
            Material(t_tab[WAVELENGTH].get_data(), t_tab[REF_INDEX].get_data(), t_tab[ABS_LENGTH].get_data(),
                     t_tab[SCAT_LENGTH].get_data(), t_tab[ANISOTROPY].get_data())
        {
            assert(t_tab[WAVELENGTH].get_title() == "w");
            assert(t_tab[REF_INDEX].get_title() == "n");
            assert(t_tab[ABS_LENGTH].get_title() == "a");
            assert(t_tab[SCAT_LENGTH].get_title() == "s");
            assert(t_tab[ANISOTROPY].get_title() == "g");
        }


        //  -- Initialisation --
        /**
         *  Construct the interaction interpolator by calculating the interaction length coefficients from the absorption and
         *  scattering length coefficients.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_abs_length    Vector of corresponding absorption lengths.
         *  @param  t_scat_length   Vector of corresponding scattering lengths.
         *
         *  @post   t_wavelength size must match t_abs_length size.
         *  @post   t_wavelength size must match t_scat_length size.
         *
         *  @return The initialised interaction linear interpolator.
         */
        interpolator::Linear Material::init_interation(const std::vector<double>& t_wavelength,
                                                       const std::vector<double>& t_abs_length,
                                                       const std::vector<double>& t_scat_length) const
        {
            assert(t_wavelength.size() == t_abs_length.size());
            assert(t_wavelength.size() == t_scat_length.size());

            // Create interaction value vector.
            std::vector<double> interaction(t_wavelength.size());

            // Calculate the interaction coefficient values.
            for (size_t i = 0; i < t_wavelength.size(); ++i)
            {
                interaction[i] = t_abs_length[i] + t_scat_length[i];
            }

            return (interpolator::Linear(t_wavelength, interaction));
        }

        /**
         *  Construct the albedo interpolator by calculating the albedo from the absorption and scattering length coefficients.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_abs_length    Vector of corresponding absorption lengths.
         *  @param  t_scat_length   Vector of corresponding scattering lengths.
         *
         *  @post   t_wavelength size must match t_abs_length size.
         *  @post   t_wavelength size must match t_scat_length size.
         *
         *  @return The initialised interaction linear interpolator.
         */
        interpolator::Linear Material::init_albedo(const std::vector<double>& t_wavelength,
                                                   const std::vector<double>& t_abs_length,
                                                   const std::vector<double>& t_scat_length) const
        {
            assert(t_wavelength.size() == t_abs_length.size());
            assert(t_wavelength.size() == t_scat_length.size());

            // Create albedo value vector.
            std::vector<double> albedo(t_wavelength.size());

            // Calculate the albedo values.
            for (size_t i = 0; i < t_wavelength.size(); ++i)
            {
                albedo[i] = t_abs_length[i] / (t_abs_length[i] + t_scat_length[i]);
            }

            return (interpolator::Linear(t_wavelength, albedo));
        }



    } // namespace phys
} // namespace arc
