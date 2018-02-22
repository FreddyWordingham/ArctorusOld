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
        {{{{0.32242, 0.988869, 0.975952, 0.968718}}, {{0.702071, 0.709838, 0.733454, 0.749993}}, {{0.236788, 0.0344567, 0.685422, 0.108697}}, {{0.805686, 0.750529, 0.462761, 0.66285}}}});
    //arc::math::Mat<2, 2> mat({{{{0.0, 1.0}}, {{2.0, 3.0}}}});
    VAL(mat);
    VAL(arc::math::minors(mat));

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
