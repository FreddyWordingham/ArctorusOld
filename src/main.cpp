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
    std::cout << "Arctorus directory:\n" << ARCTORUS_DIR << "\n";

    std::cout << utl::is_numerical("0.123") << "\n";
    std::cout << utl::is_numerical("1E23") << "\n";
    std::cout << utl::is_numerical("-2.0E2") << "\n";
    std::cout << utl::is_numerical("E3") << "\n";
    std::cout << utl::is_numerical("") << "\n";
    std::cout << utl::is_numerical(" ") << "\n";
    std::cout << utl::is_numerical("  ") << "\n";

    return (0);
}
