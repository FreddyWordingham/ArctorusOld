/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   25/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_RNG_HPP
#define ARCTORUS_SRC_GEN_RNG_HPP



//  == INCLUDES ==
//  -- System --
#include <cmath>
#include <ctime>

//  -- Classes --
#include "cls/random/uniform.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace rng
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Seeding --
        inline void seed(random::Uniform::base t_seed = static_cast<random::Uniform::base>(time(nullptr)));

        //  -- Generation --
        inline double random(double t_min = 0.0, double t_max = 1.0);
        inline double gaussian(double t_mu = 0.0, double t_sigma = 1.0);



        //  == FUNCTIONS ==
        //  -- Seeding --
        /**
         *  Seed the random number generator.
         *
         *  @param  t_seed  Value of the seed.
         */
        inline void seed(const random::Uniform::base t_seed)
        {
            random::Uniform::get_instance(t_seed);
        }


        //  -- Generation --
        /**
         *  Retrieve a random number from the uniform generator.
         *
         *  @param  t_min   Minimum bound for the generated value.
         *  @param  t_max   Maximum bound for the generated value.
         *
         *  @return A random double between the given bounds.
         */
        inline double random(const double t_min, const double t_max)
        {
            return (random::Uniform::get_instance()(t_min, t_max));
        }

        /**
         *  Generate a random double from a gaussian with a given average and standard deviation.
         *
         *  @param  t_mu    Average of the gaussian distribution.
         *  @param  t_sigma Standard deviation of the distribution.
         *
         *  @return A random double from the specified gaussian distribution.
         */
        inline double gaussian(const double t_mu, const double t_sigma)
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

            return (std::sqrt(-2.0 * std::log(r_0)) * cos(2.0 * M_PI * r_1));
        }



    } // namespace rng
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_RNG_HPP
