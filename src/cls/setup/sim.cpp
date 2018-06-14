/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/setup/sim.hpp"

// File Writing
#include <iostream>
#include <fstream>
using namespace std;
ofstream myfile;


//  == INCLUDES ==
//  -- General --
#include "gen/optics.hpp"

//  -- Utility --
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
            m_grid(t_json["simulation"]["grid"].parse_child<math::Vec<3>>("min"),
                   t_json["simulation"]["grid"].parse_child<math::Vec<3>>("max"),
                   t_json["simulation"]["grid"].parse_child<std::array<size_t, 3>>("cells"), m_entity, m_light, m_ccd,
                   m_spectrometer),
            m_log_update_period(t_json["system"].parse_child<double>("log_update_period"))
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
                VERB(entity_name[i] << " mesh    : " << utl::strip_extension(utl::strip_path(mesh_path)));
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
                VERB(light_name[i] << " mesh    : " << utl::strip_extension(utl::strip_path(mesh_path)));
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
                VERB(spectrometer_name[i] << " mesh    : " << utl::strip_extension(utl::strip_path(mesh_path)));
                VERB(spectrometer_name[i] << " trans   : " << trans);
                VERB(spectrometer_name[i] << " dir     : " << dir);
                VERB(spectrometer_name[i] << " rot     : " << rot);
                VERB(spectrometer_name[i] << " scale   : " << scale);
                VERB(spectrometer_name[i] << " range   : " << range);
                VERB(spectrometer_name[i] << " bins    : " << bins);

                // Construct the spectrometer object and add it to the vector of spectrometers.
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
        }


        //  -- Saving --
        /**
         *  Save the grid images.
         *
         *  @param  t_output_dir    Directory to write the images to.
         */
        void Sim::save_grid_images(const std::string& t_output_dir) const
        {
            m_grid.save_images(t_output_dir);
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
                m_ccd[i].save_pos_data("output_Everall04_" + std::to_string(i) + ".dat");
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
            scene.add_grid(m_grid);

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
            unsigned long int total_raman_count = 0;    //! Total number of Raman scatters that occur.
            unsigned long int escapee = 0;              //! Number of photons escaping anywhere except the detector.
            unsigned long int correct_exit = 0;         //! Number of photons exiting via the detector.
            unsigned long int raman_correct_exit = 0;   //! Number of Raman photons exiting via the detector.
            unsigned long int killed = 0;               //! Number of photons exiting via maxing the loop limit.
            unsigned long int raman_killed = 0;         //! Number of Raman photons exiting via maxing the loop limit.
            unsigned long int raman_escapee = 0;        //! Number of Raman photons exiting anywhere except the detector.

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
                mesh::Cell* cell = nullptr;             //! Pointer to current cell containing the photon.
                double            cell_energy = 0.0;    //! Energy to be added to cell total when exiting current cell.
                unsigned long int loops       = 0;      //! Number of loops made of the while loop.
                unsigned long int raman_count = 0;      //! Number of Raman scatters that occur.
                double depth = -10.0;                   //! Depth of Raman photon generation.
                unsigned long int loopcount = 0;        //! Final number of loops made before exiting.

                // Check if photon is within a grid cell.
                if (!m_grid.is_within(phot.get_pos()))
                {
                    WARN("Unable to simulate photon.", "Photon does not begin within the grid.");
                    goto kill_photon;
                }
                else
                {
                    cell = &m_grid.get_cell(phot.get_pos());
                    assert(cell != nullptr);
                }

                // Loop until exit condition is met.
                while (true)
                {
                    double x = 40E-6;

                    // Kill if photon is stuck.
                    if (loops > m_loop_limit)
                    {
                        //WARN("Photon killed early.", "Number of loops exceeded set limit.");
                        loopcount = loops;
                        ++killed;
                        if (raman_count > 0)
                        {
                            ++raman_killed;
                        }
                        goto kill_photon;
                    }

                    // Roulette optimisation.
                    if (phot.get_weight() <= m_roulette_weight)
                    {
                        if (rng::random() <= (1.0 / m_roulette_chambers))
                        {
                            phot.multiply_weight(m_roulette_chambers);
                        }
                        else
                        {
                            loopcount = loops;
                            goto kill_photon;
                        }
                    }

                    // Determine event distances.
                    event  event_type;              //! Event type.
                    double dist;                    //! Distance to the event.
                    size_t equip_index, tri_index;  //! Indices of hit equipment and triangle if hit at all.
                    std::tie(event_type, dist, equip_index, tri_index) = determine_event(phot, cell, x);

                    // Track properties.
                    cell_energy += x * phot.get_weight();

                    // Perform the event.
                    switch (event_type)
                    {
                        // Scattering event.
                        case event::SCATTER:
                        {
                            // Move to the scattering point.
                            //if (raman_count > 1)
                            //{
                            //    std::cout<<"Ramaned more than once " << raman_count << std::endl;
                            //}
                            ++loops;
                            phot.move(x);
                            //std::cout << "scatt x" << x << std::endl;
                            x = 40E-6;

                            // Scatter.
                            phot.rotate(rng::henyey_greenstein(phot.get_anisotropy()), rng::random(0.0, 2.0 * M_PI));

                            //Check whether a Raman scatter occurs.
                            const double rand = rng::random(0.0, 1.0);
                            //std::cout << "random number" << rand << std::endl;
                            if (rand <= 0.01)
                            {
                                //Ensure only Raman scattered once.
                                if (raman_count == 1)
                                {

                                }
                                else
                                {
                                    raman_count = raman_count + 1;
                                    total_raman_count = total_raman_count + 1;
                                    //Record depth of Raman generation.
                                     depth = phot.get_pos()[2];
                                    //std::cout << i << ',' << depth << std::endl;
                                }
                            }

                            // Reduce weight by the albedo.
                            phot.multiply_weight(phot.get_albedo());

                            // Check that the photon still has statistical weight.
                            if (phot.get_weight() <= 0.0)
                            {
                                loopcount = loops;
                                goto kill_photon;
                            }

                            break;
                        }

                            // Cell boundary crossing.
                        case event::CELL_CROSS:
                        {
                            // Increment cell-tracked properties.
                            m_grid_mutex.lock();
                            cell->add_energy(cell_energy);
                            m_grid_mutex.unlock();
                            cell_energy = 0.0;

                            // Move just past the cell boundary point.
                            phot.move(dist + SMOOTHING_LENGTH);
                            x = x - dist - SMOOTHING_LENGTH;

                            // Check if photon has now exited the grid.
                            if (!m_grid.is_within(phot.get_pos()))
                            {
                                ++escapee;
                                if (raman_count > 0)
                                {
                                    ++raman_escapee;
                                }
                                loopcount = loops;
                                goto kill_photon;
                            }

                            // Get new cell pointer if still within the grid.
                            cell = &m_grid.get_cell(phot.get_pos());

                            break;
                        }

                            // Entity collision.
                        case event::ENTITY_HIT:
                        {
                            // Check for close-collision.
                            if (dist < SMOOTHING_LENGTH)
                            {
                                WARN("Unable to simulate photon.", "Distance to entity is smaller than the smoothing length.");
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

                            if (rng::random() <= reflectance)   // Reflect.
                            {
                                // Move to just before the entity boundary.
                                phot.move(dist - SMOOTHING_LENGTH);
                                x = x - dist + SMOOTHING_LENGTH;
                                //Check whether a Raman scatter occurs.
                                const double rand = rng::random(0.0, 1.0);
                                if (rand <= 0.01)
                                {
                                    //Ensure only Raman scattered once.
                                    if (raman_count == 1)
                                    {

                                    }
                                    else
                                    {
                                        raman_count = raman_count + 1;
                                        total_raman_count = total_raman_count + 1;
                                        //Record depth of Raman generation.
                                        depth = phot.get_pos()[2];
                                    }
                                }
                                // Reflect the photon.
                                phot.set_dir(optics::reflection_dir(phot.get_dir(), norm));
                            }
                            else                                // Refract.
                            {
                                // Move to just past the entity boundary.
                                phot.move(dist + SMOOTHING_LENGTH);
                                x = x - dist - SMOOTHING_LENGTH;
                                //Check whether a Raman scatter occurs.
                                const double rand = rng::random(0.0, 1.0);
                                if (rand <= 0.01)
                                {
                                    //Ensure only Raman scattered once.
                                    if (raman_count == 1)
                                    {

                                    }
                                    else
                                    {
                                        raman_count = raman_count + 1;
                                        total_raman_count = total_raman_count + 1;
                                        //Record depth of Raman generation.
                                        depth = phot.get_pos()[2];
                                    }
                                }
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
                            x = x - dist;
                            //Check whether a Raman scatter occurs.
                            const double rand = rng::random(0.0, 1.0);
                            if (rand <= 0.01)
                            {
                                //Ensure only Raman scattered once.
                                if (raman_count == 1)
                                {

                                }
                                else
                                {
                                    raman_count = raman_count + 1;
                                    total_raman_count = total_raman_count + 1;
                                    //Record depth of Raman generation.
                                    depth = phot.get_pos()[2];
                                }
                            }

                            // Get normal of the hit location.
                            const math::Vec<3> norm = m_ccd[equip_index].get_mesh().get_tri(tri_index).get_norm(phot.get_pos());
                            loopcount = loops;
                            // Check if photon hits the front of the detector and that the photon has been Raman scattered.
                           // if ((phot.get_dir() * norm) < 0.0)
                            if (((phot.get_dir() * norm) < 0.0 ) && (raman_count != 0))
                            {
                                m_ccd_mutex.lock();

                                m_ccd[equip_index].add_hit(phot.get_pos(), phot.get_weight(), 700E-9);
                                m_ccd[equip_index].add_count(phot.get_pos(), depth, loopcount);

                                m_ccd_mutex.unlock();
                            }

                            // Kill the absorbed photon.
                            ++correct_exit;
                            if (raman_count > 0)
                            {
                                ++raman_correct_exit;
                            }

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
                            loopcount = loops;
                            goto kill_photon;
                        }
                    }
                }

                // Photon death label.
                loopcount = loops;
                kill_photon:;

#ifdef ENABLE_PHOTON_PATHS
                // Add the photon path.
                m_path_mutex.lock();
                m_path.push_back(phot.get_path());
                m_path_mutex.unlock();
#endif
            }

            std::cout << "Total number of photons escaping anywhere except the top " << escapee << std::endl;
            std::cout << "Total number of photons exiting correctly " << correct_exit << std::endl;
            std::cout << "Total number of photons reaching loop limit " << killed << std::endl;
            std::cout << "Total number of Raman scatters " << total_raman_count << std::endl;
            std::cout << "Total number of Raman photons exiting correctly " << raman_correct_exit << std::endl;
            std::cout << "Total number of Raman photons reaching loop limit " << raman_killed << std::endl;
            std::cout << "Total number of Raman photons escaping anywhere except the top " << raman_escapee << std::endl;

        }

        /**
         *  Determine the next event a photon will undergo.
         *
         *  @param  t_phot  Photon whose event will be determined.
         *  @param  t_cell  Cell the photon is currently within.
         *
         *  @post   Return distance must be positive.
         *  @post   Equipment index must not be a NaN if not a scattering or cell crossing event.
         *  @post   Equipment triangle index must not be a NaN if not a scattering or cell crossing event.
         *
         *  @return A tuple containing, the type of event, distance to event, indices of equipment and triangle involved.
         */
        std::tuple<Sim::event, double, size_t, size_t> Sim::determine_event(const phys::Photon& t_phot,
                                                                            const mesh::Cell* t_cell, double x) const
        {
             // Determine scatter distance.
            //const double scat_dist = -std::log(rng::random()) / t_phot.get_interaction();
            double scat_dist = x;
            assert(scat_dist > 0.0);

            // Determine the cell distance.
            const double cell_dist = t_cell->get_dist_to_wall(t_phot.get_pos(), t_phot.get_dir());
            assert(cell_dist > SMOOTHING_LENGTH);

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
            static const int  print_width = static_cast<int>(term::TEXT_WIDTH / m_thread_progress.size());
            for (size_t       i           = 0; i < m_thread_progress.size(); ++i)
            {
                progress << std::setw(print_width - 2) << m_thread_progress[i] << "% ";
            }

            // Print the progress string.
            LOG(progress.str());
        }



    } // namespace setup
} // namespace arc
