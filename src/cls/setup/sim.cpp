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
#include "gen/config.hpp"
#include "gen/optics.hpp"

//  -- Utility --
#include "utl/file.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
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
            m_num_phot(t_json.parse_child<unsigned long int>("num_phot")),
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
                const auto   trans = json_entity.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_entity.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double rot   = math::deg_to_rad(json_entity.parse_child<double>("rot", 0.0));
                const auto   scale = json_entity.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

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
                const auto   trans = json_light.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_light.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double rot   = math::deg_to_rad(json_light.parse_child<double>("rot", 0.0));
                const auto   scale = json_light.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

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
                const auto   trans = json_ccd.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_ccd.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double rot   = math::deg_to_rad(json_ccd.parse_child<double>("rot", 0.0));
                const auto   scale = json_ccd.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

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
                const auto   trans = json_spectrometer.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_spectrometer.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double rot   = math::deg_to_rad(json_spectrometer.parse_child<double>("rot", 0.0));
                const auto   scale = json_spectrometer.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

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


        //  -- Running --
        /**
         *  Run the simulation.
         */
        void Sim::run()
        {
            // Run each photon.
            for (unsigned long int i = 0; i < m_num_phot; ++i)
            {
                TEMP("Photon Loop", 100.0 * i / m_num_phot);

                // Generate a new photon.
                phys::Photon phot = m_light[m_light_select.gen_index()].gen_photon(m_aether);

                // Determine the initial cell.
                mesh::Cell* cell = &m_grid.get_cell(phot.get_pos());

                // Track energy density to be added to each cell.
                double energy = 0.0;

                // Loop until the photon exits the grid.
                unsigned long int loops = 0;
                while (m_grid.is_within(phot.get_pos()) && (phot.get_weight() > 0.0))
                {
                    // Increment number of loops.
                    ++loops;
                    if (loops > 1e6)
                    {
                        WARN("Photon removed from loop prematurely.", "Number of loops exceeded set limit.");
                        break;
                    }

                    // Call roulette if below threshold.
                    if (phot.get_weight() < m_roulette_weight)
                    {
                        if (rng::random() > (1.0 / m_roulette_chambers))
                        {
                            // Remove the photon from simulation.
                            cell->add_energy(energy);
                            break;
                        }

                        phot.multiply_weight(m_roulette_chambers);
                    }

                    const double scat_dist = -std::log(rng::random()) / phot.get_interaction();
                    const double cell_dist = cell->get_dist_to_wall(phot.get_pos(), phot.get_dir());
                    size_t       entity_index;
                    double       entity_dist;
                    math::Vec<3> entity_norm;
                    std::tie(entity_index, entity_dist, entity_norm) = cell
                        ->get_dist_to_entity(phot.get_pos(), phot.get_dir(), m_entity);
                    size_t       ccd_index;
                    double       ccd_dist;
                    math::Vec<3> ccd_norm;
                    std::tie(ccd_index, ccd_dist, ccd_norm) = cell->get_dist_to_ccd(phot.get_pos(), phot.get_dir(), m_ccd);
                    size_t       spectrometer_index;
                    double       spectrometer_dist;
                    math::Vec<3> spectrometer_norm;
                    std::tie(spectrometer_index, spectrometer_dist, spectrometer_norm) = cell
                        ->get_dist_to_spectrometer(phot.get_pos(), phot.get_dir(), m_spectrometer);

                    assert(!math::equal(scat_dist, cell_dist, SMOOTHING_LENGTH));
                    assert(!math::equal(cell_dist, entity_dist, SMOOTHING_LENGTH));
                    assert(!math::equal(scat_dist, entity_dist, SMOOTHING_LENGTH));

                    if (entity_dist <= SMOOTHING_LENGTH)
                    {
                        WARN("Photon removed from loop prematurely.",
                             "Distance to entity is shorter than the smoothing length.");

#ifdef ENABLE_PHOTON_PATHS
                        m_path.push_back(phot.get_path());
#endif

                        // Remove the photon from simulation.
                        cell->add_energy(energy);
                        break;
                    }

//                    assert(scat_dist > SMOOTHING_LENGTH);
                    assert(cell_dist > SMOOTHING_LENGTH);
                    assert(entity_dist > SMOOTHING_LENGTH);

                    // Photon hits a spectrometer detector.
                    if ((spectrometer_dist < ccd_dist) && (spectrometer_dist < scat_dist) && (spectrometer_dist < entity_dist) && (spectrometer_dist < cell_dist))
                    {
                        energy += spectrometer_dist * phot.get_weight();

                        // Move the photon to the detector surface.
                        phot.move(spectrometer_dist);

                        // Check if photon hits the front of the detector.
                        if ((phot.get_dir() * spectrometer_norm) < 0.0)
                        {
                            m_spectrometer[spectrometer_index].add_hit(phot.get_wavelength(), phot.get_weight());
                        }

                        // Remove the photon from simulation.
                        cell->add_energy(energy);
                        break;
                    }

                    // Photon hits a ccd detector.
                    if ((ccd_dist < scat_dist) && (ccd_dist < entity_dist) && (ccd_dist < cell_dist))
                    {
                        energy += ccd_dist * phot.get_weight();

                        // Move the photon to the detector surface.
                        phot.move(ccd_dist);

                        // Check if photon hits the front of the detector.
                        if ((phot.get_dir() * m_ccd[ccd_index].get_norm()) < 0.0)
                        {
                            m_ccd[ccd_index].add_hit(phot.get_pos(), phot.get_weight(), phot.get_wavelength());
                        }

                        // Remove the photon from simulation.
                        cell->add_energy(energy);
                        break;
                    }

                    if ((scat_dist < entity_dist) && (scat_dist < cell_dist))   // Scatter.
                    {
                        energy += scat_dist * phot.get_weight();

                        // Move to the scattering point.
                        phot.move(scat_dist);

                        // Scatter.
                        phot.rotate(rng::henyey_greenstein(phot.get_anisotropy()), rng::random(0.0, 2.0 * M_PI));

                        // Reduce weight by albedo.
                        phot.multiply_weight(phot.get_albedo());
                    }
                    else if (entity_dist < cell_dist)   // Change entity.
                    {
                        // If entity normal is facing away, multiply it by -1.
                        if ((phot.get_dir() * entity_norm) > 0.0)
                        {
                            entity_norm = entity_norm * -1.0;
                        }

                        energy += entity_dist * phot.get_weight();

                        // Determine the material indices.
                        int  index_i, index_t;
                        bool exiting = phot.get_entity_index() == static_cast<int>(entity_index);
                        if (exiting)    // Exiting the current entity.
                        {
                            index_i = static_cast<int>(entity_index);
                            index_t = phot.get_prev_entity_index();
                        }
                        else            // Entering a new entity.
                        {
                            index_i = phot.get_entity_index();
                            index_t = static_cast<int>(entity_index);
                        }
                        assert(index_i != index_t);

                        // Get references to the materials.
                        const phys::Material& mat_i = (index_i == -1) ? m_aether : m_entity[static_cast<size_t>(index_i)]
                            .get_mat();
                        const phys::Material& mat_t = (index_t == -1) ? m_aether : m_entity[static_cast<size_t>(index_t)]
                            .get_mat();

                        // Get optical properties of the materials.
                        const double n_i = mat_i.get_ref_index(phot.get_wavelength());
                        const double n_t = mat_t.get_ref_index(phot.get_wavelength());

                        // Calculate incident angle.
                        const double a_i = acos(-1.0 * (phot.get_dir() * entity_norm));
                        assert((a_i >= 0.0) && (a_i < (M_PI / 2.0)));

                        // Check for total internal reflection.
                        if (std::sin(a_i) > (n_t / n_i))
                        {
                            // Move to just before the boundary.
                            phot.move(entity_dist - SMOOTHING_LENGTH);

                            // Reflect the photon.
                            phot.set_dir(optics::reflection_dir(phot.get_dir(), entity_norm));
                        }
                        else
                        {
                            if (rng::random() <= optics::reflection_prob(a_i, n_i, n_t))    // Reflect.
                            {
                                // Move to just before the boundary.
                                phot.move(entity_dist - SMOOTHING_LENGTH);

                                // Reflect the photon.
                                phot.set_dir(optics::reflection_dir(phot.get_dir(), entity_norm));
                            }
                            else                                                            // Refract.
                            {
                                // Move to just past the boundary.
                                phot.move(entity_dist + SMOOTHING_LENGTH);

                                // Refract the photon.
                                phot.set_dir(optics::refraction_dir(phot.get_dir(), entity_norm, n_i / n_t));

                                // Photon moves to new entity.
                                if (exiting)
                                {
                                    phot.pop_entity_index();
                                }
                                else
                                {
                                    phot.push_entity_index(index_t);
                                }
                                phot.set_opt(index_t == -1 ? m_aether : m_entity[static_cast<size_t>(index_t)].get_mat());
                            }
                        }
                    }
                    else    // Exit cell.
                    {
                        energy += cell_dist * phot.get_weight();

                        // Add current energy to current cell and reset count.
                        cell->add_energy(energy);
                        energy = 0.0;

                        // Move into the next cell space.
                        phot.move(cell_dist + SMOOTHING_LENGTH);

                        // Change cell if still within the grid.
                        if (m_grid.is_within(phot.get_pos()))
                        {
                            cell = &m_grid.get_cell(phot.get_pos());
                        }
                    }
                }

#ifdef ENABLE_PHOTON_PATHS
                // Add the photon path.
                m_path.push_back(phot.get_path());
#endif
            }

            LOG("Photon loop complete.");
        }



    } // namespace setup
} // namespace arc
