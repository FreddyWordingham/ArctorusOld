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
         *  @pre    m_p data must always be non-negative.
         */
        Step::Step(const std::vector<double>& t_x, const std::vector<double>& t_p) :
            m_x(t_x),
            m_cdf(init_cdf())
        {
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));
        }


        //  -- Initialisation --
        /**
         *  Initialise the cumulative distribution frequency of the probability data.
         *
         *  @param  t_p Vector of corresponding probabilities.
         *
         *  @pre    m_x vector size must match t_p vector size.
         *  @pre    m_x size must be greater than one.
         *  @pre    m_p data must always be non-negative.
         *
         *  @return The initialised cumulative distribution frequency vector.
         */
        std::vector<double> Step::init_cdf(const std::vector<double> &t_p) const
        {
            assert(m_x.size() == t_p.size());
            assert(m_x.size() > 1);
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));

            // Create return vector.
            std::vector<double> r_cdf(t_p.size());
        }


    } // namespace random
} // namespace arc
