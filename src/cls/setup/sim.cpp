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
            m_roulette_weight(t_json["roulette"].parse_child<double>("weight")),
            m_roulette_chambers(t_json["roulette"].parse_child<double>("chambers")),
            m_aether(init_aether(t_json["aether"])),
            m_entity(init_entity(t_json["entities"])),
            m_light(init_light(t_json["lights"])),
            m_ccd(init_ccd(t_json["ccds"])),
            m_spectrometer(init_spectrometer(t_json["spectrometers"])),
            m_light_select(init_light_select()),
            m_grid(t_json["grid"].parse_child<math::Vec<3>>("min"), t_json["grid"].parse_child<math::Vec<3>>("max"),
                   t_json["grid"].parse_child<std::array<size_t, 3>>("cells"), m_entity, m_light, m_ccd, m_spectrometer)
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

                // Construct the ccd object an add it to the vector of ccds.
                r_ccd.emplace_back(detector::Ccd(ccd_name[i], pix[X], pix[Y], col, trans, dir, rot, scale));
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
                const auto min  = json_spectrometer.parse_child<double>("min");
                const auto max  = json_spectrometer.parse_child<double>("max");
                const auto bins = json_spectrometer.parse_child<size_t>("bins");

                // Get file paths.
                const std::string mesh_path = json_spectrometer.parse_child<std::string>("mesh");

                // Construct the spectrometer object an add it to the vector of spectrometers.
                r_spectrometer.emplace_back(
                    detector::Spectrometer(spectrometer_name[i], geom::Mesh(utl::read(mesh_path), trans, dir, rot, scale), min,
                                           max, bins));
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
         *  @param  t_num_phot  The number of photons to run.
         */
        void Sim::run_photons(const unsigned long int t_num_phot)
        {
            // Run each photon through the simulation.
            for (unsigned long int i = 0; i < t_num_phot; ++i)
            {
                // Emit a new photon.
                phys::Photon phot = m_light[m_light_select.gen_index()].gen_photon(m_aether);

                // Check if photon is within the grid and get current cell.
                if (!m_grid.is_within(phot.get_pos()))
                {
                    WARN("Unable to simulate photon.", "Photon does not begin with the grid.");
                    goto kill_photon;
                }
                mesh::Cell* cell = &m_grid.get_cell(phot.get_pos());
                cell->add_energy(0.1);
                assert(cell != nullptr);

                // Initialise tracked properties.
                double cell_energy = 0.0;   //! Energy to be added to cell total when exiting current cell.

                // Loop until exit condition is met.
                while (true)
                {
                    // Check if photon has exited the grid.
                    if (!m_grid.is_within(phot.get_pos()))
                    {
                        goto kill_photon;
                    }

                    // Determine event distances.
                    event  event_type;              //! Event type.
                    double dist;                    //! Distance to the event.
                    size_t equip_index, tri_index;  //! Indices of hit equipment and triangle if hit at all.
                    std::tie(event_type, dist, equip_index, tri_index) = determine_event(phot, cell);

                    // Track properties.
                    cell_energy += dist * phot.get_weight();

                    // Perform the event.
                    switch (event_type)
                    {
                        case event::SCATTER:
                            // Move to the scattering point.
                            phot.move(dist);

                            // Scatter.
                            phot.rotate(rng::henyey_greenstein(phot.get_anisotropy()), rng::random(0.0, 2.0 * M_PI));

                            // Reduce weight by the albedo.
                            phot.multiply_weight(phot.get_albedo());

                            break;
                        case event::CELL_CROSS:

                            break;
                        case event::ENTITY_HIT:

                            break;
                        case event::CCD_HIT:

                            break;
                        case event::SPECTROMETER_HIT:

                            break;
                    }

                    phot.move(dist);
                    break;
                }

                // Photon death label.
                kill_photon:;

#ifdef ENABLE_PHOTON_PATHS
                // Add the photon path.
                m_path.push_back(phot.get_path());
#endif
            }
        }

        /**
         *  Determine the next event a photon will undergo.
         *
         *  @param  t_phot  Photon whose event will be determined.
         *  @param  t_cell  Cell the photon is currently within.
         *
         *  @post   Return distance must be greater than the smoothing length.
         *  @post   Equipment index must not be a NaN if not a scattering or cell crossing event.
         *  @post   Equipment triangle index must not be a NaN if not a scattering or cell crossing event.
         *
         *  @return A tuple containing, the type of event, distance to event, indices of equipment and triangle involved.
         */
        std::tuple<Sim::event, double, size_t, size_t> Sim::determine_event(const phys::Photon& t_phot,
                                                                            const mesh::Cell* t_cell) const
        {
            // Determine scatter distance.
            const double scat_dist = -std::log(rng::random()) / t_phot.get_interaction();
            assert(scat_dist > SMOOTHING_LENGTH);

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
                    assert(scat_dist > SMOOTHING_LENGTH);
                    return (std::tuple<event, double, size_t, size_t>(event::SCATTER, scat_dist,
                                                                      std::numeric_limits<size_t>::signaling_NaN(),
                                                                      std::numeric_limits<size_t>::signaling_NaN()));
                case 1:
                    assert(cell_dist > SMOOTHING_LENGTH);
                    return (std::tuple<event, double, size_t, size_t>(event::CELL_CROSS, cell_dist,
                                                                      std::numeric_limits<size_t>::signaling_NaN(),
                                                                      std::numeric_limits<size_t>::signaling_NaN()));
                case 2:
                    assert(entity_dist > SMOOTHING_LENGTH);
                    assert(!std::isnan(entity_index));
                    assert(!std::isnan(entity_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::ENTITY_HIT, entity_dist, entity_index,
                                                                      entity_tri_index));
                case 3:
                    assert(ccd_dist > SMOOTHING_LENGTH);
                    assert(!std::isnan(ccd_index));
                    assert(!std::isnan(ccd_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::CCD_HIT, ccd_dist, ccd_index, ccd_tri_index));
                case 4:
                    assert(spectrometer_dist > SMOOTHING_LENGTH);
                    assert(!std::isnan(spectrometer_index));
                    assert(!std::isnan(spectrometer_tri_index));
                    return (std::tuple<event, double, size_t, size_t>(event::SPECTROMETER_HIT, spectrometer_dist,
                                                                      spectrometer_index, spectrometer_tri_index));
                default: ERROR("Unable to simulate photon.", "Code should be unreachable.");
            }
        }



    } // namespace setup
} // namespace arc
