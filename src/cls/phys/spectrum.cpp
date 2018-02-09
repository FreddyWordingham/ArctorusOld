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


        //  -- Initialisation --



    } // namespace phys
} // namespace arc
