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
#include "gen/math.hpp"

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
            m_aether(init_aether(t_json["aether"])),
            m_entity(init_entity(t_json["entities"])),
            m_light(init_light(t_json["lights"])),
            m_light_select(init_light_select()),
            m_grid(t_json["grid"].parse_child<math::Vec<3>>("min"), t_json["grid"].parse_child<math::Vec<3>>("max"),
                   t_json["grid"].parse_child<std::array<size_t, 3>>("cells"), m_entity, m_light)
        {
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
            LOG("Constructing aether.");

            // Get file paths.
            const std::string mat_path = t_json.parse_child<std::string>("mat");

            return (phys::Material(file::read(mat_path)));
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
                LOG("Constructing entity : " << entity_name[i]);

                // Create a json object of the entity.
                const data::Json json_entity = t_json[entity_name[i]];

                // Get the transformation values.
                const auto   trans = json_entity.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_entity.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double spin  = math::deg_to_rad(json_entity.parse_child<double>("spin", 0.0));
                const auto   scale = json_entity.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

                // Get file paths.
                const std::string mesh_path = json_entity.parse_child<std::string>("mesh");
                const std::string mat_path  = json_entity.parse_child<std::string>("mat");

                // Construct the entity object an add it to the vector of entities.
                r_entity.emplace_back(equip::Entity(geom::Mesh(file::read(mesh_path), trans, dir, spin, scale),
                                                    phys::Material(file::read(mat_path))));
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
                LOG("Constructing light : " << light_name[i]);

                // Create a json object of the light.
                const data::Json json_light = t_json[light_name[i]];

                // Get the transformation values.
                const auto   trans = json_light.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const auto   dir   = json_light.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 1.0}}));
                const double spin  = math::deg_to_rad(json_light.parse_child<double>("spin", 0.0));
                const auto   scale = json_light.parse_child<math::Vec<3>>("scale", math::Vec<3>({{1.0, 1.0, 1.0}}));

                // Get light properties.
                const auto power = json_light.parse_child<double>("power");

                // Get file paths.
                const std::string mesh_path = json_light.parse_child<std::string>("mesh");
                const std::string spec_path = json_light.parse_child<std::string>("spec");

                // Construct the light object an add it to the vector of lights.
                r_light.emplace_back(equip::Light(geom::Mesh(file::read(mesh_path), trans, dir, spin, scale),
                                                  phys::Spectrum(file::read(spec_path)), power));
            }

            return (r_light);
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
        //  -- Rendering --
        /**
         *  Render a scene of the current simulation.
         */
        void Sim::render() const
        {
            // Create a graphical scene.
            graphical::Scene scene;

            // Add objects to the scene.
            scene.add_light_vector(m_light);
            scene.add_entity_vector(m_entity);
            scene.add_photon_vector(m_path);
            scene.add_cell(m_grid.get_min_bound(), m_grid.get_max_bound(), 1.0);

            double      max_energy_density = 0.0;
            for (size_t i                  = 0; i < m_grid.get_num_cells(X); ++i)
            {
                for (size_t j = 0; j < m_grid.get_num_cells(Y); ++j)
                {
                    for (size_t k = 0; k < m_grid.get_num_cells(Z); ++k)
                    {
                        if (m_grid.get_cell(i, j, k).get_energy_density() > max_energy_density)
                        {
                            max_energy_density = m_grid.get_cell(i, j, k).get_energy_density();
                        }
                    }
                }
            }
            VAL(max_energy_density);

            for (size_t i                  = 0; i < m_grid.get_num_cells(X); ++i)
            {
                for (size_t j = 0; j < m_grid.get_num_cells(Y); ++j)
                {
                    for (size_t k = 0; k < m_grid.get_num_cells(Z); ++k)
                    {
                        scene.add_cell(m_grid.get_cell(i, j, k).get_min_bound(), m_grid.get_cell(i, j, k).get_max_bound(),
                                       m_grid.get_cell(i, j, k).get_energy_density() / max_energy_density);
                    }
                }
            }

            // Render the scene.
            while (!scene.should_close())
            {
                scene.handle_input();
                scene.render();
            }
        }


        //  -- Running --
        /**
         *  Run the simulation.
         */
        void Sim::run()
        {
            for (unsigned long int i = 0; i < m_num_phot; ++i)
            {
                TEMP("Photon Loop", 100.0 * i / m_num_phot);

                // Generate a new photon.
                phys::particle::Photon phot = m_light[m_light_select.gen_index()].gen_photon(m_aether);

                // Determine starting cell containing the photon.
                std::unique_ptr<mesh::Cell> cell = nullptr;
                if (m_grid.is_within(phot.get_pos()))
                {
                    cell = std::make_unique<mesh::Cell>(m_grid.get_cell(phot.get_pos()));
                }

                double distance_through_cell = 0.0;

                // Loop until the photon exits the grid.
                while (m_grid.is_within(phot.get_pos()))
                {
                    const double scat_dist = -std::log(rng::random()) / phot.get_interaction();
                    const double cell_dist = cell->dist_to_boundary(phot.get_pos(), phot.get_dir());

                    if (scat_dist < cell_dist)
                    {
                        // Undergo a scattering.
                        phot.move(scat_dist);
                        distance_through_cell += scat_dist;

                        phot.scatter();
//                        phot.multiply_weight(phot.get_albedo());
                    }
                    else
                    {
                        // Move to the next grid cell.
                        distance_through_cell += cell_dist;
                        m_grid.get_cell(phot.get_pos()).add_energy_density(distance_through_cell);
                        phot.move(cell_dist + 1e-10);

                        if (m_grid.is_within(phot.get_pos()))
                        {
                            cell = std::make_unique<mesh::Cell>(m_grid.get_cell(phot.get_pos()));
                        }

                        distance_through_cell = 0.0;
                    }
                }

                // Add the photon path.
                m_path.push_back(phot.get_path());
            }
        }



    } // namespace setup
} // namespace arc
