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

        {
        }



    } // namespace phys
} // namespace arc
