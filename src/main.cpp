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

    std::array<double, 7> arr_a({{0.0, -3.0, -7.5, 4.0, M_PI, 1.0/3.0, -1.0/4.0}});
    std::array<int, 7> arr_b({{0, -3, -7, 4, 3, 0, -2}});
    std::array<unsigned int, 7> arr_c({{0, 3, 7, 4, 3, 0, 2}});

    std::cout << "\n-\n";

    std::cout << utl::min_index(arr_a) << "\n";
    std::cout << utl::max_index(arr_a) << "\n";
    std::cout << utl::min(arr_a) << "\n";
    std::cout << utl::max(arr_a) << "\n";
    std::cout << utl::total(arr_a) << "\n";
    std::cout << utl::magnitude(arr_a) << "\n";

    std::cout << "\n-\n";

    std::cout << utl::min_index(arr_b) << "\n";
    std::cout << utl::max_index(arr_b) << "\n";
    std::cout << utl::min(arr_b) << "\n";
    std::cout << utl::max(arr_b) << "\n";
    std::cout << utl::total(arr_b) << "\n";
    std::cout << utl::magnitude(arr_b) << "\n";

    std::cout << "\n-\n";

    std::cout << utl::min_index(arr_c) << "\n";
    std::cout << utl::max_index(arr_c) << "\n";
    std::cout << utl::min(arr_c) << "\n";
    std::cout << utl::max(arr_c) << "\n";
    std::cout << utl::total(arr_c) << "\n";
    std::cout << utl::magnitude(arr_c) << "\n";

    return (0);
}
