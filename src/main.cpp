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

//  -- Classes --
#include "cls/file/handle.hpp"



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");
    VERB("Arctorus directory:\n" << arc::config::ARCTORUS_DIR);

    LOG(READ_FILE("../README.md"));

    std::cout << 1 << "\n" << 2 << "\n";
    std::cout << "\r\r" << 3 << "\n" << 4 << "\n";


    return (0);
}
