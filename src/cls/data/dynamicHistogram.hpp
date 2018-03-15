/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/03/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DATA_DYNAMICHISTOGRAM_HPP
#define ARCTORUS_SRC_CLS_DATA_DYNAMICHISTOGRAM_HPP



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
         *  Collects double values and bins them into an array of bins with dynamic limits.
         */
        class DynamicHistogram
        {
            //  == ENUMERATIONS ==
            //  -- Alignment --
          public:
            /**
             *  Enumeration of the bin alignment positions which may be set when calling get_bin_pos.
             */
            enum class align
            {
                LEFT,   //! Save bin left position.
                CENTER, //! Save bin center position.
                RIGHT   //! Save bin right position.
            };


            //  == FIELDS ==
          private:
            //  -- Bounds --
            double m_min_bound; //! Minimum bound of the histogram range.
            double m_max_bound; //! Maximum bound of the histogram range.

            //  -- Data --
            double              m_bin_width;    //! Width of the histogram bins.
            std::vector<double> m_data;         //! Histogram bin data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            DynamicHistogram(double t_min_bound, double t_max_bound, size_t t_num_bins);


            //  == OPERATORS ==
          public:
            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const DynamicHistogram& t_hist);


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_min_bound() const { return (m_min_bound); }
            double get_max_bound() const { return (m_max_bound); }
            double get_bin_width() const { return (m_bin_width); }
            size_t get_num_bin() const { return (m_data.size()); }
            std::vector<double> get_bin_pos(align t_align = align::CENTER) const;

            //  -- Collection --
            void bin_value(double t_val, double t_weight = 1.0);

            //  -- Serialisation --
            std::string serialise(bool t_normalise = false, align t_align = align::CENTER) const;

          public:
            //  -- Growth --
            void ascend();
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_DYNAMICHISTOGRAM_HPP
