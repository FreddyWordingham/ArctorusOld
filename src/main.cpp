/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"
#include "gen/rng.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/setup/sim.hpp"



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
    arc::math::Mat<4, 4> mat(
        {{{{0.416046, 0.497469, 0.206966, 0.219239}}, {{0.438962, 0.289681, 0.764902, 0.135496}}, {{0.211479, 0.217616, 0.795794, 0.517415}}, {{0.191503, 0.96364, 0.724689, 0.130287}}}});
    //arc::math::Mat<2, 2> mat({{{{0.0, 1.0}}, {{2.0, 3.0}}}});
    VAL(mat);
    VAL(arc::math::inverse(mat));

    exit(1);

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

    // Render the simulation scene.
    if (setup.parse_child<bool>("pre_render", false))
    {
        pdt.render();
    }

    // Run the simulation.
    pdt.run();

    // Save grid data.
    pdt.save_grid_images(setup.parse_child<std::string>("output_dir"));

    // Save ccd data.
    pdt.save_ccd_images(setup.parse_child<std::string>("output_dir"));

    // Render the simulation scene.
    if (setup.parse_child<bool>("post_render", false))
    {
        pdt.render();
    }

    return (0);
}
