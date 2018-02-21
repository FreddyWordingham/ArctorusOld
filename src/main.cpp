/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/rng.hpp"
#include "gen/math.hpp"

//  -- Classes --
#include "cls/setup/sim.hpp"

#include "cls/data/image.hpp"


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
    arc::data::Image img(40 * 2, 20 * 2);

    for (size_t i = 0; i < 20; ++i)
    {
        img.add_to_pixel(i, i, {{1.0, 1.0, 1.0}});
    }

    img.save("test.ppm", 1.0);

/*
    // Check the number of command line arguments.
    if (t_argc != 2)
    {
        ERROR("Invalid number of command line arguments passed.", "./path/to/arctorus <parameters.json>");
    }

    // Convert first command line argument to a string.
    std::string parameters_filepath(t_argv[1]);
    LOG("Setup file: '" << parameters_filepath << "'.");

    // Create the setup json file.
    const arc::data::Json setup("setup_file", arc::file::read(parameters_filepath));

    // Set the program seed.
    arc::rng::seed(setup.parse_child("seed", static_cast<arc::random::Uniform::base>(time(nullptr))));

    // Construct the simulation object.
    arc::setup::Sim pdt(setup);

    // Run the simulation.
    pdt.run();

    // Render the simulation scene.
    pdt.render();*/

    return (0);
}
