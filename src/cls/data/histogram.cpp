/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   23/01/2018.
 */



//  == HEADER ==
#include "cls/data/histogram.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Classes --
#include "cls/data/table.hpp"
#include "cls/file/handle.hpp"



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
         *  @param  t_dynamic   Specify if histogram is dynamic.
         *
         *  @pre    t_max_bound must be greater than t_min_bound.
         *  @pre    t_num_bins must be greater than 0.
         */
        Histogram::Histogram(const double t_min_bound, const double t_max_bound, const size_t t_num_bins,
                             const bool t_dynamic) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_bin_width((m_max_bound - m_min_bound) / t_num_bins),
            m_data(t_num_bins),
            m_dynamic(t_dynamic)
        {
            assert(t_max_bound > t_min_bound);
            assert(t_num_bins > 0);
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
        std::ostream& operator<<(std::ostream& t_stream, const Histogram& t_hist)
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
        std::vector<double> Histogram::get_bin_pos(const align t_align) const
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

        /**
         *  Determine the average value from the histogram data.
         *
         *  @return The average value of the histogram.
         */
        double Histogram::get_average() const
        {
            double      total = 0.0;
            double      ave   = 0.0;
            for (size_t i     = 0; i < m_data.size(); ++i)
            {
                const double x = ((i + 0.5) * m_bin_width);
                total += m_data[i];
                ave += x * m_data[i];
            }

            return (ave / total);
        }

        /**
         *  Determine the most probable value from the histogram data.
         *
         *  @return The most probable value of the histogram.
         */
        double Histogram::get_most_probable() const
        {
            return (m_min_bound + (m_bin_width * (utl::max_index(m_data) + 0.5)));
        }


        //  -- Collection --
        /**
         *  Bin the given value within the histogram.
         *
         *  @param  t_val       Value to be binned.
         *  @param  t_weight    Weight of the value to be binned.
         *
         *  @pre    t_weight must be positive.
         */
        void Histogram::bin_value(double t_val, double t_weight)
        {
            assert(t_weight > 0.0);

            if ((t_val < m_min_bound) || (t_val > m_max_bound))
            {
                if (m_dynamic)
                {
                    if (t_val < m_min_bound)
                    {
                        const double m      = 1 + ((t_val - m_max_bound) / (m_max_bound - m_min_bound));
                        const auto   growth = static_cast<unsigned int>(std::ceil(std::log2(m)));

                        for (unsigned int i = 0; i < growth; ++i)
                        {
                            descend();
                        }
                    }
                    else
                    {
                        const double m      = 1 + ((t_val - m_max_bound) / (m_max_bound - m_min_bound));
                        const auto   growth = static_cast<unsigned int>(std::ceil(std::log2(m)));

                        for (unsigned int i = 0; i < growth; ++i)
                        {
                            ascend();
                        }
                    }
                }
                else
                {
                    return;
                }
            }

            assert((t_val >= m_min_bound) && (t_val <= m_max_bound));

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
        std::string Histogram::serialise(const bool t_normalise, const align t_align) const
        {
            std::stringstream stream;

            stream << Table(std::vector<Column>(
                {Column("bin", get_bin_pos(t_align)), Column("count", (t_normalise ? (m_data / utl::max(m_data)) : m_data))}));

            return (stream.str());
        }


        //  -- Saving --
        /**
         *  Save the state of the histogram to a given file path.
         *
         *  @param  t_path      Path to the save location of the file.
         *  @param  t_normalise When true, normalise the count data to a maximum of unity.
         *  @param  t_align     Alignment position of the bin.
         */
        void Histogram::save(const std::string& t_path, const bool t_normalise, const align t_align) const
        {
            file::Handle file(t_path, std::fstream::out);

            switch (t_align)
            {
                case align::LEFT:
                    file.comment() << "Bin alignment: left.\n";
                    break;
                case align::CENTER:
                    file.comment() << "Bin alignment: center.\n";
                    break;
                case align::RIGHT:
                    file.comment() << "Bin alignment: right.\n";
                    break;
            }

            file.comment() << "Total counts: " << utl::total(m_data) << "\n";
            file.comment() << "Normalised: " << std::boolalpha << t_normalise << "\n";
            file.comment() << "Average: " << get_average() << "\n";
            file.comment() << "Most probable: " << get_most_probable() << "\n";

            file << serialise(t_normalise, t_align);
        }


        //  -- Growth --
        /**
         *  Increase the max bound of the histogram's range.
         *
         *  @pre    m_dynamic must be true.
         */
        void Histogram::ascend()
        {
            assert(m_dynamic);

            // Increase the maximum bound and double the bin width.
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

        /**
         *  Decrease the min bound of the histogram's range.
         *
         *  @pre    m_dynamic must be true.
         */
        void Histogram::descend()
        {
            assert(m_dynamic);

            // Decrease the minimum bound and double the bin width.
            m_min_bound -= (m_max_bound - m_min_bound);
            m_bin_width *= 2.0;

            // Determine the number of bins.
            const size_t num_bins = m_data.size();

            // Re-bin the data.
            for (size_t i = (num_bins - 1); i >= (num_bins / 2); --i)
            {
                VAL(i);
                const size_t j = (2 * i) - num_bins;
                m_data[i] = m_data[j] + m_data[j + 1];
            }
            for (size_t i = 0; i < (num_bins / 2); ++i)
            {
                m_data[i] = 0.0;
            }
        }



    } // namespace data
} // namespace arc
