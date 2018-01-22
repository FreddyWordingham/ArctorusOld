/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");

    std::string str = "       ";
//    std::getline(std::cin, str);

    std::cout << "String reads: \n'" << str << "'\n";

    arc::utl::strip_whitespace(&str);
    std::cout << "After cull  : \n'" << str << "'\n";


    return (0);
}
