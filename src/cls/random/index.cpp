/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   13/02/2018.
 */



//  == HEADER ==
#include "cls/random/index.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"
#include "gen/rng.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a index generator from a given probability distribution.
         *
         *  @param  t_p Vector of index probabilities.
         *
         *  @post   m_p data must always be non-negative.
         */
        Index::Index(const std::vector<double>& t_p) :
            m_max_bound(t_p.size() - 1),
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
         *  @pre    m_p data must always be non-negative.
         *
         *  @post   m_cdf final value must be unity.
         *
         *  @return The initialised cumulative distribution frequency vector.
         */
        std::vector<double> Index::init_cdf(const std::vector<double>& t_p) const
        {
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));

            // Create return vector.
            std::vector<double> r_cdf(t_p.size() + 1);

            // Initialise the cdf values.
            r_cdf[0] = 0.0;
            for (size_t i = 1; i < r_cdf.size(); ++i)
            {
                r_cdf[i] = r_cdf[i - 1] + t_p[i - 1];
            }

            // Normalise the cdf values.
            for (size_t i=0; i<r_cdf.size(); ++i)
            {
                r_cdf[i] /= r_cdf.back();
            }

            assert(m_cdf.back() == 1.0);

            return (r_cdf);
        }



        //  == OPERATORS ==
        //  -- Generation --
        /**
         *  Generate a random index from the step probability distribution.
         *
         *  @return A randomly generated value from the step probability distribution.
         */
        size_t Index::operator()() const
        {
            return (utl::lower_index(m_cdf, rng::random()));
        }



    } // namespace random
} // namespace arc
