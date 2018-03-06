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
#include <unistd.h>

//  -- General --
#include "gen/config.hpp"
#include "gen/math.hpp"

//  -- Utility --
#include "utl/file.hpp"

//  -- Classes --
#include "cls/setup/sim.hpp"



//  == FUNCTION PROTOTYPES ==
//  -- File --
void save_run_info(const std::string& t_output_dir);



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
    const std::string output_dir = "output_" + setup["system"]
        .parse_child<std::string>("output_dir_name") + "_" + arc::utl::create_timestamp("%Y%m%d%H%M%S") + "/";
    arc::utl::create_directory(output_dir);
    LOG("Output directory: " << output_dir);

    // Save run information files.
    save_run_info(output_dir);

    // Set the program seed.
    arc::rng::seed(setup["system"].parse_child("seed", static_cast<arc::random::Uniform::base>(time(nullptr))));

    // Construct the simulation object.
    SEC("Constructing Simulation");
    arc::setup::Sim pdt(setup);

    // Render the simulation scene.
    if (setup["system"].parse_child<bool>("pre_render", false))
    {
        pdt.render();
    }

    // Run the simulation.
    SEC("Running Simulation");

    // Get the number of photons to run.
    const auto num_phot                  = setup["simulation"].parse_child<unsigned long int>("num_phot");
    LOG("Number of photons to run: " << num_phot);

    // Initialise the threads.
    std::vector<std::thread> threads;
    const unsigned int       num_threads = std::min(std::thread::hardware_concurrency(),
                                                    setup["system"].parse_child<unsigned int>("max_threads", 1));
    if (num_threads == 0)
    {
        ERROR("Unable to run simulation.", "Number of threads can not be zero.");
    }
    LOG("Number of threads: " << num_threads);
    pdt.set_num_threads(num_threads);

    // Get start time of simulation.
    const std::chrono::steady_clock::time_point sim_start_time = std::chrono::steady_clock::now();

    // Set off the threads.
    const unsigned long int num_phot_per_thread = num_phot / num_threads;
    for (unsigned long int  i                   = 0; i < num_threads; ++i)
    {
        threads.emplace_back(&arc::setup::Sim::run_photons, &pdt, num_phot_per_thread, i);
    }

    // Wait for each thread to finish.
    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    // Calculate runtime.
    const double sim_runtime = std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now() - sim_start_time).count();
    LOG("Simulation runtime: " << arc::utl::create_time_string(sim_runtime));
    LOG("Ave photon runtime: " << arc::utl::create_time_string(sim_runtime / num_phot));

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
    if (setup["system"].parse_child<bool>("post_render", false))
    {
        pdt.render();
    }

    return (0);
}



//  == FUNCTIONS ==
//  -- File --
/**
 *  Save the current run information.
 *
 *  @param  t_output_dir    Data output directory path.
 */
void save_run_info(const std::string& t_output_dir)
{
    // Create the file handle.
    arc::file::Handle run_info(t_output_dir + "run_info.txt", std::fstream::out);

    // Write the build information.
    run_info << "Build information\n";
    run_info << "Branch   : " << arc::config::BUILD_BRANCH << "\n";
    run_info << "Hash     : " << arc::config::BUILD_HASH << "\n";
    run_info << "Patch    : " << arc::config::BUILD_PATCH << "\n";
    run_info << "Compiler : " << arc::config::BUILD_COMPILER << "\n";
    run_info << "Type     : " << arc::config::BUILD_TYPE << "\n";
    run_info << "Date     : " << arc::config::BUILD_DATE << "\n";

    // Write current working directory.
    char buffer[1024];
    run_info << "\nWorking directory: " << getcwd(buffer, sizeof(buffer)) << "\n";
}
