/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   23/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DATA_HISTOGRAM_HPP
#define ARCTORUS_SRC_CLS_DATA_HISTOGRAM_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == CLASS ==
        /**
         *  Collects double values and bins them into an array of bins.
         */
        class Histogram
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const double m_min_bound;   //! Minimum bound of the histogram range.
            const double m_max_bound;   //! Minimum bound of the histogram range.

            //  -- Data --
            const double        m_bin_width;    //! Width of the histogram bins.
            std::vector<double> m_data;         //! Histogram bin data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Histogram(double t_min_bound, double t_max_bound, size_t t_num_bins);


            //  == OPERATORS ==
          private:
            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const Histogram& t_hist);


            //  == METHODS ==
          private:
            //  -- Getters --
            std::vector<double> get_bin_pos() const;
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_HISTOGRAM_HPP
