/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/setup/sim.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/optics.hpp"
#include "gen/rng.hpp"

//  -- Utility --
#include "utl/colourmap.hpp"
#include "utl/file.hpp"

//  -- Classes --
#include "cls/graphical/scene.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Initialise a sim object from a json setup file.
         *
         *  @param  t_json Json setup file.
         */
        Sim::Sim(const data::Json& t_json) :
            m_loop_limit(t_json["optimisation"].parse_child<unsigned long int>("loop_limit")),
            m_roulette_weight(t_json["optimisation"]["roulette"].parse_child<double>("weight")),
            m_roulette_chambers(t_json["optimisation"]["roulette"].parse_child<double>("chambers")),
            m_aether(init_aether(t_json["simulation"]["aether"])),
            m_entity(init_entity(t_json["simulation"]["entities"])),
            m_light(init_light(t_json["simulation"]["lights"])),
            m_ccd(init_ccd(t_json["simulation"]["ccds"])),
            m_spectrometer(init_spectrometer(t_json["simulation"]["spectrometers"])),
            m_light_select(init_light_select()),
            m_root(std::make_unique<tree::Cell>(t_json["tree"].parse_child<unsigned int>("min_depth"),
                                                t_json["tree"].parse_child<unsigned int>("max_depth"),
                                                t_json["tree"].parse_child<unsigned int>("max_tri"),
                                                t_json["tree"].parse_child<math::Vec<3>>("min_bound"),
                                                t_json["tree"].parse_child<math::Vec<3>>("max_bound"), m_entity, m_light, m_ccd,
                                                m_spectrometer)),
            m_scatters(0.0, 100.0, 100, true),
            m_exit_weight(0.0, 1.0, 100, true),
            m_log_update_period(t_json["system"].parse_child<double>("log_update_period")),
            m_uniform_dist(0.0, 1.0)
        {
            // Validate settings.
            if (m_roulette_weight < 0.0)
            {
                ERROR("Value of m_roulette_weight is invalid.",
                      "Value of m_roulette_weight must be non-negative, but is: '" << m_roulette_weight << "'.");
            }
            if (m_roulette_chambers <= 1.0)
            {
                ERROR("Value of m_roulette_chambers is invalid.",
                      "Value of m_roulette_chambers must be greater than one, but is: '" << m_roulette_chambers << "'.");
            }

            // Check wavelengths are valid.
            double      light_min_bound = m_light[0].get_min_bound();
            double      light_max_bound = m_light[0].get_max_bound();
            for (size_t i               = 1; i < m_light.size(); ++i)
            {
                if (m_light[i].get_min_bound() > light_min_bound)
                {
                    light_min_bound = m_light[i].get_min_bound();
                }
                if (m_light[i].get_max_bound() < light_max_bound)
                {
                    light_max_bound = m_light[i].get_max_bound();
                }
            }

            double      mat_min_bound = m_aether.get_min_bound();
            double      mat_max_bound = m_aether.get_max_bound();
            for (size_t i             = 0; i < m_entity.size(); ++i)
            {
                if (m_entity[i].get_min_bound() > mat_min_bound)
                {
                    mat_min_bound = m_entity[i].get_min_bound();
                }
                if (m_entity[i].get_max_bound() < mat_max_bound)
                {
                    mat_max_bound = m_entity[i].get_max_bound();
                }
            }

            if ((light_min_bound < mat_min_bound) || (light_max_bound > mat_max_bound))
            {
                ERROR("Unable to construct setup::Sim object.",
                      "Range of wavelengths emitted by lights: '" << light_min_bound << "' - '" << light_max_bound
                                                                  << "', falls beyond the range of wavelengths handled by the materials:'"
                                                                  << mat_min_bound << "' - '" << mat_max_bound << "'.");
            }

            // Log tree properties.
            LOG("Total tree cells   : " << m_root->get_total_cells());
            LOG("Max leaf triangles : " << m_root->get_max_tri());
        }

        /**
         *  Initialise a sim object from a serialised json setup file.
         *
         *  @param  t_serial    Serialised json setup file.
         */
        Sim::Sim(const std::string& t_serial) :
            Sim(data::Json("sim", t_serial))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the aether material.
         *
         *  @param  t_json  Json setup file.
         *
         *  @return The initialised aether material.
         */
        phys::Material Sim::init_aether(const data::Json& t_json) const
        {
            LOG("Constructing aether");

            // Get file paths.
            const std::string mat_path = t_json.parse_child<std::string>("mat");
            VERB("Aether material: " << utl::strip_extension(utl::strip_path(mat_path)));

            return (phys::Material(utl::read(mat_path)));
        }

        /**
         *  Initialise the vector of entity objects.
         *
         *  @param  t_json Json setup file.
         *
         *  @return The initialise vector of entity objects.
         */
        std::vector<equip::Entity> Sim::init_entity(const data::Json& t_json) const
        {
            // Create the return vector of entities.
            std::vector<equip::Entity> r_entity;

            // Get list of entity names.
            std::vector<std::string> entity_name = t_json.get_child_names();

            // Construct the entity objects.
            for (size_t i = 0; i < entity_name.size(); ++i)
            {
                LOG("Constructing entity       : " << entity_name[i]);

                // Create a json object of the entity.
                const data::Json json_entity = t_json[entity_name[i]];

                // Get the transformation values.
                const auto   trans = json_entity.parse_child<math::Vec<3>>("trans", math::Vec<3>(0.0, 0.0, 0.0));
                const auto   dir   = json_entity.parse_child<math::Vec<3>>("dir", math::Vec<3>(0.0, 0.0, 1.0));
                const double rot   = math::deg_to_rad(json_entity.parse_child<double>("rot", 0.0));
                const auto   scale = json_entity.parse_child<math::Vec<3>>("scale", math::Vec<3>(1.0, 1.0, 1.0));

                // Get file paths.
                const std::string mesh_path = json_entity.parse_child<std::string>("mesh");
                const std::string mat_path  = json_entity.parse_child<std::string>("mat");

                // Print verbose information.
                VERB(entity_name[i] << " material: " << utl::strip_extension(utl::strip_path(mat_path)));
                VERB(entity_name[i] << " tree    : " << utl::strip_extension(utl::strip_path(mesh_path)));
                VERB(entity_name[i] << " trans   : " << trans);
                VERB(entity_name[i] << " dir     : " << dir);
                VERB(entity_name[i] << " rot     : " << rot);
                VERB(entity_name[i] << " scale   : " << scale);

                // Construct the entity object an add it to the vector of entities.
                r_entity.emplace_back(equip::Entity(geom::Mesh(utl::read(mesh_path), trans, dir, rot, scale),
                                                    phys::Material(utl::read(mat_path))));
            }

            return (r_entity);
        }

        /**
         *  Initialise the vector of light objects.
         *
         *  @param  t_json Json setup file.
         *
         *  @return The initialise vector of light objects.
         */
        std::vector<equip::Light> Sim::init_light(const data::Json& t_json) const
        {
            // Create the return vector of lights.
            std::vector<equip::Light> r_light;

            // Get list of light names.
            std::vector<std::string> light_name = t_json.get_child_names();

            // Construct the light objects.
            for (size_t i = 0; i < light_name.size(); ++i)
            {
                LOG("Constructing light        : " << light_name[i]);

                // Create a json object of the light.
                const data::Json json_light = t_json[light_name[i]];

                // Get the transformation values.
                const auto   trans = json_light.parse_child<math::Vec<3>>("trans", math::Vec<3>(0.0, 0.0, 0.0));
                const auto   dir   = json_light.parse_child<math::Vec<3>>("dir", math::Vec<3>(0.0, 0.0, 1.0));
                const double rot   = math::deg_to_rad(json_light.parse_child<double>("rot", 0.0));
                const auto   scale = json_light.parse_child<math::Vec<3>>("scale", math::Vec<3>(1.0, 1.0, 1.0));

                // Get light properties.
                const auto power = json_light.parse_child<double>("power");

                // Get file paths.
                const std::string mesh_path = json_light.parse_child<std::string>("mesh");
                const std::string spec_path = json_light.parse_child<std::string>("spec");

                // Print verbose information.
                VERB(light_name[i] << " material: " << utl::strip_extension(utl::strip_path(spec_path)));
                VERB(light_name[i] << " tree    : " << utl::strip_extension(utl::strip_path(mesh_path)));
                VERB(light_name[i] << " power   : " << power);
                VERB(light_name[i] << " trans   : " << trans);
                VERB(light_name[i] << " dir     : " << dir);
                VERB(light_name[i] << " rot     : " << rot);
                VERB(light_name[i] << " scale   : " << scale);

                // Construct the light object an add it to the vector of lights.
                r_light.emplace_back(
                    equip::Light(geom::Mesh(utl::read(mesh_path), trans, dir, rot, scale), phys::Spectrum(utl::read(spec_path)),
                                 power));
            }

            return (r_light);
        }

        /**
         *  Initialise the vector of ccd objects.
         *
         *  @param  t_json  Json setup file.
         *
         *  @return The initialised vector of ccd objects.
         */
        std::vector<detector::Ccd> Sim::init_ccd(const data::Json& t_json) const
        {
            // Create the return vector of ccds.
            std::vector<detector::Ccd> r_ccd;

            // Get list of ccd names.
            std::vector<std::string> ccd_name = t_json.get_child_names();

            // Construct the ccd objects.
            for (size_t i = 0; i < ccd_name.size(); ++i)
            {
                LOG("Constructing ccd          : " << ccd_name[i]);

                // Create a json object of the ccd.
                const data::Json json_ccd = t_json[ccd_name[i]];

                // Get the transformation values.
                const auto   trans = json_ccd.parse_child<math::Vec<3>>("trans", math::Vec<3>(0.0, 0.0, 0.0));
                const auto   dir   = json_ccd.parse_child<math::Vec<3>>("dir", math::Vec<3>(0.0, 0.0, 1.0));
                const double rot   = math::deg_to_rad(json_ccd.parse_child<double>("rot", 0.0));
                const auto   scale = json_ccd.parse_child<math::Vec<3>>("scale", math::Vec<3>(1.0, 1.0, 1.0));

                // Get ccd properties.
                const auto pix = json_ccd.parse_child<std::array<size_t, 2>>("pixel");
                const auto col = json_ccd.parse_child<bool>("col");

                // Print verbose information.
                VERB(ccd_name[i] << " trans   : " << trans);
                VERB(ccd_name[i] << " dir     : " << dir);
                VERB(ccd_name[i] << " rot     : " << rot);
                VERB(ccd_name[i] << " scale   : " << scale);
                VERB(ccd_name[i] << " pix     : " << pix);
                VERB(ccd_name[i] << " col     : " << col);

                // Construct the ccd object an add it to the vector of ccds.
                r_ccd.emplace_back(ccd_name[i], pix[X], pix[Y], col, trans, dir, rot, scale);
            }

            return (r_ccd);
        }

        /**
         *  Initialise the vector of spectrometer objects.
         *
         *  @param  t_json  Json setup file.
         *
         *  @return The initialised vector of spectrometer objects.
         */
        std::vector<detector::Spectrometer> Sim::init_spectrometer(const data::Json& t_json) const
        {
            // Create the return vector of spectrometers.
            std::vector<detector::Spectrometer> r_spectrometer;

            // Get list of spectrometer names.
            std::vector<std::string> spectrometer_name = t_json.get_child_names();

            // Construct the spectrometer objects.
            for (size_t i = 0; i < spectrometer_name.size(); ++i)
            {
                LOG("Constructing spectrometer : " << spectrometer_name[i]);

                // Create a json object of the spectrometer.
                const data::Json json_spectrometer = t_json[spectrometer_name[i]];

                // Get the transformation values.
                const auto   trans = json_spectrometer.parse_child<math::Vec<3>>("trans", math::Vec<3>(0.0, 0.0, 0.0));
                const auto   dir   = json_spectrometer.parse_child<math::Vec<3>>("dir", math::Vec<3>(0.0, 0.0, 1.0));
                const double rot   = math::deg_to_rad(json_spectrometer.parse_child<double>("rot", 0.0));
                const auto   scale = json_spectrometer.parse_child<math::Vec<3>>("scale", math::Vec<3>(1.0, 1.0, 1.0));

                // Get spectrometer properties.
                const auto range = json_spectrometer.parse_child<std::array<double, 2>>("range");
                const auto bins  = json_spectrometer.parse_child<size_t>("bins");

                // Get file paths.
                const std::string mesh_path = json_spectrometer.parse_child<std::string>("mesh");

                // Print verbose information.
                VERB(spectrometer_name[i] << " tree    : " << utl::strip_extension(utl::strip_path(mesh_path)));
                VERB(spectrometer_name[i] << " trans   : " << trans);
                VERB(spectrometer_name[i] << " dir     : " << dir);
                VERB(spectrometer_name[i] << " rot     : " << rot);
                VERB(spectrometer_name[i] << " scale   : " << scale);
                VERB(spectrometer_name[i] << " range   : " << range);
                VERB(spectrometer_name[i] << " bins    : " << bins);

                // Construct the spectrometer object an add it to the vector of spectrometers.
                r_spectrometer
                    .emplace_back(spectrometer_name[i], geom::Mesh(utl::read(mesh_path), trans, dir, rot, scale), range[0],
                                  range[1], bins);
            }

            return (r_spectrometer);
        }

        /**
         *  Construct the light index selector object.
         *
         *  @return The initialised light index selector.
         */
        random::Index Sim::init_light_select() const
        {
            // Create a vector of light powers.
            std::vector<double> power;
            for (size_t         i = 0; i < m_light.size(); ++i)
            {
                power.push_back(m_light[i].get_power());
            }

            return (random::Index(power));
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Report the total number of errors that occured during the simulation.
         */
        void Sim::get_error_report() const
        {
            // Calculate total error.
            const double total_error = m_error_loop + m_error_prox;

            if (total_error > 0.0)
            {
                WARN("Photon weight was lost.", "Total weight lost to proximity errors : " << m_error_prox);
                WARN("Photon weight was lost.", "Total weight lost to exceeding set loop limit : " << m_error_loop);
            }
            else
            {
                LOG("No errors occured during the photon loop.");
            }
        }


        //  -- Setters --
        /**
         *  Set the number of threads by initialising the thread progress vector.
         *
         *  @param  t_num_threads   Number of simulation threads.
         *
         *  @pre    t_num_threads must not be zero.
         */
        void Sim::set_num_threads(const unsigned int t_num_threads)
        {
            assert(t_num_threads != 0);
            m_thread_progress = std::vector<double>(t_num_threads, 0.0);

            // Random number generator initialisation.
            const auto seed = static_cast<size_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            LOG("Simulation seed: " << seed);
            for (size_t i = 0; i < t_num_threads; ++i)
            {
                m_rng_engine.emplace_back(seed + i);
            }
        }


        //  -- Saving --
        /**
         *  Save the tree images.
         *
         *  @param  t_output_dir    Directory to write the images to.
         *  @param  t_level         Level of depth resolution to save images with.
         */
        void Sim::save_tree_images(const std::string& t_output_dir, const size_t t_level) const
        {
            // Form the data cube.
            std::vector<std::vector<std::vector<double>>> data_cube = m_root->get_data_cube(t_level);

            // Normalise the data cube.
            double      max = 0.0;
            size_t      res = data_cube.size();
            for (size_t i   = 0; i < res; ++i)
            {
                for (size_t j = 0; j < res; ++j)
                {
                    for (size_t k = 0; k < res; ++k)
                    {
                        if (data_cube[i][j][k] > max)
                        {
                            max = data_cube[i][j][k];
                        }
                    }
                }
            }
            assert(max > 0.0);
            for (size_t i = 0; i < res; ++i)
            {
                for (size_t j = 0; j < res; ++j)
                {
                    for (size_t k = 0; k < res; ++k)
                    {
                        data_cube[i][j][k] /= max;
                    }
                }
            }

            // Save slices of the data cube.
            save_slices(t_output_dir, X, data_cube);
            save_slices(t_output_dir, Y, data_cube);
            save_slices(t_output_dir, Z, data_cube);
        }

        /**
         *  Save the slices of one dimension of the tree.
         *
         *  @param  t_output_dir    Directory to write the images to.
         *  @param  t_dimension     Dimension to be sliced.
         *  @param  t_data          Data to be sliced into images.
         *
         *  @pre    t_dimension must be less than three.
         */
        void Sim::save_slices(const std::string& t_output_dir, const size_t t_dimension,
                              const std::vector<std::vector<std::vector<double>>>& t_data) const
        {
            assert(t_dimension < 3);

            // Determine image resolution.
            size_t res = t_data.size();

            // Set dimensions.
            size_t      width, height, slice;
            std::string dim_name;
            switch (t_dimension)
            {
                case X:
                    width    = Y;
                    height   = Z;
                    slice    = X;
                    dim_name = "X";
                    break;
                case Y:
                    width    = X;
                    height   = Z;
                    slice    = Y;
                    dim_name = "Y";
                    break;
                case Z:
                    width    = X;
                    height   = Y;
                    slice    = Z;
                    dim_name = "Z";
                    break;
                default: ERROR("Unable to save tree slice images.",
                               "The given slice dimension: '" << t_dimension << "' is invalid.");
            }

            // Create sub-directory.
            const std::string sub_dir = t_output_dir + "tree_" + dim_name + "_slices/";
            utl::create_directory(sub_dir);

            // Write the images.
            for (size_t i = 0; i < res; ++i)
            {
                TEMP("Saving " + dim_name + " slices", 100.0 * i / res);

                // Create the image.
                data::Image img(res, res);

                // Write each pixel.
                for (size_t j = 0; j < res; ++j)
                {
                    for (size_t k = 0; k < res; ++k)
                    {
                        switch (t_dimension)
                        {
                            case X:
                                img.add_to_pixel(j, k, utl::colourmap::transform_rainbow(t_data[i][j][k]));
                                break;
                            case Y:
                                img.add_to_pixel(j, k, utl::colourmap::transform_rainbow(t_data[j][i][k]));
                                break;
                            case Z:
                                img.add_to_pixel(j, k, utl::colourmap::transform_rainbow(t_data[j][k][i]));
                                break;
                            default: ERROR("Unable to save tree slice images.",
                                           "The given slice dimension: '" << t_dimension << "' is invalid.");
                        }
                    }
                }

                // Save the image.
                img.save(sub_dir + dim_name + "_" + std::to_string(i) + ".ppm");
            }

            LOG("Grid " << dim_name << " slice image saving complete.");
        }

        /**
         *  Save the ccd images.
         *
         *  @param  t_output_dir    Directory to write the images to.
         */
        void Sim::save_ccd_images(const std::string& t_output_dir) const
        {
            // Get the maximum rgb values.
            double      max = 0.0;
            for (size_t i   = 0; i < m_ccd.size(); ++i)
            {
                std::array<double, 3> ccd_max = m_ccd[i].get_max_value();
                for (size_t           j       = 0; j < 3; ++j)
                {
                    if (ccd_max[j] > max)
                    {
                        max = ccd_max[j];
                    }
                }
            }

            // Check maximum was not zero.
            if ((!m_ccd.empty()) && (max <= 0.0))
            {
                WARN("Unable to save ccd images.", "Maximum pixel value was less than, or equal to, zero.");

                return;
            }

            // Save each ccd image.
            for (size_t i = 0; i < m_ccd.size(); ++i)
            {
                m_ccd[i].save(t_output_dir, max);
            }

            LOG("CCD image saving complete.");
        }

        /**
         *  Save the spectrometer data.
         *
         *  @param  t_output_dir    Directory to write the images to.
         */
        void Sim::save_spectrometer_data(const std::string& t_output_dir) const
        {
            // Save each spectrometer's data.
            for (size_t i = 0; i < m_spectrometer.size(); ++i)
            {
                m_spectrometer[i].save(t_output_dir);
            }

            LOG("Spectrometer data saving complete.");
        }

        /**
         *  Save the histogram data.
         *
         *  @param  t_output_dir    Directory to write the histograms to.
         */
        void Sim::save_histogram_data(const std::string& t_output_dir) const
        {
            // Save the scattering data.
            m_scatters.save(t_output_dir + "scatters.dat");

            // Save the exit weight data.
            m_exit_weight.save(t_output_dir + "weight.dat");
        }


        //  -- Rendering --
        /**
         *  Render a scene of the current simulation.
         */
        void Sim::render() const
        {
#ifdef ENABLE_GRAPHICS
            // Create a graphical scene.
            graphical::Scene scene;

            // Add objects to the scene.
            scene.add_light_vector(m_light);
            scene.add_entity_vector(m_entity);
            scene.add_ccd_vector(m_ccd);
            scene.add_spectrometer_vector(m_spectrometer);
#ifdef ENABLE_PHOTON_PATHS
            scene.add_photon_vector(m_path);
#endif
            scene.add_tree(m_root);

            // Render the scene.
            while (!scene.should_close())
            {
                scene.handle_input();
                scene.render();
            }
#else
            WARN("Unable to render scene.", "GRAPHICS compile-time option has been set to off.");
#endif
        }


        //  -- Simulation --
        /**
         *  Run a number of photons through the simulation.
         *
         *  @param  t_num_phot      The number of photons to run.
         *  @param  t_thread_index  Index of the thread running this batch of photons.
         */
        void Sim::run_photons(const unsigned long int t_num_phot, const size_t t_thread_index)
        {
            // Run each photon through the simulation.
            for (unsigned long int i = 0; i < t_num_phot; ++i)
            {
                // Set loop progress.
                m_thread_progress[t_thread_index] = (100.0 * i) / t_num_phot;

                // Print loop progress.
                log_progress();

                // Emit a new photon.
                phys::Photon phot = m_light[m_light_select.gen_index()].gen_photon(m_aether);

                // Initialise tracked properties.
                tree::Cell* cell = nullptr;             //! Pointer to current cell containing the photon.
                double            cell_energy = 0.0;    //! Energy to be added to cell total when exiting cell.
                unsigned long int loops       = 0;      //! Number of loops made of the while loop.
                unsigned long int num_scat    = 0;      //! Number of photon scatterings made.

                // Check if photon is within a tree cell.
                if (!m_root->is_within(phot.get_pos()))
                {
                    WARN("Unable to simulate photon.", "Photon does not begin with the tree.");
                    goto kill_photon;
                }
                else
                {
                    cell = m_root->get_leaf(phot.get_pos());
                    assert(cell != nullptr);
                }

                // Loop until exit condition is met.
                while (true)
                {
                    // Increment loop counter.
                    ++loops;

                    // Kill if photon is stuck.
                    if (loops > m_loop_limit)
                    {
                        m_counter_mutex.lock();
                        m_error_loop += phot.get_weight();
                        m_counter_mutex.unlock();

                        goto kill_photon;
                    }

                    // Roulette optimisation.
                    if (phot.get_weight() <= m_roulette_weight)
                    {
                        if (m_uniform_dist(m_rng_engine[t_thread_index]) <= (1.0 / m_roulette_chambers))
                        {
                            phot.multiply_weight(m_roulette_chambers);
                        }
                        else
                        {
                            goto kill_photon;
                        }
                    }

                    // Determine event distances.
                    event  event_type;              //! Event type.
                    double dist;                    //! Distance to the event.
                    size_t equip_index, tri_index;  //! Indices of hit equipment and triangle if hit at all.
                    std::tie(event_type, dist, equip_index, tri_index) = determine_event(phot, cell, t_thread_index);

                    // Track properties.
                    cell_energy += dist * phot.get_weight();

                    // Perform the event.
                    switch (event_type)
                    {
                        // Scattering event.
                        case event::SCATTER:
                        {
                            ++num_scat;

                            // Move to the scattering point.
                            phot.move(dist);

                            // Scatter.
                            phot.rotate(rng::henyey_greenstein(phot.get_anisotropy()),
                                        m_uniform_dist(m_rng_engine[t_thread_index]) * 2.0 * M_PI);

                            // Reduce weight by the albedo.
                            phot.multiply_weight(phot.get_albedo());

                            // Check that the photon still has statistical weight.
                            if (phot.get_weight() <= 0.0)
                            {
                                goto kill_photon;
                            }

                            break;
                        }

                            // Cell boundary crossing.
                        case event::CELL_CROSS:
                        {
                            // Increment cell-tracked properties.
                            m_cell_mutex.lock();
                            cell->add_energy(cell_energy);
                            m_cell_mutex.unlock();
                            cell_energy = 0.0;

                            // Move just past the cell boundary point.
                            phot.move(dist + SMOOTHING_LENGTH);

                            // Check if photon has now exited the tree.
                            if (!m_root->is_within(phot.get_pos()))
                            {
                                goto kill_photon;
                            }

                            // Get new cell pointer if still within the tree.
                            cell = m_root->get_leaf(phot.get_pos());

                            break;
                        }

                            // Entity collision.
                        case event::ENTITY_HIT:
                        {
                            // Check for close-collision.
                            if (dist < SMOOTHING_LENGTH)
                            {
                                m_counter_mutex.lock();
                                m_error_prox += phot.get_weight();
                                m_counter_mutex.unlock();

                                goto kill_photon;
                            }

                            // Get the normal of the hit location.
                            math::Vec<3> norm = m_entity[equip_index].get_mesh().get_tri(tri_index)
                                                                     .get_norm(phot.get_pos() + (phot.get_dir() * dist));

                            // If entity normal is facing away, multiply it by -1.
                            if ((phot.get_dir() * norm) > 0.0)
                            {
                                norm *= -1.0;
                            }
                            assert(norm.is_normalised());

                            // Determine the material indices.
                            int  index_i, index_t;
                            bool exiting      = phot.get_entity_index() == static_cast<int>(equip_index);
                            if (exiting)    // Exiting the current entity.
                            {
                                index_i = static_cast<int>(equip_index);
                                index_t = phot.get_prev_entity_index();
                            }
                            else            // Entering a new entity.
                            {
                                index_i = phot.get_entity_index();
                                index_t = static_cast<int>(equip_index);
                            }
                            assert(index_i != index_t);

                            // Get references to the materials.
                            const phys::Material& mat_i = (index_i == -1) ? m_aether : m_entity[static_cast<size_t>(index_i)]
                                .get_mat();
                            const phys::Material& mat_t = (index_t == -1) ? m_aether : m_entity[static_cast<size_t>(index_t)]
                                .get_mat();

                            // Get refractive indices of the materials.
                            const double n_i = mat_i.get_ref_index(phot.get_wavelength());
                            const double n_t = mat_t.get_ref_index(phot.get_wavelength());

                            // Calculate angle of incidence.
                            const double a_i = std::acos(-phot.get_dir() * norm);
                            assert((a_i >= 0.0) && (a_i < (M_PI / 2.0)));

                            // Calculate reflectance probability.
                            double reflectance;
                            if (std::sin(a_i) >= (n_t / n_i))   // Total internal reflectance.
                            {
                                reflectance = 1.0;
                            }
                            else                                // Specular reflectance.
                            {
                                reflectance = optics::reflection_prob(a_i, n_i, n_t);
                            }
                            assert((reflectance >= 0.0) && (reflectance <= 1.0));

                            if (m_uniform_dist(m_rng_engine[t_thread_index]) <= reflectance)   // Reflect.
                            {
                                // Move to just before the entity boundary.
                                phot.move(dist - SMOOTHING_LENGTH);

                                // Reflect the photon.
                                phot.set_dir(optics::reflection_dir(phot.get_dir(), norm));
                            }
                            else                                // Refract.
                            {
                                // Move to just past the entity boundary.
                                phot.move(dist + SMOOTHING_LENGTH);

                                // Refract the photon.
                                phot.set_dir(optics::refraction_dir(phot.get_dir(), norm, n_i / n_t));

                                // Determine new optical properties.
                                if (exiting)                    // Exiting material.
                                {
                                    phot.pop_entity_index();
                                }
                                else                            // Entering material.
                                {
                                    phot.push_entity_index(index_t);
                                }
                                phot.set_opt(index_t == -1 ? m_aether : m_entity[static_cast<size_t>(index_t)].get_mat());
                            }

                            break;
                        }

                            // Ccd detector hit.
                        case event::CCD_HIT:
                        {
                            // Move to the hit location.
                            phot.move(dist);

                            // Get normal of the hit location.
                            const math::Vec<3> norm = m_ccd[equip_index].get_mesh().get_tri(tri_index).get_norm(phot.get_pos());

                            // Check if photon hits the front of the detector.
                            if ((phot.get_dir() * norm) < 0.0)
                            {
                                m_ccd_mutex.lock();
                                m_ccd[equip_index].add_hit(phot.get_pos(), phot.get_weight(), phot.get_wavelength());
                                m_ccd_mutex.unlock();
                            }

                            // Kill the absorbed photon.
                            goto kill_photon;
                        }

                            // Spectrometer detector hit.
                        case event::SPECTROMETER_HIT:
                        {
                            // Move to the hit location.
                            phot.move(dist);

                            // Get normal of the hit location.
                            const math::Vec<3> norm = m_spectrometer[equip_index].get_mesh().get_tri(tri_index)
                                                                                 .get_norm(phot.get_pos());

                            // Check if photon hits the front of the detector.
                            if ((phot.get_dir() * norm) < 0.0)
                            {
                                m_spectrometer_mutex.lock();
                                m_spectrometer[equip_index].add_hit(phot.get_wavelength(), phot.get_weight());
                                m_spectrometer_mutex.unlock();
                            }

                            // Kill the absorbed photon.
                            goto kill_photon;
                        }
                    }
                }

                // Photon death label.
                kill_photon:;

                // Add photon data to histograms.
                m_hist_mutex.lock();
                m_scatters.bin_value(num_scat, phot.get_weight());
                m_exit_weight.bin_value(phot.get_weight());
                m_hist_mutex.unlock();

#ifdef ENABLE_PHOTON_PATHS
                // Add the photon path.
                m_path_mutex.lock();
                m_path.push_back(phot.get_path());
                m_path_mutex.unlock();
#endif
            }
        }

        /**
         *  Determine the next event a photon will undergo.
         *
         *  @param  t_phot          Photon whose event will be determined.
         *  @param  t_cell          Cell the photon is currently within.
         *  @param  t_thread_index  Index of the thread running this batch of photons.
         *
         *  @post   Return distance must be positive.
         *  @post   Equipment index must not be a NaN if not a scattering or cell crossing event.
         *  @post   Equipment triangle index must not be a NaN if not a scattering or cell crossing event.
         *
         *  @return A tuple containing, the type of event, distance to event, indices of equipment and triangle involved.
         */
        std::tuple<Sim::event, double, size_t, size_t> Sim::determine_event(const phys::Photon& t_phot,
                                                                            const tree::Cell* t_cell,
                                                                            const size_t t_thread_index)
        {
            // Determine scatter distance.
            const double scat_dist = -std::log(m_uniform_dist(m_rng_engine[t_thread_index]) / t_phot.get_interaction());
            assert(scat_dist > 0.0);

            // Determine the cell distance.
            const double cell_dist = t_cell->get_dist_to_wall(t_phot.get_pos(), t_phot.get_dir());
//            assert(cell_dist > SMOOTHING_LENGTH);

            // Check for entity collision.
            bool   entity_hit;
            double entity_dist;
            size_t entity_index, entity_tri_index;
            std::tie(entity_hit, entity_dist, entity_index, entity_tri_index) = t_cell
                ->entity_dist(t_phot.get_pos(), t_phot.get_dir());

            // Check for ccd collision.
            bool   ccd_hit;
            double ccd_dist;
            size_t ccd_index, ccd_tri_index;
            std::tie(ccd_hit, ccd_dist, ccd_index, ccd_tri_index) = t_cell->ccd_dist(t_phot.get_pos(), t_phot.get_dir());

            // Check for spectrometer collision.
            bool   spectrometer_hit;
            double spectrometer_dist;
            size_t spectrometer_index, spectrometer_tri_index;
            std::tie(spectrometer_hit, spectrometer_dist, spectrometer_index, spectrometer_tri_index) = t_cell
                ->spectrometer_dist(t_phot.get_pos(), t_phot.get_dir());

            // Determine which distance is shortest.
            std::array<double, 5> dist({{scat_dist, cell_dist, entity_dist, ccd_dist, spectrometer_dist}});
            switch (std::distance(std::begin(dist), std::min_element(std::begin(dist), std::end(dist))))
            {
                case 0:
                    assert(scat_dist > 0.0);
                    return (std::tuple<event, double, size_t, size_t>(event::SCATTER, scat_dist,
                                                                      std::numeric_limits<size_t>::signaling_NaN(),
                                                                      std::numeric_limits<size_t>::signaling_NaN()));
                case 1:
                    assert(cell_dist > 0.0);
                    return (std::tuple<event, double, size_t, size_t>(event::CELL_CROSS, cell_dist,
                                                                      std::numeric_limits<size_t>::signaling_NaN(),
                                                                      std::numeric_limits<size_t>::signaling_NaN()));
                case 2:
                    assert(entity_dist > 0.0);
                    assert(!std::isnan(entity_index));
                    assert(!std::isnan(entity_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::ENTITY_HIT, entity_dist, entity_index,
                                                                      entity_tri_index));
                case 3:
                    assert(ccd_dist > 0.0);
                    assert(!std::isnan(ccd_index));
                    assert(!std::isnan(ccd_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::CCD_HIT, ccd_dist, ccd_index, ccd_tri_index));
                case 4:
                    assert(spectrometer_dist > 0.0);
                    assert(!std::isnan(spectrometer_index));
                    assert(!std::isnan(spectrometer_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::SPECTROMETER_HIT, spectrometer_dist,
                                                                      spectrometer_index, spectrometer_tri_index));
                default: ERROR("Unable to simulate photon.", "Code should be unreachable.");
            }
        }

        /**
         *  Log the progress of all threads.
         *  Only print if more time than m_log_update_period stipulates.
         */
        void Sim::log_progress() const
        {
            // Return if minimum update time has not yet passed.
            static std::chrono::steady_clock::time_point last_update;
            const std::chrono::steady_clock::time_point  cur_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::duration<double>>(cur_time - last_update).count() < m_log_update_period)
            {
                return;
            }
            last_update                   = cur_time;

            // Log the progress of all loops.
            std::stringstream progress;
            static const auto print_width = static_cast<int>(term::TEXT_WIDTH / m_thread_progress.size());
            assert(print_width > 2);
            for (size_t i = 0; i < m_thread_progress.size(); ++i)
            {
                progress << std::setw(print_width - 2) << m_thread_progress[i] << "% ";
            }

            // Print the progress string.
            LOG(progress.str());
        }



    } // namespace setup
} // namespace arc
