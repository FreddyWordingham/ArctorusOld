/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   23/01/2018.
 */



//  == HEADER ==
#include "cls/data/histogram.hpp"



//  == INCLUDES ==
//  -- Classes --
#include "cls/data/table.hpp"



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



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of a histogram to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_hist      Histogram to be written.
         *
         *  @return A reference to the stream post-write.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Histogram& t_hist)
        {
            t_stream << Table(std::vector<Column>({Column("bin", t_hist.get_bin_pos()), Column("count", t_hist.m_data)}));

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Create a vector of bin positions.
         *
         *  @return A vector of bin positions.
         */
        std::vector<double> Histogram::get_bin_pos() const
        {
            std::vector<double> r_pos(m_data.size());

            for (size_t i = 0; i < r_pos.size(); ++i)
            {
                r_pos[i] = m_min_bound + (i * m_bin_width);
            }

            return (r_pos);
        }



    } // namespace data
} // namespace arc
