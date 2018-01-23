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

    arc::data::Table tab(arc::file::read("table.dat"));

    VAL(tab);

    VAL(tab.get_num_cols());
    VAL(tab.get_num_rows());

    for (size_t i = 0; i < 4; ++i)
    {
        tab[i][i]     = 0.0;
        tab[i][i + 1] = 1.0;
    }

    VAL(tab);

    return (0);
}
