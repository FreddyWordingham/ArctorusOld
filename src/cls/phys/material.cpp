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
         *  Construct a material object from a data table.
         *
         *  @param  t_table Data table to construct the material from.
         */
        Material::Material(const data::Table& t_table) :
            m_min_bound(t_table[WAVELENGTH].front()),
            m_max_bound(t_table[WAVELENGTH].back()),
            m_ref_index(t_table[WAVELENGTH], t_table[REF_INDEX]),
            m_interaction(init_interation(t_table[WAVELENGTH], t_table[ABS_LENGTH], t_table[SCAT_LENGTH])),
            m_albedo(init_albedo(t_table[WAVELENGTH], t_table[ABS_LENGTH]), t_table[SCAT_LENGTH]),
            m_anisotropy(t_table[WAVELENGTH], t_table[ANISOTROPY])
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
