/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include <cls/data/column.hpp>
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


    arc::data::Column col(arc::file::read("column.dat"));

    LOG(col);

    //  col.save("column.dat");

    return (0);
}
