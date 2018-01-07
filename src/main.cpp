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

//  -- Utility --
#include "utl/string.hpp"



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

    std::cout << utl::create_timestamp() << "\n";

    for (int i=0; i<1000; ++i)
    {
        std::cout << utl::create_timestring(i) << "\n";
    }

    return (0);
}
