/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <iostream>

//  -- General --
#include "gen/config.hpp"
#include "gen/math.hpp"

//  -- Utility --



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
    std::cout << "Hello world!\n";
    std::cout << "Build information:\n" << BUILD_INFO << "\n";

    std::cout << square(2.5) << "\n";
    std::cout << cube(2.5) << "\n";

    return (0);
}
