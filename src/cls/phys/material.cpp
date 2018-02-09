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

        }

        interpolator::Linear Material::init_albedo(const std::vector<double>& t_wavelength,
                                                   const std::vector<double>& t_abs_length,
                                                   const std::vector<double>& t_scat_length) const
        {

        }



    } // namespace phys
} // namespace arc
