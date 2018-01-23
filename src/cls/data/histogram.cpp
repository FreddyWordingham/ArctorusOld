/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   23/01/2018.
 */



//  == HEADER ==
#include "cls/data/histogram.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a histogram with given collection bounds and a given number of evenly spaced bins.
         *
         *  @param  t_min_bound Minimum bound of the histogram range.
         *  @param  t_max_bound Maximum bound of the histogram range.
         *  @param  t_num_bins  Number of histogram bins.
         *
         *  @pre    t_max_bound must be greater than t_min_bound.
         *  @pre    t_num_bins must be greater than 0.
         */
        Histogram::Histogram(const double t_min_bound, const double t_max_bound, const size_t t_num_bins) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_bin_width(m_max_bound - m_min_bound / (t_num_bins - 1)),
            m_data(t_num_bins)
        {
            assert(t_max_bound > t_min_bound);
            assert(t_num_bins > 0);
        }



    } // namespace data
} // namespace arc
