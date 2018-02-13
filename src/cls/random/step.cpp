/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   13/02/2018.
 */



//  == HEADER ==
#include "cls/random/step.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/rng.hpp"

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
         *  @post   m_p data must always be non-negative.
         */
        Step::Step(const std::vector<double>& t_x, const std::vector<double>& t_p) :
            m_x(t_x),
            m_cdf(init_cdf(t_p))
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
        std::vector<double> Step::init_cdf(const std::vector<double>& t_p) const
        {
            assert(m_x.size() == t_p.size());
            assert(m_x.size() > 1);
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));

            // Create return vector.
            std::vector<double> r_cdf(t_p.size());

            // Initialise the cdf values.
            r_cdf[0] = t_p[0];
            for (size_t i = 1; i < t_p.size(); ++i)
            {
                r_cdf[i] = r_cdf[i - 1] + t_p[i];
            }

            // Normalise the cdf values.
            for (size_t i = 0; i < t_p.size(); ++i)
            {
                r_cdf[i] /= r_cdf.back();
            }

            return (r_cdf);
        }



        //  == OPERATORS ==
        //  -- Generation --
        /**
         *  Generate a random number from the step probability distribution.
         *
         *  @return A randomly generated value from the step probability distribution.
         */
        double Step::operator()() const
        {
            return (m_x[utl::lower_index(m_cdf, rng::random())]);
        }



    } // namespace random
} // namespace arc
