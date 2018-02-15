/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <vector>
#include <cls/data/histogram.hpp>

//  -- General --
#include "gen/math.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/setup/sim.hpp"



//  == NAMESPACE ==
using namespace arc;



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main(const int t_argc, const char** t_argv)
{
    // Check the number of command line arguments.
    if (t_argc != 2)
    {
        ERROR("Invalid number of command line arguments passed.", "./path/to/arctorus <parameters.json>");
    }

    LOG("Hello world!");

    setup::Sim pdt(file::read("parameters.json"));

    pdt.render();

    return (0);
}
