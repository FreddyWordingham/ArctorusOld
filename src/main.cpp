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

    std::array<int, 4> arr({{0, 1, 2, 3}});

    std::cout << "\n-\n";

    for (int i=0; i<=20; ++i)
    {
        double x = i * 0.1;
        std::cout << x << "\t" << utl::lower_index(arr, x) << "\t" << utl::upper_index(arr, x) << "\n";
    }

    std::cout << arr << "\n";

    return (0);
}
