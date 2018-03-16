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



    } // namespace rng
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_RNG_HPP
