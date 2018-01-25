/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   25/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_RANDOM_UNIFORM_HPP
#define ARCTORUS_SRC_CLS_RANDOM_UNIFORM_HPP



//  == INCLUDES ==
//  -- System --
#include <cstdint>



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == CLASS ==
        /**
         *  A sudo-random number generator capable of producing sudo random numbers with uniform probability.
         *  Primarily used to generate random doubles between zero and unity.
         */
        class Uniform
        {
            //  == FIELDS ==
          private:
            //  -- Seed --
            const uint64_t m_seed;  //! Seed used to initialise the generator.

            //  -- Generation Variables --
            uint64_t m_u;   //! First value used in the generation of random values.
            uint64_t m_v;   //! Second value used in the generation of random values.
            uint64_t m_w;   //! Third value used in the generation of random values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace random
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_RANDOM_UNIFORM_HPP
