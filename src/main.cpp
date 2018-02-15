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
 *  @param  t_argc  Command line argument count.
 *  @param  t_argv  Command line argument vector.
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

    // Convert first command line argument to a string.
    std::string parameters_filepath(t_argv[1]);
    LOG("Setup file: '" << parameters_filepath << "'.");

    // Construct the simulation object.
    setup::Sim pdt(file::read(parameters_filepath));

    // Render the simulation scene.
    pdt.render();

    return (0);
}
