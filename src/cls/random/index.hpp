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
            //  -- Data --
            const std::vector<size_t> m_index;  //! Vector of index values
            const std::vector<double> m_cdf;    //! The normalised cumulative distribution of the probabilities.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Index(const std::vector<size_t>& t_x, const std::vector<double>& t_p);

          private:
            //  -- Initialisation --
            std::vector<double> init_cdf(const std::vector<double> &t_p) const;


            //  == OPERATORS ==
          public:
            //  -- Generation --
            size_t operator()() const;
        };



    } // namespace random
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_RANDOM_INDEX_HPP
