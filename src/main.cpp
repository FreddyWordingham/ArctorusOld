/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <cmath>

//  -- General --
#include "gen/config.hpp"
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/math/vec.hpp"

using namespace arc;


//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");
    VERB("Arctorus directory:\n" << arc::config::ARCTORUS_DIR);

    LOG(READ_FILE("../README.md"));

    arc::math::Vec<5> vec({{0.0, 1.0, -1.0, 7.0, -7.0}});

    VAL(vec.magnitude());


    return (0);
}
