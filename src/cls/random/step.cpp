/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   13/02/2018.
 */



//  == HEADER ==
#include "cls/random/step.hpp"



//  == INCLUDES ==
//  -- Utility --
#include "utl/vector.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a step random number generator from a given probability distribution.
         *
         *  @param  t_x Vector of values.
         *  @param  t_p Vector of corresponding probabilities.
         *
         *  @post   t_p must always be greater than, or equal to, zero.
         */
        Step::Step(const std::vector<double>& t_x, const std::vector<double>& t_p) :
            m_x(t_x),
            m_cdf(init_cdf())
        {
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));
        }


        //  -- Initialisation --



    } // namespace random
} // namespace arc
