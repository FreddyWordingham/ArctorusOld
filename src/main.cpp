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
#include "gen/math.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"

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

    arc::math::Mat<2, 2> a({{{{4.0, 1.0}}, {{2.0, -3.0}}}});
    arc::math::Mat<2, 2> b({{{{-1.0, -3.0}}, {{4.0, 2.0}}}});

    VAL(a);
    VAL(b);
    VAL(a + b);

    return (0);
}
