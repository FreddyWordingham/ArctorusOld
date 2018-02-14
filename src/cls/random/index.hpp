/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   13/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_RANDOM_INDEX_HPP
#define ARCTORUS_SRC_CLS_RANDOM_INDEX_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == CLASS ==
        /**
         *  A generator class which generates random indices according to a given step probability distribution.
         */
        class Index
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const size_t m_min_bound = 0;   //! Minimum index of the generation range.
            const size_t m_max_bound;       //! Maximum index of the generation range.

            //  -- Data --
            const std::vector<double> m_cdf;    //! The normalised cumulative distribution of the probabilities.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Index(const std::vector<double>& t_p);

          private:
            //  -- Initialisation --
            std::vector<double> init_cdf(const std::vector<double> &t_p) const;


            //  == OPERATORS ==
          public:
            //  -- Getters --
            size_t get_min_bound() const { return (m_min_bound); }
            size_t get_max_bound() const { return (m_max_bound); }

            //  -- Generation --
            size_t operator()() const;
        };



    } // namespace random
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_RANDOM_INDEX_HPP
