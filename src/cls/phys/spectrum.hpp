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
            //  == ENUMERATIONS ==
          private:
            //  -- Format --
            /**
             *  Layout of the data columns within a spectral data table file.
             */
            enum spec_column_order
            {
                WAVELENGTH,     //! Index of the wavelength data column.
                PROBABILITY     //! Index of the probability data column.
            };


            //  == FIELDS ==
          private:
            //  -- Data --
            const random::Linear m_dist;    //! Random number distribution generator.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Spectrum(const std::vector<double>& t_wavelength, const std::vector<double>& t_prob);
            explicit Spectrum(const data::Table& t_tab);
            explicit Spectrum(const std::string& t_serial);


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_min_bound() const { return (m_dist.get_min_bound()); }
            double get_max_bound() const { return (m_dist.get_max_bound()); }

            //  -- Generation --
            double gen_wavelength() const { return (m_dist()); }
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_SPECTRUM_HPP
