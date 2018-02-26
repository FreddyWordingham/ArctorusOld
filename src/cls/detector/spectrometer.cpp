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
         */
        Spectrometer::Spectrometer(const std::string& t_name, const geom::Mesh& t_mesh, const double t_min_bound,
                                   const double t_max_bound, const size_t t_num_bins) :
            m_name(t_name),
            m_mesh(t_mesh),
            m_data(t_min_bound, t_max_bound, t_num_bins)
        {
            assert(t_min_bound < t_max_bound);
            assert(t_num_bins > 0);
        }



    } // namespace detector
} // namespace arc
