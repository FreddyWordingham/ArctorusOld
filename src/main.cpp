/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Classes --
#include "cls/data/table.hpp"



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");


    arc::data::Table tab({"one", "two", "three", "four things"}, {{0.0, 1.0, 2,   3,  4,   5.0},
                                                                  {0.0, 1.0, 4.0, 9,  16,  25},
                                                                  {0,   1,   8,   27, 64,  125},
                                                                  {0,   1,   16,  81, 256, 625}});

    return (0);
}
