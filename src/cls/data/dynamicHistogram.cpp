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
#include <sstream>

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
         *  @pre    t_num_bins must be even.
         */
        DynamicHistogram::DynamicHistogram(const double t_min_bound, const double t_max_bound, const size_t t_num_bins) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_bin_width((m_max_bound - m_min_bound) / t_num_bins),
            m_data(t_num_bins)
        {
            assert(t_max_bound > t_min_bound);
            assert(t_num_bins > 0);
            assert((t_num_bins % 2) == 0);
        }



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of a histogram to a given ostream.
         *  Histogram is converted to a table before printing.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_hist      Histogram to be written.
         *
         *  @return A reference to the stream post-write.
         */
        std::ostream& operator<<(std::ostream& t_stream, const DynamicHistogram& t_hist)
        {
            t_stream << t_hist.serialise();

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Create a vector of bin positions.
         *
         *  @param  t_align Set bin alignment position to the left, middle, or right of the bin.
         *
         *  @return A vector of bin positions.
         */
        std::vector<double> DynamicHistogram::get_bin_pos(const align t_align) const
        {
            std::vector<double> r_pos(m_data.size());

            double offset = 0.0;
            switch (t_align)
            {
                case align::LEFT:
                    offset = 0.0;
                    break;
                case align::CENTER:
                    offset = 0.5;
                    break;
                case align::RIGHT:
                    offset = 1.0;
                    break;
            }

            for (size_t i = 0; i < r_pos.size(); ++i)
            {
                r_pos[i] = m_min_bound + ((i + offset) * m_bin_width);
            }

            return (r_pos);
        }


        //  -- Collection --
        /**
         *  Bin the given value within the histogram.
         *
         *  @param  t_val       Value to be binned.
         *  @param  t_weight    Weight of the value to be binned.
         *
         *  @pre    t_val must be within the bound limits.
         *  @pre    t_weight must be positive.
         */
        void DynamicHistogram::bin_value(double t_val, double t_weight)
        {
            assert((t_val >= m_min_bound) && (t_val <= m_max_bound));
            assert(t_weight > 0.0);

            const auto bin = static_cast<size_t>((t_val - m_min_bound) / m_bin_width);

            (bin == m_data.size()) ? m_data[bin - 1] += t_weight : m_data[bin] += t_weight;
        }



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


        //  -- Growth --
        /**
         *  Increase the max bound of the histogram's range.
         */
        void DynamicHistogram::ascend()
        {
            // Increase the maximum bound and bin width.
            m_max_bound += (m_max_bound - m_min_bound);
            m_bin_width *= 2.0;

            // Determine the number of bins.
            const size_t num_bins = m_data.size();

            // Re-bin the data.
            for (size_t i = 0; i < (num_bins / 2); ++i)
            {
                m_data[i] = m_data[i * 2] + m_data[(i * 2) + 1];
            }
            for (size_t i = (num_bins / 2); i < num_bins; ++i)
            {
                m_data[i] = 0.0;
            }
        }



    } // namespace data
} // namespace arc
