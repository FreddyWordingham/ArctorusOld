/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/phys/material.hpp"



//  == INCLUDES ==
//  -- System --



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
        }

        interpolator::Linear Material::init_interation(const std::vector<double>& t_wavelength,
                                                       const std::vector<double>& t_abs_length,
                                                       const std::vector<double>& t_scat_length) const
        {
            // Create interaction value vector.
            std::vector<double> interaction(t_wavelength.size());


            return (interpolator::Linear(t_wavelength, interaction));
        }

        interpolator::Linear Material::init_albedo(const std::vector<double>& t_wavelength,
                                                   const std::vector<double>& t_abs_length,
                                                   const std::vector<double>& t_scat_length) const
        {
            return (interpolator::Linear(t_wavelength, albedo));
        }



    } // namespace phys
} // namespace arc
