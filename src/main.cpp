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

    std::string a = "one";
    std::string b = "1.23";
    std::string c = "1e92.3";
    std::string d = "2.3e32";
    std::string e = "2,32";

    std::cout << a << " : " << utl::is_numerical(a) << "\n";
    std::cout << b << " : " << utl::is_numerical(b) << "\n";
    std::cout << c << " : " << utl::is_numerical(c) << "\n";
    std::cout << d << " : " << utl::is_numerical(d) << "\n";
    std::cout << e << " : " << utl::is_numerical(e) << "\n";

    return (0);
}
