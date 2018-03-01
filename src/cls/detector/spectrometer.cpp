/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   26/02/2018.
 */



//  == HEADER ==
#include "cls/detector/spectrometer.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace detector
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a spectrometer using a given mesh and histogram properties.
         *
         *  @param  t_name      Name of the spectrometer.
         *  @param  t_mesh      Mesh to form the surface of the spectrometer.
         *  @param  t_min_bound Minimum bound of the spectrometer.
         *  @param  t_max_bound Maximum bound of the spectrometer.
         *  @param  t_num_bins  Number of spectrometer bins.
         *
         *  @pre    t_min_bound must be non-negative.
         *  @pre    t_min_bound must be less than t_max_bound.
         *  @pre    t_num_bins must be positive.
         */
        Spectrometer::Spectrometer(const std::string& t_name, const geom::Mesh& t_mesh, const double t_min_bound,
                                   const double t_max_bound, const size_t t_num_bins) :
            m_name(t_name),
            m_mesh(t_mesh),
            m_data(t_min_bound, t_max_bound, t_num_bins)
        {
            assert(t_min_bound >= 0.0);
            assert(t_min_bound < t_max_bound);
            assert(t_num_bins > 0);
        }



        //  == METHODS ==
        //  -- Setters --
        /**
         *  Add a hit to the spectrometer.
         *
         *  @param  t_wavelength    Wavelength to be binned.
         *  @param  t_weight        Statistical weight of the value.
         *
         *  @pre    t_wavelength must be non-negative.
         *  @pre    t_weight must be non-negative.
         */
        void Spectrometer::add_hit(const double t_wavelength, const double t_weight)
        {
            assert(t_wavelength >= 0.0);
            assert(t_weight >= 0.0);

            // Check if wavelength is outside of recorded range.
            if ((t_wavelength < m_data.get_min_bound()) || (t_wavelength > m_data.get_max_bound()))
            {
                return;
            }

            // Bin the value.
            m_data.bin_value(t_wavelength, t_weight);
        }


        //  -- Save --
        /**
         *  Save the state of the spectrometer.
         *
         *  @param  t_output_dir    Directory to write the images to.
         */
        void Spectrometer::save(const std::string& t_output_dir) const
        {
            m_data.save(t_output_dir + m_name + ".dat");
        }



    } // namespace detector
} // namespace arc
