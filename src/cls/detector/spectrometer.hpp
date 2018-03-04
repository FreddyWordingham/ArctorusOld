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
//  -- System --
#include <mutex>

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
            std::mutex      m_data_mutex;   //! Protects data.
            data::Histogram m_data;         //! Wavelength data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Spectrometer(const std::string& t_name, const geom::Mesh& t_mesh, double t_min_bound, double t_max_bound,
                         size_t t_num_bins);
            Spectrometer(const Spectrometer&& t_spectrometer);


            //  == METHODS ==
          public:
            //  -- Getters --
            const geom::Mesh& get_mesh() const { return (m_mesh); }

            //  -- Setters --
            void add_hit(double t_wavelength, double t_weight);

            //  -- Save --
            void save(const std::string& t_output_dir) const;
        };



    } // namespace detector
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DETECTOR_SPECTROMETER_HPP
