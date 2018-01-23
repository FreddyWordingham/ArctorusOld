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
            const size_t        m_num_bins;    //! Number of histogram bins.
            const size_t        m_bin_width;   //! Width of the histogram bins.
            std::vector<double> m_data; //! Histogram bin data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Histogram(const std::vector<double>& t_data);
//            Histogram(const double t_min_bound, const double t_max_bound, const size_t t_num_bins);


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_HISTOGRAM_HPP
