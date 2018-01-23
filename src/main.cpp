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
#include "cls/file/handle.hpp"
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

//    LOG(arc::file::read("table.dat"));

    arc::data::Table tab;

    LOG(tab);

    tab.append_col(arc::data::Column("Col title", {0.0, 1.0, 2.0, 3.0}));
    LOG(tab);
    tab.append_col(arc::data::Column("Col title B", {0.0, 1.0, 4.0, 360.5}));
    LOG(tab);
    tab.append_col(arc::data::Column("C", {-3.0, -3.0, -2.0, 77.5}));
    LOG(tab);
    tab.append_row({-88, -22, -343});
    LOG(tab);

    return (0);
}
