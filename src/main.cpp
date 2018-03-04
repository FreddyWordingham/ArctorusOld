/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <algorithm>
#include <thread>

//  -- General --
#include "gen/math.hpp"

//  -- Utility --
#include "utl/file.hpp"

//  -- Classes --
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
    SEC("Initialising Arctorus");

    // Check the number of command line arguments.
    if (t_argc != 2)
    {
        ERROR("Invalid number of command line arguments passed.", "./path/to/arctorus <parameters.json>");
    }

    // Convert first command line argument to a string.
    const std::string parameters_filepath(t_argv[1]);
    LOG("Setup file: '" << parameters_filepath << "'.");

    // Create the setup json file.
    const arc::data::Json setup("setup_file", arc::utl::read(parameters_filepath));

    // Create output directory and check it was created successfully,
    const std::string output_dir = "output_" + setup
        .parse_child<std::string>("output_dir_name") + "_" + arc::utl::create_timestamp("%Y%m%d%H%M%S") + "/";
    arc::utl::create_directory(output_dir);

    // Set the program seed.
    arc::rng::seed(setup.parse_child("seed", static_cast<arc::random::Uniform::base>(time(nullptr))));

    // Construct the simulation object.
    SEC("Constructing Simulation");
    arc::setup::Sim pdt(setup);

    // Render the simulation scene.
    if (setup.parse_child<bool>("pre_render", false))
    {
        pdt.render();
    }

    // Run the simulation.
    SEC("Running Simulation");

    // Get the number of photons to run.
    const unsigned long int num_phot     = setup.parse_child<unsigned long int>("num_phot");
    LOG("Number of photons to run: " << num_phot);

    // Initialise the threads.
    std::vector<std::thread> threads;
    const unsigned int       num_threads = std::min(std::thread::hardware_concurrency(),
                                                    setup.parse_child<unsigned int>("max_threads"));
    if (num_threads == 0)
    {
        ERROR("Unable to run simulation.", "Number of threads can not be zero.");
    }
    LOG("Number of threads: " << num_threads);

    // Set off the threads.
    const unsigned long int num_phot_per_thread = num_phot / num_threads;
    for (unsigned long int  i                   = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread(&arc::setup::Sim::run_photons, &pdt, num_phot_per_thread));
    }

    // Wait for each thread to finish.
    for (size_t             i                   = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

//    pdt.run_photons(num_phot);

    // Save grid data.
    SEC("Saving Data");
    const std::string grid_images_dir = output_dir + "grid_images/";
    arc::utl::create_directory(grid_images_dir);
    pdt.save_grid_images(grid_images_dir);

    // Save ccd data.
    const std::string ccd_images_dir = output_dir + "ccd_images/";
    arc::utl::create_directory(ccd_images_dir);
    pdt.save_ccd_images(ccd_images_dir);

    // Save spectrometer data.
    const std::string spectrometer_data_dir = output_dir + "spectrometer_data/";
    arc::utl::create_directory(spectrometer_data_dir);
    pdt.save_spectrometer_data(spectrometer_data_dir);

    // Render the simulation scene.
    if (setup.parse_child<bool>("post_render", false))
    {
        pdt.render();
    }

    return (0);
}
