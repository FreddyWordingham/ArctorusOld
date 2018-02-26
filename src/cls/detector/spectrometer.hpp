/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   26/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DETECTOR_SPECTROMETER_HPP
#define ARCTORUS_SRC_CLS_DETECTOR_SPECTROMETER_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/data/histogram.hpp"
#include "cls/geom/mesh.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace detector
    {



        //  == CLASS ==
        /**
         *  Spectrometer like detector.
         *  Stores information about photons hitting a mesh surface.
         */
        class Spectrometer
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const std::string m_name;   //! Name of the ccd.
            const geom::Mesh  m_mesh;   //! Mesh describing the surface of the detector.

            //  -- Data --
            data::Histogram m_data; //! Wavelength data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace detector
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DETECTOR_SPECTROMETER_HPP
