/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/random/linear.hpp"



//  == INCLUDES ==
//  -- System --

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
         *  Construct a linear random number generator from a given probability distribution.
         *
         *  @param  t_x Vector of X positions.
         *  @param  t_p Vector of corresponding probabilities.
         */
        Linear::Linear(const std::vector<double>& t_x, const std::vector<double>& t_p) :
            m_x(t_x),
            m_p(t_p),
            m_cdf(init_cdf()),
            m_frac(init_frac())
        {

        }


        //  -- Initialisation --
        /**
         *  Initialise the cumulative distribution vector of the probability distribution.
         *
         *  @pre    m_x size must match m_p size.
         *  @pre    m_x size must be greater than one.
         *  @pre    m_x data must be in ascending order.
         *  @pre    m_p data must always be non-negative.
         *
         *  @return The initialised cdf data vector.
         */
        std::vector<double> Linear::init_cdf() const
        {
            assert(m_x.size() == m_p.size());
            assert(m_x.size() > 1);
            assert(utl::is_ascending(m_x));
            assert(utl::is_always_less_than_or_equal_to(m_p, 0.0));

            // Calculate the area of each trapezium.
            std::vector<double> base(m_x.size() - 1);
            for (size_t         i = 0; i < base.size(); ++i)
            {
                base[i] = ((m_p[i] + m_p[i + 1]) * (m_x[i + 1] - m_x[i])) / 2.0;
            }

            // Calculate the values of the cdf.
            std::vector<double> r_cdf(m_x.size());
            r_cdf[0] = 0.0;
            for (size_t i = 0; i < r_cdf.size(); ++i)
            {
                r_cdf[i] = r_cdf[i - 1] + base[i - 1];
            }

            // Normalise the cdf data.
            for (size_t i = 0; i < r_cdf.size(); ++i)
            {
                r_cdf[i] /= r_cdf.back();
            }

            return (r_cdf);
        }

        /**
         *  Initialise the value of fractional values.
         *  These are the fractions of the triangular interpolation values to complete the integration range.
         *
         *  @return The initialised vector of fractional values.
         */
        std::vector<double> Linear::init_frac() const
        {
            std::vector<double> r_frac(m_x.size() - 1);

            for (size_t i = 0; i < r_frac.size(); ++i)
            {
                double above = (std::fabs(m_p[i + 1] - m_p[i]) * (m_x[i + 1] - m_x[i])) / 2.0;
                double below = ((m_p[i] + m_p[i + 1]) / 2.0) * (m_x[i + 1] - m_x[i]);

                r_frac[i] = above / below;
            }

            return (r_frac);
        }



    } // namespace random
} // namespace arc
