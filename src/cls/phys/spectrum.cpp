/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/phys/spectrum.hpp"



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
         *  Construct a spectrum from a vector of wavelengths and associated probabilities.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_prob          Vector of corresponding probabilities.
         *
         *  @post   t_wavelength vector must be the same size as t_prob vector.
         */
        Spectrum::Spectrum(const std::vector<double>& t_wavelength, const std::vector<double>& t_prob) :
            m_dist(t_wavelength, t_prob)
        {
            assert(t_wavelength.size() == t_prob.size());
        }

        /**
         *  Construct a spectrum from a set of optical property vectors.
         *
         *  @param  t_tab   Table of optical properties.
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



    } // namespace phys
} // namespace arc
