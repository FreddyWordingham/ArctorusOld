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
#include "utl/vector.hpp"
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

    std::vector<int> vec({0, 1, 2, 3});

    std::cout << "\n-\n";

    std::cout << vec << "\n";

    std::cout << utl::min_index(vec) << "\n";
    std::cout << utl::max_index(vec) << "\n";
    std::cout << utl::min(vec) << "\n";
    std::cout << utl::max(vec) << "\n";
    std::cout << utl::total(vec) << "\n";
    std::cout << utl::magnitude(vec) << "\n";

    std::cout << utl::is_ascending(vec) << "\n";
    std::cout << utl::is_descending(vec) << "\n";
    std::cout << utl::is_monotonic(vec) << "\n";
    std::cout << utl::is_uniform(vec) << "\n";


    std::array<int, 4> arr({{0, 1, 2, 3}});
    std::cout << "-\n" << utl::is_uniform(arr, 0.1) << "\n";

    return (0);
}
