/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"

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
    pdt.save_grid_images();

    // Save ccd data.
    pdt.save_ccd_images();

    // Save spectrometer data.
    pdt.save_spectrometer_data();

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
