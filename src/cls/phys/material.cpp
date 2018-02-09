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
