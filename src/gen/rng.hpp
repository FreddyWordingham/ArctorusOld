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
        double henyey_greenstein(double t_g);
        double gaussian(double t_mu = 0.0, double t_sigma = 1.0);



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



    } // namespace rng
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_RNG_HPP
