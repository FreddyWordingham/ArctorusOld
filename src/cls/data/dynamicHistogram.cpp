/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/03/2018.
 */



//  == HEADER ==
#include "cls/data/dynamicHistogram.hpp"



//  == INCLUDES ==
//  -- System --
#include <cassert>

//  -- Utility --
#include "utl/vector.hpp"

//  -- Classes --
#include "cls/data/column.hpp"
#include "cls/data/table.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a dynamic histogram with given initial collection bounds and a given number of evenly spaced bins.
         *
         *  @param  t_min_bound Minimum bound of the histogram range.
         *  @param  t_max_bound Maximum bound of the histogram range.
         *  @param  t_num_bins  Number of histogram bins.
         *
         *  @pre    t_max_bound must be greater than t_min_bound.
         *  @pre    t_num_bins must be greater than 0.
         */
        DynamicHistogram::DynamicHistogram(const double t_min_bound, const double t_max_bound, const size_t t_num_bins) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_bin_width((m_max_bound - m_min_bound) / t_num_bins),
            m_data(t_num_bins)
        {
            assert(t_max_bound > t_min_bound);
            assert(t_num_bins > 0);
        }



        //  == METHODS ==
        //  -- Serialisation --
        /**
         *  Create a string representation of the histogram.
         *
         *  @param  t_normalise When true, normalise the count data to a maximum of unity.
         *  @param  t_align     Alignment position of the bin.
         *
         *  @return A string representation of the histogram.
         */
        std::string DynamicHistogram::serialise(const bool t_normalise, const align t_align) const
        {
            std::stringstream stream;

            stream << Table(std::vector<Column>(
                {Column("bin", get_bin_pos(t_align)), Column("count", (t_normalise ? (m_data / utl::max(m_data)) : m_data))}));

            return (stream.str());
        }



    } // namespace data
} // namespace arc
