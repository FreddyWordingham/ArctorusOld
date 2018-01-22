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
#include "cls/data/column.hpp"



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");


    arc::data::Column col("String", {0.0, 1.0, 4.0, 9.0, 16.0});

    LOG(col);

    col.save("column.dat");

    return (0);
}
