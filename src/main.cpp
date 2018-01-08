/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <array>
#include <iostream>

//  -- General --
#include "gen/config.hpp"
#include "gen/math.hpp"

//  -- Utility --
#include "utl/string.hpp"
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
    std::cout << "Hello world!\n";
    std::cout << "Build information:\n" << BUILD_INFO << "\n";
    std::cout << "Arctorus directory:\n" << ARCTORUS_DIR << "\n";

    std::array<int, 7> arr({{9, 7, 3, 0, -2, -3, -5}});

    std::cout << "\n-\n";

    std::cout << utl::lower_index(arr, -0.5) << "\n";
    std::cout << utl::upper_index(arr, -0.5) << "\n";
//    std::cout << utl::lower_index(arr, -3.2) << "\n";

    return (0);
}
