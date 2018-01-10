/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/config.hpp"
#include "gen/log.hpp"

#include "utl/array.hpp"


//  == NAMESPACE ==
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
    VERB("Arctorus directory:\n" << ARCTORUS_DIR);

    //std::array<double, 3> arr({{0.0, 1.0, -1.0}});
    double x = 1.25;
    VAL(x);

    WARN("Something.", "Went wrong.");

    return (0);
}
