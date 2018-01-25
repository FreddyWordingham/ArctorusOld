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
#include <ctime>

//  -- Classes --
#include "cls/random/uniform.hpp"



//  == MACROS ==
//  -- Access --
/**
 *  Call the random number generator.
 *
 *  @param  t_min   Minimum bound for the generated value.
 *  @param  t_max   Maximum bound for the generated value.
 *
 *  @return A random double between the given bounds.
 */
#define RANDOM(t_min, t_max) random::Uniform::get_instance()(t_min, t_max)



//  == NAMESPACE ==
namespace arc
{
    namespace rng
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Seeding --
        void seed(random::Uniform::base t_seed = static_cast<random::Uniform::base>(time(nullptr)));



        //  == FUNCTIONS ==
        //  -- Seeding --
        /**
         *  Seed the random number generator.
         *
         *  @param  t_seed  Value of the seed.
         */
        void seed(const random::Uniform::base t_seed)
        {
            random::Uniform::get_instance(t_seed);
        }



    } // namespace rng
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_RNG_HPP
