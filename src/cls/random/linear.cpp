/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/random/linear.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"
#include "gen/math.hpp"
#include "gen/rng.hpp"



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
         *
         *  @post   t_x must be sorted into ascending order.
         *  @post   t_min_bound must be less than m_max_bound.
         */
        Linear::Linear(const std::vector<double>& t_x, const std::vector<double>& t_p) :
            m_min_bound(t_x.front()),
            m_max_bound(t_x.back()),
            m_x(t_x),
            m_p(init_p(t_p)),
            m_grad(init_grad()),
            m_inter(init_inter()),
            m_cdf(init_cdf()),
            m_frac(init_frac())
        {
            assert(utl::is_ascending(t_x));
            assert(m_min_bound < m_max_bound);
        }


        //  -- Initialisation --
        /**
         *  Initialise the probability vector by normalising the area.
         *
         *  @pre    t_p size must equal m_x size.
         *  @pre    t_p must always be greater than zero.
         *
         *  @return Initialise the probability values.
         */
        std::vector<double> Linear::init_p(const std::vector<double>& t_p) const
        {
            assert(t_p.size() == m_x.size());
            assert(utl::is_always_greater_than_or_equal_to(t_p, 0.0));

            // Sum the area of each trapezium.
            double      total_area = 0.0;
            for (size_t i          = 0; i < (t_p.size() - 1); ++i)
            {
                total_area += ((t_p[i] + t_p[i + 1]) * (m_x[i + 1] - m_x[i])) / 2.0;
            }

            // Create the return probability values.
            std::vector<double> r_p(t_p.size());

            // Calculate the normalised probability values.
            for (size_t i          = 0; i < (t_p.size() - 1); ++i)
            {
                r_p[i] = t_p[i] / total_area;
            }

            return (r_p);
        }

        /**
         *  Initialise the vector of probability gradients.
         *
         *  @return The initialised vector of probability gradients.
         */
        std::vector<double> Linear::init_grad() const
        {
            // Create the return vector;
            std::vector<double> r_grad(m_x.size() - 1);

            // Calculate the gradients.
            for (size_t i = 0; i < r_grad.size(); ++i)
            {
                r_grad[i] = (m_p[i + 1] - m_p[i]) / (m_x[i + 1] - m_x[i]);
            }

            return (r_grad);
        }

        /**
         *  Initialise the vector of probability y-axis intersections.
         *
         *  @return The initialised vector of probability y-axis intersections.
         */
        std::vector<double> Linear::init_inter() const
        {
            // Create the return vector;
            std::vector<double> r_inter(m_x.size() - 1);

            // Calculate the gradients.
            for (size_t i = 0; i < r_inter.size(); ++i)
            {
                r_inter[i] = m_p[i] - (m_grad[i] * m_x[i]);
            }

            return (r_inter);
        }

        /**
         *  Initialise the cumulative distribution vector of the probability distribution.
         *
         *  @pre    m_x size must match m_p size.
         *  @pre    m_x size must be greater than one.
         *  @pre    m_x data must be in ascending order.
         *  @pre    m_p data must always be non-negative.
         *
         *  @post   m_cdf final value must be unity.
         *
         *  @return The initialised cdf data vector.
         */
        std::vector<double> Linear::init_cdf() const
        {
            assert(m_x.size() == m_p.size());
            assert(m_x.size() > 1);
            assert(utl::is_ascending(m_x));
            assert(utl::is_always_greater_than_or_equal_to(m_p, 0.0));

            // Calculate the area of each trapezium.
            std::vector<double> base(m_x.size() - 1);
            for (size_t         i = 0; i < base.size(); ++i)
            {
                base[i] = ((m_p[i] + m_p[i + 1]) * (m_x[i + 1] - m_x[i])) / 2.0;
            }

            // Calculate the values of the cdf.
            std::vector<double> r_cdf(m_x.size());
            r_cdf[0] = 0.0;
            for (size_t i = 1; i < r_cdf.size(); ++i)
            {
                r_cdf[i] = r_cdf[i - 1] + base[i - 1];
            }

            assert(m_cdf.back() == 1.0);

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
            // Create the vector of fractional triangle areas.
            std::vector<double> r_frac(m_x.size() - 1);

            // Calculate the fraction of area occupied by the triangle.
            for (size_t i = 0; i < r_frac.size(); ++i)
            {
                double above = (std::fabs(m_p[i + 1] - m_p[i]) * (m_x[i + 1] - m_x[i])) / 2.0;
                double below = ((m_p[i] + m_p[i + 1]) / 2.0) * (m_x[i + 1] - m_x[i]);

                r_frac[i] = above / below;
            }

            return (r_frac);
        }



        //  == OPERATORS ==
        //  -- Generation --
        /**
         *  Generate a random number from the probability distribution.
         *
         *  @return A randomly generated value from the probability distribution.
         */
        double Linear::operator()() const
        {
            // Generate a random double between zero and one.
            const double r = rng::random();

            // Determine the lower index of the cdf where the value is found.
            static size_t lower_index = 0;
            lower_index = utl::lower_index(m_cdf, r, lower_index);

            // Generate a value by interpolating the probabilities.
            const double f = rng::random();
            if (f <= m_frac[lower_index])
            {
                if (m_p[lower_index] < m_p[lower_index + 1])
                {
                    return (m_x[lower_index] + (std::sqrt(rng::random()) * (m_x[lower_index + 1] - m_x[lower_index])));
                }
                return (m_x[lower_index + 1] - (std::sqrt(rng::random()) * (m_x[lower_index + 1] - m_x[lower_index])));
            }

            return (m_x[lower_index] + (rng::random() * (m_x[lower_index + 1] - m_x[lower_index])));
        }

        /**
         *  Generate a random number from the probability distribution between the given limits.
         *
         *  @param  t_min   Minimum value that may be returned.
         *  @param  t_max   Maximum value that may be returned.
         *
         *  @pre    t_min must be greater than, or equal to, m_lower_bound and less than m_upper_bound.
         *  @pre    t_max must be greater than m_lower_bound and less than, or equal to, the m_upper_bound.
         *
         *  @post   r_val must be between the limits of t_min and t_max.
         *
         *  @return A randomly generated value from the probability distribution between the limits.
         */
        double Linear::operator()(const double t_min, const double t_max) const
        {
            assert((t_min >= m_min_bound) && (t_min < m_max_bound));
            assert((t_max > m_min_bound) && (t_min <= m_max_bound));

            // Generate a random double between the interpolated cdf values.
            const double r = rng::random(get_cdf(t_min), get_cdf(t_max));

            // Determine the lower index of the cdf where the value is found.
            static size_t lower_index = 0;
            lower_index = utl::lower_index(m_cdf, r, lower_index);

            // Generate a value by interpolating the probabilities.
            const double f = rng::random();
            if (f <= m_frac[lower_index])
            {
                if (m_p[lower_index] < m_p[lower_index + 1])
                {
                    return (m_x[lower_index] + (std::sqrt(rng::random()) * (m_x[lower_index + 1] - m_x[lower_index])));
                }
                return (m_x[lower_index + 1] - (std::sqrt(rng::random()) * (m_x[lower_index + 1] - m_x[lower_index])));
            }

            // Calculate the generated value.
            const double r_val = m_x[lower_index] + (rng::random() * (m_x[lower_index + 1] - m_x[lower_index]));

            assert((r_val >= t_min) && (r_val <= t_max));

            return (r_val);
        }



        //  == METHODS ==
        //  -- Interpolation --
        /**
         *  Calculate the cdf for the given value of x.
         *
         *  @param  t_x Value of x to calculate the cdf of.
         *
         *  @pre    t_x must fall within the bounds.
         *
         *  @post   r_cdf must be between zero and one.
         *
         *  @return The cdf for the given value.
         */
        double Linear::get_cdf(const double t_x) const
        {
            assert((t_x >= m_min_bound) && (t_x <= m_max_bound));

            if (math::equal(t_x, m_min_bound))
            {
                return (0.0);
            }
            else if (math::equal(t_x, m_max_bound))
            {
                return (1.0);
            }

            const size_t lower_index = utl::lower_index(m_x, t_x);

            const double r_cdf = m_cdf[lower_index] + ((m_grad[lower_index] / 2.0) * (math::square(t_x) - math::square(
                m_x[lower_index]))) + (m_inter[lower_index] * (t_x - m_x[lower_index]));

            assert((r_cdf >= 0.0) && (r_cdf <= 1.0));

            return (r_cdf);
        }



    } // namespace random
} // namespace arc
