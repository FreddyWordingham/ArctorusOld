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


    std::array<double, 4> arr({{0.0, 1.0, 2.0, 3.0}});
    for (size_t           i = 0; i < 5; ++i)
    {
        std::cout << i << " : ";
        std::cout << arr[i];
        std::cout << "\n";
    }

    return (0);
}
