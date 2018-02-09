/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_SPECTRUM_HPP
#define ARCTORUS_SRC_CLS_PHYS_SPECTRUM_HPP



//  == INCLUDES ==
//  -- System --
#include "cls/data/table.hpp"
#include "cls/random/linear.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == CLASS ==
        /**
         *  Light spectrum used to select photon wavelengths.
         */
        class Spectrum
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            const random::Linear m_dist;    //! Random number distribution generator.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Spectrum(const std::vector<double>& t_wavelength, const std::vector<double>& t_prob);
            explicit Spectrum(const data::Table& t_tab);

            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_SPECTRUM_HPP
