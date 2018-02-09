/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/phys/spectrum.hpp"



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
         *  Construct a spectrum from a vector of wavelengths and associated probabilities.
         *
         *  @param  t_wavelength    Vector of wavelength values.
         *  @param  t_prob          Vector of corresponding probabilities.
         *
         *  @post   t_wavelength vector must be in ascending order.
         *  @post   t_wavelength front element must be greater than zero.
         *  @post   t_wavelength front element must be smaller than the back element.
         *  @post   t_wavelength vector must be the same size as t_prob vector.
         *  @post   t_prop vector must always be greater than zero.
         */
        Spectrum::Spectrum(const std::vector<double>& t_wavelength, const std::vector<double>& t_prob) :
            m_min_bound(t_wavelength.front()),
            m_max_bound(t_wavelength.back()),
            m_dist(t_wavelength, t_prob)
        {
            assert(utl::is_ascending(t_wavelength));
            assert(t_wavelength.front() > 0.0);
            assert(t_wavelength.front() < t_wavelength.back());
            assert(t_wavelength.size() == t_prob.size());
            assert(utl::is_always_greater_than(t_prob, 0.0));
        }

        /**
         *  Construct a spectrum from a set of a table of spectral data.
         *
         *  @param  t_tab   Table of spectral data.
         *
         *  @post   WAVELENGTH index column must have the correct title.
         *  @post   PROBABILITY index column must have the correct title.
         */
        Spectrum::Spectrum(const data::Table& t_tab) :
            Spectrum(t_tab[WAVELENGTH].get_data(), t_tab[PROBABILITY].get_data())
        {
            assert(t_tab[WAVELENGTH].get_title() == "w");
            assert(t_tab[PROBABILITY].get_title() == "p");
        }

        /**
         *  Construct a spectrum from a serialised spectrum object.
         *
         *  @param  t_serial    Serialised form of a spectrum object.
         */
        Spectrum::Spectrum(const std::string& t_serial) :
            Spectrum(data::Table(t_serial))
        {
        }


        //  -- Initialisation --



    } // namespace phys
} // namespace arc
