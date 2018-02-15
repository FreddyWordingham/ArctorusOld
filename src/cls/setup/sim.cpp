/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/setup/sim.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        Sim::Sim(const parser::Json& t_json)
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the vector of light objects.
         *
         *  @param  t_json Json setup file.
         *
         *  @return The initialise vector of light objects.
         */
        Sim::init_light(const parser::Json& t_json) const
        {
        }


    } // namespace setup
} // namespace arc
