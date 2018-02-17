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
#include "cls/data/json.hpp"
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
    /*// Check the number of command line arguments.
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


    const arc::math::Vec<3> center({{-0.0001, -0.0001, -0.0001}});
    const double width = (1.0/3.0) + 0.00001;
    const arc::math::Vec<3> half_size({{width, width, width}});


    const arc::math::Vec<3> pos_0({{0.0, 0.0, 1.0}});
    const arc::math::Vec<3> pos_1({{1.0, 0.0, 0.0}});
    const arc::math::Vec<3> pos_2({{0.0, 1.0, 0.0}});

    const arc::geom::Triangle tri({{arc::geom::Vertex(pos_0, arc::math::Vec<3>({{0.0, 0.0, 1.0}})), arc::geom::Vertex(pos_1, arc::math::Vec<3>({{0.0, 0.0, 1.0}})), arc::geom::Vertex(pos_2, arc::math::Vec<3>({{0.0, 0.0, 1.0}}))}});

    VAL(arc::math::tri_cuboid_overlap(center, half_size, tri));

    return (0);
}
