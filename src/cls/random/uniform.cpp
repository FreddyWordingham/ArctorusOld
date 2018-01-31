/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   25/01/2018.
 */



//  == HEADER ==
#include "cls/random/uniform.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == INSTANTIATION ==
        //  -- Singleton --
        /**
         *  Retrieve an instance of the uniform random number generator class.
         *  Implements a singleton whereby only one uniform object may be created.
         *  Uses lazy initialisation.
         *
         *  @param  t_seed  Seed used to initialise the random number generator.
         *
         *  @return The initialised uniform object.
         */
        Uniform& Uniform::get_instance(const base t_seed)
        {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
            static Uniform s_uni(t_seed);
#pragma clang diagnostic pop

            return (s_uni);
        }


        //  -- Constructors --
        /**
         *  Construct a uniform random number generator using a given seed.
         *
         *  @param  t_seed  Seed used to initialise the random number generator.
         */
        Uniform::Uniform(const base t_seed) :
            m_seed(t_seed),
            m_u(static_cast<base>(0)),
            m_v(static_cast<base>(4101842887655102017)),
            m_w(static_cast<base>(1))
        {
            init_generation_variables();

            LOG("Seed: " << m_seed);
        }


        //  -- Initialisation --
        /**
         *  Initialise the generation variables through bit shifting and calls to the generator method.
         */
        void Uniform::init_generation_variables()
        {
            m_u = m_seed ^ m_v;
            gen_base();
            m_v = m_u;
            gen_base();
            m_w = m_v;
            gen_base();
        }



        //  == METHODS ==
        //  -- Generation --
        /**
         *  Generate a base value through bitwise operations.
         *  All values have an equal probability of generation over time.
         *
         *  @return A sudo random base value.
         */
        Uniform::base Uniform::gen_base()
        {
            m_u    = m_u + static_cast<base>(2862933555777941757) + static_cast<base>(7046029254386353087);
            m_v ^= m_v >> 17;
            m_v ^= m_v << 31;
            m_v ^= m_v >> 8;
            m_w    = static_cast<base>(4294957665) * (m_w & 0xffffffff) + (m_w >> 32);
            base x = m_u ^(m_u << 2);
            x ^= x >> 35;
            x ^= x << 4;

            return ((x + m_v) ^ m_w);
        }



    } // namespace random
} // namespace arc
