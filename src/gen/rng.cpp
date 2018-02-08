/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   06/02/2018.
 */



//  == HEADER ==
#include "gen/rng.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace rng
    {



        //  == FUNCTIONS ==
        //  -- Generation --
        /**
         *  Generate a random double drawn from the henyey-greenstein distribution.
         *
         *  @param  t_g Anisotropy value.
         *
         *  @pre    t_g must be between -1.0 and 1.0.
         *
         *  @return The value drawn from the henyey-greenstein phase function.
         */
        double henyey_greenstein(const double t_g)
        {
            assert((t_g > -1.0) && (t_g < 1.0));

            return acos((1.0 + math::square(t_g) - math::square(
                (1.0 - math::square(t_g)) / (1.0 - t_g + (2.0 * t_g * rng::random())))) / (2.0 * t_g));
        }

        /**
         *  Generate a random double from a gaussian with a given average and standard deviation.
         *
         *  @param  t_mu    Average of the gaussian distribution.
         *  @param  t_sigma Standard deviation of the distribution.
         *
         *  @return A random double from the specified gaussian distribution.
         */
        double gaussian(const double t_mu, const double t_sigma)
        {
            // Only generate a new pair of numbers every other call.
            static bool generate = false;
            generate = !generate;

            // Store the second (spare) randomly generated value.
            static double spare;

            // If a new pair is not required, return the unused previously generated value.
            if (!generate)
            {
                return ((spare * t_sigma) + t_mu);
            }

            // Generate a pair of uniform random values.
            double r_0, r_1;
            do
            {
                r_0 = random();
                r_1 = random();
            }
            while (r_0 <= std::numeric_limits<double>::min());

            // Convert the uniform random values to gaussian values.
            spare = std::sqrt(-2.0 * std::log(r_0)) * sin(2.0 * M_PI * r_1);

            return ((std::sqrt(-2.0 * std::log(r_0)) * cos(2.0 * M_PI * r_1) * t_sigma) + t_mu);
        }



    } // namespace rng
} // namespace arc
