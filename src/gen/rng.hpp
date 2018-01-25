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
//  -- Generation --
/**
 *  Macro used to access an instance of the uniform random number generator class.
 */
//#define SEED(t_seed) arc::random::Uniform::get_instance((t_seed))

constexpr const SEED = static_cast<arc::random::Uniform::base>(time(nullptr));



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_RNG_HPP
