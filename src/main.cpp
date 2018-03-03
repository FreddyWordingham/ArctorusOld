/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"

//  -- Utility --
#include "utl/file.hpp"

//  -- Classes --
#include "cls/setup/sim.hpp"


#include <thread>
/*


class Wallet
{
    int        mMoney;
    std::mutex mutex;
  public:
    Wallet() :
        mMoney(0) {}
    int getMoney() { return mMoney; }
    void addMoney(int money)
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        for (int                    i = 0; i < money; ++i)
        {
            mMoney++;
        }
    }
};



int testMultithreadedWallet()
{
    Wallet                   walletObject;
    std::vector<std::thread> threads;
    for (int                 i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}*/




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
/*    int      val = 0;
    for (int k   = 0; k < 1000; k++)
    {
        if ((val = testMultithreadedWallet()) != 5000)
        {
            std::cout << "Error at count = " << k << " Money in Wallet = " << val << std::endl;
        }
    }

    return 0;*/



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
    const unsigned long int num_phot     = setup.parse_child<unsigned long int>("num_phot");
    LOG("Number of photons to run: " << num_phot);
    std::vector<std::thread> threads;
    const size_t             num_threads = std::thread::hardware_concurrency();
    LOG("Number of threads: " << num_threads);

    const unsigned long int num_phot_per_thread = num_phot / num_threads;
    for (unsigned long int  i                   = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread(&arc::setup::Sim::run_photons, &pdt, num_phot_per_thread));
    }
    for (int                i                   = 0; i < threads.size(); i++)
    {
        threads.at(i).join();
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

    /*const std::string name("intralipid_000-5");
    const double conc = 00.5 / 100.0;
    const double soy_conc = conc;
    const double water_conc = 1.0 - conc;
    VAL(soy_conc);
    VAL(water_conc);

    std::vector<double> w(601), n(601), a(601), s(601), g(601);

    for (size_t i = 0; i <= 600; ++i)
    {
        const double lambda = i + 400.0;

        w[i] = lambda * 1E-9;

        const double n_water = 1.311 + (1.154e+4 / arc::math::square(lambda)) + (-1.132e9/arc::math::square(arc::math::square(lambda)));
        const double n_soy = 1.451 + (1.154e+4 / arc::math::square(lambda)) + (-1.132e9/arc::math::square(arc::math::square(lambda)));
        n[i] = (n_soy * conc) + (n_water * (1.0 - conc));

        const double a_water = 3.066e+5 / (1.0 + std::exp(-1.0 * ((lambda - 1.770e+3)/5.413e+1)));
        const double a_soy = 1.171e+5 / (1.0 + std::exp(-1.0 * ((lambda + 3.210e+2)/-3.659e+1)));
        a[i] = (((0.88 * a_water) + (0.12 * a_soy)) * 1e+3) * soy_conc;

        s[i] = ((3.873e+8 * std::pow(lambda, -2.397e+0)) * 1e+3) * soy_conc;

        g[i] = 1.090e+0 + (-6.812e-4 * lambda);
    }

    arc::data::Table mat;
    mat.append_col(arc::data::Column("w", w));
    mat.append_col(arc::data::Column("n", n));
    mat.append_col(arc::data::Column("a", a));
    mat.append_col(arc::data::Column("s", s));
    mat.append_col(arc::data::Column("g", g));

    mat.save(name);*/

    return (0);
}
