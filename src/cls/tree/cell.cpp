/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/03/2018.
 */



//  == HEADER ==
#include "cls/tree/cell.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace tree
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a root cell to record a given list of entity, light, ccd and spectrometer objects.
         *  Tree will reproduce until at least the minimum depth has been reached.
         *  Tree will stop reproducing until either the maxmium depth is reached, or the target maximum number of triangles has
         *  been reached.
         *
         *  @param  t_min_depth     Minimum depth for the cell to split to.
         *  @param  t_max_depth     Maximum depth for the cell to split to.
         *  @param  t_max_tri       Target maximum number of triangles to contain within leaf cells.
         *  @param  t_min_bound     Minimum spatial bound of the cell.
         *  @param  t_max_bound     Maximum spatial bound of the cell.
         *  @param  t_entity        Vector of entity objects which may lie within the cell.
         *  @param  t_light         Vector of light objects which may lie within the cell.
         *  @param  t_ccd           Vector of ccd objects which may lie within the cell.
         *  @param  m_spectrometer  Vector of spectrometer objects which may lie within the cell.
         *
         *  @post   t_min_depth must be less than, or equal to, t_max_depth.
         *  @post   t_max_bound[X] must be greater than t_min_bound[X].
         *  @post   t_max_bound[Y] must be greater than t_min_bound[Y].
         *  @post   t_max_bound[Z] must be greater than t_min_bound[Z].
         *  @post   m_half_width[X] must be positive.
         *  @post   m_half_width[Y] must be positive.
         *  @post   m_half_width[Z] must be positive.
         */
        Cell::Cell(const unsigned int t_min_depth, const unsigned int t_max_depth, const unsigned int t_max_tri,
                   const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                   const std::vector<detector::Spectrometer>& t_spectrometer) :
            m_center((t_max_bound + t_min_bound) / 2.0),
            m_half_width((t_max_bound - t_min_bound) / 2.0),
            m_entity(t_entity),
            m_light(t_light),
            m_ccd(t_ccd),
            m_spectrometer(t_spectrometer),
            m_entity_tri_list(init_entity_tri_list()),
            m_light_tri_list(init_light_tri_list()),
            m_ccd_tri_list(init_ccd_tri_list()),
            m_spectrometer_tri_list(init_spectrometer_tri_list()),
            m_depth(0),
            m_leaf(init_leaf(t_min_depth, t_max_depth, t_max_tri)),
            m_child(init_child(t_min_depth, t_max_depth, t_max_tri))
        {
            assert(t_min_depth <= t_max_depth);

            assert(t_max_bound[X] > t_min_bound[X]);
            assert(t_max_bound[Y] > t_min_bound[Y]);
            assert(t_max_bound[Z] > t_min_bound[Z]);

            assert(m_half_width[X] > 0.0);
            assert(m_half_width[Y] > 0.0);
            assert(m_half_width[Z] > 0.0);
        }

        /**
         *  Construct a daughter cell to record a sub-list of entity, light, ccd and spectrometer objects.
         *  Only tests overlaps of triangles listed within the given triangle directory lists.
         *  Depth, cell center and cell half-width are set using given values.
         *
         *  @param  t_depth                 Depth of the cell.
         *  @param  t_min_depth             Minimum depth for the cell to split to.
         *  @param  t_max_depth             Maximum depth for the cell to split to.
         *  @param  t_max_tri               Target maximum number of triangles to contain within leaf cells.
         *  @param  t_center                Center of the cell.
         *  @param  t_half_width            Half-width of the cell.
         *  @param  t_entity                Vector of entity objects which may lie within the cell.
         *  @param  t_light                 Vector of light objects which may lie within the cell.
         *  @param  t_ccd                   Vector of ccd objects which may lie within the cell.
         *  @param  t_spectrometer          Vector of spectrometer objects which may lie within the cell.
         *  @param  t_entity_tri_list       List of entity triangles which may lie within the cell.
         *  @param  t_light_tri_list        List of light triangles which may lie within the cell.
         *  @param  t_ccd_tri_list          List of ccd triangles which may lie within the cell.
         *  @param  t_spectrometer_tri_list List of spectrometer triangles which may lie within the cell.
         */
        Cell::Cell(unsigned int t_depth, unsigned int t_min_depth, unsigned int t_max_depth, unsigned int t_max_tri,
                   const math::Vec<3>& t_center, const math::Vec<3>& t_half_width, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                   const std::vector<detector::Spectrometer>& t_spectrometer,
                   const std::vector<std::array<size_t, 2>>& t_entity_tri_list,
                   const std::vector<std::array<size_t, 2>>& t_light_tri_list,
                   const std::vector<std::array<size_t, 2>>& t_ccd_tri_list,
                   const std::vector<std::array<size_t, 2>>& t_spectrometer_tri_list) :
            m_center(t_center),
            m_half_width(t_half_width),
            m_entity(t_entity),
            m_light(t_light),
            m_ccd(t_ccd),
            m_spectrometer(t_spectrometer),
            m_entity_tri_list(init_entity_tri_list(t_entity_tri_list)),
            m_light_tri_list(init_light_tri_list(t_light_tri_list)),
            m_ccd_tri_list(init_ccd_tri_list(t_ccd_tri_list)),
            m_spectrometer_tri_list(init_spectrometer_tri_list(t_spectrometer_tri_list)),
            m_depth(t_depth),
            m_leaf(init_leaf(t_min_depth, t_max_depth, t_max_tri)),
            m_child(init_child(t_min_depth, t_max_depth, t_max_tri))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the vector list of entity triangles within the cell.
         *
         *  @return The initialised list vector of entity triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_entity_tri_list() const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_entity_tri_list;

            // Iterate through each of the entity sources.
            for (size_t i = 0; i < m_entity.size(); ++i)
            {
                // Iterate through each of the entity's triangles.
                for (size_t j = 0; j < m_entity[i].get_mesh().get_num_tri(); ++j)
                {
                    // If the cell overlaps any part of the triangle, add the indices to the list.
                    if (tri_overlap(m_entity[i].get_mesh().get_tri(j)))
                    {
                        r_entity_tri_list.push_back({{i, j}});
                    }
                }
            }

            return (r_entity_tri_list);
        }

        /**
         *  Initialise the vector list of entity triangles within the cell using a sub vector list of triangles.
         *
         *  @param  t_entity_tri_list   List of entity triangles which may lie within the cell.
         *
         *  @return The initialised list vector of entity triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_entity_tri_list(
            const std::vector<std::array<size_t, 2>>& t_entity_tri_list) const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_entity_tri_list;

            // Iterate through the vector list of triangles.
            for (size_t i = 0; i < t_entity_tri_list.size(); ++i)
            {
                if (tri_overlap(m_entity[t_entity_tri_list[i][OBJ]].get_mesh().get_tri(t_entity_tri_list[i][TRI])))
                {
                    r_entity_tri_list.push_back(t_entity_tri_list[i]);
                }
            }

            return (r_entity_tri_list);
        }

        /**
         *  Initialise the vector list of light triangles within the cell.
         *
         *  @return The initialised list vector of light triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_light_tri_list() const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_light_tri_list;

            // Iterate through each of the light sources.
            for (size_t i = 0; i < m_light.size(); ++i)
            {
                // Iterate through each of the light's triangles.
                for (size_t j = 0; j < m_light[i].get_mesh().get_num_tri(); ++j)
                {
                    // If the cell overlaps any part of the triangle, add the indices to the list.
                    if (tri_overlap(m_light[i].get_mesh().get_tri(j)))
                    {
                        r_light_tri_list.push_back({{i, j}});
                    }
                }
            }

            return (r_light_tri_list);
        }

        /**
         *  Initialise the vector list of light triangles within the cell using a sub vector list of triangles.
         *
         *  @param  t_light_tri_list    List of light triangles which may lie within the cell.
         *
         *  @return The initialised list vector of light triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_light_tri_list(
            const std::vector<std::array<size_t, 2>>& t_light_tri_list) const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_light_tri_list;

            // Iterate through the vector list of triangles.
            for (size_t i = 0; i < t_light_tri_list.size(); ++i)
            {
                if (tri_overlap(m_light[t_light_tri_list[i][OBJ]].get_mesh().get_tri(t_light_tri_list[i][TRI])))
                {
                    r_light_tri_list.push_back(t_light_tri_list[i]);
                }
            }

            return (r_light_tri_list);
        }

        /**
         *  Initialise the vector list of ccd triangles within the cell.
         *
         *  @return The initialised list vector of ccd triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_ccd_tri_list() const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_ccd_tri_list;

            // Iterate through each of the ccd sources.
            for (size_t i = 0; i < m_ccd.size(); ++i)
            {
                // Iterate through each of the ccd's triangles.
                for (size_t j = 0; j < m_ccd[i].get_mesh().get_num_tri(); ++j)
                {
                    // If the cell overlaps any part of the triangle, add the indices to the list.
                    if (tri_overlap(m_ccd[i].get_mesh().get_tri(j)))
                    {
                        r_ccd_tri_list.push_back({{i, j}});
                    }
                }
            }

            return (r_ccd_tri_list);
        }

        /**
         *  Initialise the vector list of ccd triangles within the cell using a sub vector list of triangles.
         *
         *  @param  t_ccd_tri_list  List of ccd triangles which may lie within the cell.
         *
         *  @return The initialised list vector of ccd triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_ccd_tri_list(
            const std::vector<std::array<size_t, 2>>& t_ccd_tri_list) const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_ccd_tri_list;

            // Iterate through the vector list of triangles.
            for (size_t i = 0; i < t_ccd_tri_list.size(); ++i)
            {
                if (tri_overlap(m_ccd[t_ccd_tri_list[i][OBJ]].get_mesh().get_tri(t_ccd_tri_list[i][TRI])))
                {
                    r_ccd_tri_list.push_back(t_ccd_tri_list[i]);
                }
            }

            return (r_ccd_tri_list);
        }

        /**
         *  Initialise the vector list of spectrometer triangles within the cell.
         *
         *  @return The initialised list vector of spectrometer triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_spectrometer_tri_list() const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_spectrometer_tri_list;

            // Iterate through each of the spectrometer sources.
            for (size_t i = 0; i < m_spectrometer.size(); ++i)
            {
                // Iterate through each of the spectrometer's triangles.
                for (size_t j = 0; j < m_spectrometer[i].get_mesh().get_num_tri(); ++j)
                {
                    // If the cell overlaps any part of the triangle, add the indices to the list.
                    if (tri_overlap(m_spectrometer[i].get_mesh().get_tri(j)))
                    {
                        r_spectrometer_tri_list.push_back({{i, j}});
                    }
                }
            }

            return (r_spectrometer_tri_list);
        }

        /**
         *  Initialise the vector list of spectrometer triangles within the cell using a sub vector list of triangles.
         *
         *  @param  t_spectrometer_tri_list List of spectrometer triangles which may lie within the cell.
         *
         *  @return The initialised list vector of spectrometer triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_spectrometer_tri_list(
            const std::vector<std::array<size_t, 2>>& t_spectrometer_tri_list) const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_spectrometer_tri_list;

            // Iterate through the vector list of triangles.
            for (size_t i = 0; i < t_spectrometer_tri_list.size(); ++i)
            {
                if (tri_overlap(
                    m_spectrometer[t_spectrometer_tri_list[i][OBJ]].get_mesh().get_tri(t_spectrometer_tri_list[i][TRI])))
                {
                    r_spectrometer_tri_list.push_back(t_spectrometer_tri_list[i]);
                }
            }

            return (r_spectrometer_tri_list);
        }

        /**
         *  Determine if this cell is a terminal leaf cell.
         *
         *  @param  t_min_depth     Minimum depth for the cell to split to.
         *  @param  t_max_depth     Maximum depth for the cell to split to.
         *  @param  t_max_tri       Target maximum number of triangles to contain within leaf cells.
         *
         *  @return True if this cell is a terminal leaf cell.
         */
        bool Cell::init_leaf(const unsigned int t_min_depth, const unsigned int t_max_depth, const unsigned int t_max_tri) const
        {
            // If the cell has reached the maximum allowed depth, it is required to be terminal.
            if (m_depth >= t_max_depth)
            {
                return (true);
            }

            // If the cell has not yet reached the minimum splitting depth, it must procreate.
            if (m_depth < t_min_depth)
            {
                return (false);
            }

            // Otherwise, only split if the number of contained triangles exceeds that of the maximum limit.
            size_t total_triangles = m_entity_tri_list.size() + m_light_tri_list.size() + m_ccd_tri_list
                .size() + m_spectrometer_tri_list.size();
            return (total_triangles <= t_max_tri);
        }

        /**
         *  Initialise the array of daughter cells.
         *
         *  @param  t_min_depth     Minimum depth for the cell to split to.
         *  @param  t_max_depth     Maximum depth for the cell to split to.
         *  @param  t_max_tri       Target maximum number of triangles to contain within leaf cells.
         *
         *  @return The initialised array of daughter cells.
         */
        std::array<std::unique_ptr<Cell>, 8> Cell::init_child(const unsigned int t_min_depth, const unsigned int t_max_depth,
                                                              const unsigned int t_max_tri) const
        {
            // If cell is a leaf, do not create children.
            if (m_leaf)
            {
                return (std::array<std::unique_ptr<Cell>, 8>(
                    {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}));
            }

            const unsigned int daughter_depth = m_depth + 1;
            const math::Vec<3> half_width     = m_half_width / 2.0;
            const math::Vec<3> offset         = m_half_width / 2.0;

            return (std::array<std::unique_ptr<Cell>, 8>(
                {{std::make_unique<Cell>(daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                                         math::Vec<3>(m_center[X] + offset[X], m_center[Y] + offset[Y],
                                                      m_center[Z] + offset[Z]), half_width, m_entity, m_light, m_ccd,
                                         m_spectrometer, m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                                         m_spectrometer_tri_list), std::make_unique<Cell>(daughter_depth, t_min_depth,
                                                                                          t_max_depth, t_max_tri,
                                                                                          math::Vec<3>(m_center[X] - offset[X],
                                                                                                       m_center[Y] + offset[Y],
                                                                                                       m_center[Z] + offset[Z]),
                                                                                          half_width, m_entity, m_light, m_ccd,
                                                                                          m_spectrometer, m_entity_tri_list,
                                                                                          m_light_tri_list, m_ccd_tri_list,
                                                                                          m_spectrometer_tri_list), std::make_unique<
                    Cell>(daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                          math::Vec<3>(m_center[X] + offset[X], m_center[Y] - offset[Y], m_center[Z] + offset[Z]), half_width,
                          m_entity, m_light, m_ccd, m_spectrometer, m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                          m_spectrometer_tri_list), std::make_unique<Cell>(daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                                                                           math::Vec<3>(m_center[X] - offset[X],
                                                                                        m_center[Y] - offset[Y],
                                                                                        m_center[Z] + offset[Z]), half_width,
                                                                           m_entity, m_light, m_ccd, m_spectrometer,
                                                                           m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                                                                           m_spectrometer_tri_list), std::make_unique<Cell>(
                    daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                    math::Vec<3>(m_center[X] + offset[X], m_center[Y] + offset[Y], m_center[Z] - offset[Z]), half_width,
                    m_entity, m_light, m_ccd, m_spectrometer, m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                    m_spectrometer_tri_list), std::make_unique<Cell>(daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                                                                     math::Vec<3>(m_center[X] - offset[X],
                                                                                  m_center[Y] + offset[Y],
                                                                                  m_center[Z] - offset[Z]), half_width,
                                                                     m_entity, m_light, m_ccd, m_spectrometer,
                                                                     m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                                                                     m_spectrometer_tri_list), std::make_unique<Cell>(
                    daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                    math::Vec<3>(m_center[X] + offset[X], m_center[Y] - offset[Y], m_center[Z] - offset[Z]), half_width,
                    m_entity, m_light, m_ccd, m_spectrometer, m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                    m_spectrometer_tri_list), std::make_unique<Cell>(daughter_depth, t_min_depth, t_max_depth, t_max_tri,
                                                                     math::Vec<3>(m_center[X] - offset[X],
                                                                                  m_center[Y] - offset[Y],
                                                                                  m_center[Z] - offset[Z]), half_width,
                                                                     m_entity, m_light, m_ccd, m_spectrometer,
                                                                     m_entity_tri_list, m_light_tri_list, m_ccd_tri_list,
                                                                     m_spectrometer_tri_list)}}));
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Retrieve a pointer to the leaf cell for a given position within the cell.
         *
         *  @param  t_pos   Position of the point.
         *
         *  @pre    t_pos must be within the current cell.
         *
         *  @return A pointer to the leaf cell containing the given position.
         */
        Cell* Cell::get_leaf(const math::Vec<3>& t_pos)
        {
            VAL(t_pos);
            VAL(m_depth);
            VAL(m_center);
            VAL(m_half_width);
            LOG(" ");
            assert(is_within(t_pos));

            // If this cell is a leaf, return a pointer to this cell.
            if (m_leaf)
            {
                return (this);
            }

            // Determine the child index.
            size_t child_index = 0;
            if (t_pos[X] < m_center[X])
            {
                child_index += 1;
            }
            if (t_pos[Y] < m_center[Y])
            {
                child_index += 2;
            }
            if (t_pos[Z] < m_center[Z])
            {
                child_index += 4;
            }

            return (m_child[child_index]->get_leaf(t_pos));
        }

        /**
         *  Determine if a given point falls within the bounds of the cell.
         *
         *  @param  t_pos   Position of the point.
         *
         *  @return True if the point does fall within the bounds of the cell.
         */
        bool Cell::is_within(const math::Vec<3>& t_pos) const
        {
            // Check if any dimensions fall outside of the cells.
            for (size_t i = 0; i < 3; ++i)
            {
                if ((t_pos[i] < (m_center[X] - m_half_width[X])) || (t_pos[i] > (m_center[X] + m_half_width[X])))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine the distance to the wall of the cell from the given position travelling along the given direction.
         *
         *  @param  t_pos   Position of the point within the cell.
         *  @param  t_dir   Direction of travel.
         *
         *  @pre    t_pos must be within the cell.
         *  @pre    t_dir must be normalised.
         *
         *  @post   r_dist must be positive.
         *
         *  @return The distance to the wall of the cell from the given position travelling along the given direction.
         */
        double Cell::get_dist_to_wall(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
        {
            assert(is_within(t_pos));
            assert(t_dir.is_normalised());

            // Calculate distance to each boundary.
            std::array<double, 6> dist{};
            for (size_t           i = 0; i < 3; ++i)
            {
                dist[i * 2]       = (t_dir[i] == 0.0) ? std::numeric_limits<double>::max()
                                                      : ((m_center[i] - m_half_width[i]) - t_pos[i]) / t_dir[i];
                dist[(i * 2) + 1] = (t_dir[i] == 0.0) ? std::numeric_limits<double>::max()
                                                      : ((m_center[i] + m_half_width[i]) - t_pos[i]) / t_dir[i];
            }

            // Determine the smallest positive distance.
            double            r_dist = std::numeric_limits<double>::max();
            for (unsigned int i      = 0; i < 6; ++i)
            {
                if ((dist[i] < r_dist) && (dist[i] > 0.0))
                {
                    r_dist = dist[i];
                }
            }

            assert(r_dist > 0.0);

            return (r_dist);
        }

        /**
         *  Determine the distance to the closest entity triangle within the cell.
         *  If no entity is hit, the first value of the tuple will be set to false.
         *  The second value of the returned tuple holds the distance to the entity triangle if one was hit.
         *  The third and fourth values of the returned tuple hold the hit entity and triangle indices respectively.
         *  If no entity triangle is hit the first value is false and the others are set to NaN.
         *
         *  @param  t_pos       Start position of the ray.
         *  @param  t_dir       Direction of the ray.
         *
         *  @return A tuple containing, hit status, distance to intersection, collision entity and triangle indices.
         */
        std::tuple<bool, double, size_t, size_t> Cell::entity_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no entity triangles, there is no hit.
            if (m_entity_tri_list.empty())
            {
                return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN()));
            }

            // Run through all entity triangles and determine if any hits occur.
            bool        hit            = false;
            double      r_dist         = std::numeric_limits<double>::max();
            size_t      r_entity_index = std::numeric_limits<size_t>::signaling_NaN();
            size_t      r_tri_index    = std::numeric_limits<size_t>::signaling_NaN();
            for (size_t i              = 0; i < m_entity_tri_list.size(); ++i)
            {
                // Get a reference to the triangle.
                const geom::Triangle& tri = m_entity[m_entity_tri_list[i][0]].get_mesh().get_tri(m_entity_tri_list[i][1]);

                // Determine if there is a hit.
                bool   tri_hit;
                double tri_dist;
                std::tie(tri_hit, tri_dist) = tri.intersection_dist(t_pos, t_dir);

                // If a hit does occur, and it is closer than any hit so far, store the information.
                if (tri_hit && (tri_dist < r_dist))
                {
                    hit            = true;
                    r_dist         = tri_dist;
                    r_entity_index = m_entity_tri_list[i][0];
                    r_tri_index    = m_entity_tri_list[i][1];
                }
            }

            // If a hit did occur, return the information.
            if (hit)
            {
                return (std::tuple<bool, double, size_t, size_t>(true, r_dist, r_entity_index, r_tri_index));
            }

            return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN()));
        }

        /**
         *  Determine the distance to the closest ccd triangle within the cell.
         *  If no ccd is hit, the first value of the tuple will be set to false.
         *  The second value of the returned tuple holds the distance to the ccd triangle if one was hit.
         *  The third and fourth values of the returned tuple hold the hit ccd and triangle indices respectively.
         *  If no ccd triangle is hit the first value is false and the others are set to NaN.
         *
         *  @param  t_pos       Start position of the ray.
         *  @param  t_dir       Direction of the ray.
         *
         *  @return A tuple containing, hit status, distance to intersection, collision ccd and triangle indices.
         */
        std::tuple<bool, double, size_t, size_t> Cell::ccd_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no ccd triangles, there is no hit.
            if (m_ccd_tri_list.empty())
            {
                return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN()));
            }

            // Run through all ccd triangles and determine if any hits occur.
            bool        hit         = false;
            double      r_dist      = std::numeric_limits<double>::max();
            size_t      r_ccd_index = std::numeric_limits<size_t>::signaling_NaN();
            size_t      r_tri_index = std::numeric_limits<size_t>::signaling_NaN();
            for (size_t i           = 0; i < m_ccd_tri_list.size(); ++i)
            {
                // Get a reference to the triangle.
                const geom::Triangle& tri = m_ccd[m_ccd_tri_list[i][0]].get_mesh().get_tri(m_ccd_tri_list[i][1]);

                // Determine if there is a hit.
                bool   tri_hit;
                double tri_dist;
                std::tie(tri_hit, tri_dist) = tri.intersection_dist(t_pos, t_dir);

                // If a hit does occur, and it is closer than any hit so far, store the information.
                if (tri_hit && (tri_dist < r_dist))
                {
                    hit         = true;
                    r_dist      = tri_dist;
                    r_ccd_index = m_ccd_tri_list[i][0];
                    r_tri_index = m_ccd_tri_list[i][1];
                }
            }

            // If a hit did occur, return the information.
            if (hit)
            {
                return (std::tuple<bool, double, size_t, size_t>(true, r_dist, r_ccd_index, r_tri_index));
            }

            return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN()));
        }

        /**
         *  Determine the distance to the closest spectrometer triangle within the cell.
         *  If no spectrometer is hit, the first value of the tuple will be set to false.
         *  The second value of the returned tuple holds the distance to the spectrometer triangle if one was hit.
         *  The third and fourth values of the returned tuple hold the hit spectrometer and triangle indices respectively.
         *  If no spectrometer triangle is hit the first value is false and the others are set to NaN.
         *
         *  @param  t_pos       Start position of the ray.
         *  @param  t_dir       Direction of the ray.
         *
         *  @return A tuple containing, hit status, distance to intersection, collision spectrometer and triangle indices.
         */
        std::tuple<bool, double, size_t, size_t> Cell::spectrometer_dist(const math::Vec<3>& t_pos,
                                                                         const math::Vec<3>& t_dir) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no spectrometer triangles, there is no hit.
            if (m_spectrometer_tri_list.empty())
            {
                return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN(),
                                                                 std::numeric_limits<size_t>::signaling_NaN()));
            }

            // Run through all spectrometer triangles and determine if any hits occur.
            bool        hit                  = false;
            double      r_dist               = std::numeric_limits<double>::max();
            size_t      r_spectrometer_index = std::numeric_limits<size_t>::signaling_NaN();
            size_t      r_tri_index          = std::numeric_limits<size_t>::signaling_NaN();
            for (size_t i                    = 0; i < m_spectrometer_tri_list.size(); ++i)
            {
                // Get a reference to the triangle.
                const geom::Triangle& tri = m_spectrometer[m_spectrometer_tri_list[i][0]].get_mesh().get_tri(
                    m_spectrometer_tri_list[i][1]);

                // Determine if there is a hit.
                bool   tri_hit;
                double tri_dist;
                std::tie(tri_hit, tri_dist) = tri.intersection_dist(t_pos, t_dir);

                // If a hit does occur, and it is closer than any hit so far, store the information.
                if (tri_hit && (tri_dist < r_dist))
                {
                    hit                  = true;
                    r_dist               = tri_dist;
                    r_spectrometer_index = m_spectrometer_tri_list[i][0];
                    r_tri_index          = m_spectrometer_tri_list[i][1];
                }
            }

            // If a hit did occur, return the information.
            if (hit)
            {
                return (std::tuple<bool, double, size_t, size_t>(true, r_dist, r_spectrometer_index, r_tri_index));
            }

            return (std::tuple<bool, double, size_t, size_t>(false, std::numeric_limits<double>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN(),
                                                             std::numeric_limits<size_t>::signaling_NaN()));
        }


        //  -- Setters --
        /**
         *  Add a given energy to the total energy of the cell.
         *
         *  @param  t_energy    Energy to add to the cell.
         *
         *  @pre    t_energy must be positive.
         */
        void Cell::add_energy(const double t_energy)
        {
            assert(t_energy > 0.0);

            m_energy += t_energy;
        }


        //  -- Overlap Test --
        /**
         *  Determine if the cell box is intersecting with a triangle.
         *  Cell and triangle are considered to be overlapping even if the triangle is in the plane of the box.
         *
         *  @param  t_tri       Triangle to test intersection with.
         *
         *  @return True if the cell and triangle are intersecting.
         */
        bool Cell::tri_overlap(const geom::Triangle& t_tri) const
        {
            // Translate everything so the box center is at the origin.
            const math::Vec<3> v0 = t_tri.get_pos(0) - m_center;
            const math::Vec<3> v1 = t_tri.get_pos(1) - m_center;
            const math::Vec<3> v2 = t_tri.get_pos(2) - m_center;

            // Compute triangle edges.
            const math::Vec<3> e0 = v1 - v0;
            const math::Vec<3> e1 = v2 - v1;
            const math::Vec<3> e2 = v0 - v2;

            double p0, p2, rad;

            p0  = (e0[Z] * v0[Y]) - (e0[Y] * v0[Z]);
            p2  = (e0[Z] * v2[Y]) - (e0[Y] * v2[Z]);
            rad = (std::fabs(e0[Z]) * m_half_width[Y]) + (std::fabs(e0[Y]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e0[Z] * v0[X]) + (e0[X] * v0[Z]);
            p2  = (-e0[Z] * v2[X]) + (e0[X] * v2[Z]);
            rad = (std::fabs(e0[Z]) * m_half_width[X]) + (std::fabs(e0[X]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e0[Y] * v1[X]) - (e0[X] * v1[Y]);
            p2  = (e0[Y] * v2[X]) - (e0[X] * v2[Y]);
            rad = (std::fabs(e0[Y]) * m_half_width[X]) + (std::fabs(e0[X]) * m_half_width[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Z] * v0[Y]) - (e1[Y] * v0[Z]);
            p2  = (e1[Z] * v2[Y]) - (e1[Y] * v2[Z]);
            rad = (std::fabs(e1[Z]) * m_half_width[Y]) + (std::fabs(e1[Y]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e1[Z] * v0[X]) + (e1[X] * v0[Z]);
            p2  = (-e1[Z] * v2[X]) + (e1[X] * v2[Z]);
            rad = (std::fabs(e1[Z]) * m_half_width[X]) + (std::fabs(e1[X]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Y] * v0[X]) - (e1[X] * v0[Y]);
            p2  = (e1[Y] * v1[X]) - (e1[X] * v1[Y]);
            rad = (std::fabs(e1[Y]) * m_half_width[X]) + (std::fabs(e1[X]) * m_half_width[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Z] * v0[Y]) - (e2[Y] * v0[Z]);
            p2  = (e2[Z] * v1[Y]) - (e2[Y] * v1[Z]);
            rad = (std::fabs(e2[Z]) * m_half_width[Y]) + (std::fabs(e2[Y]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e2[Z] * v0[X]) + (e2[X] * v0[Z]);
            p2  = (-e2[Z] * v1[X]) + (e2[X] * v1[Z]);
            rad = (std::fabs(e2[Z]) * m_half_width[X]) + (std::fabs(e2[X]) * m_half_width[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Y] * v1[X]) - (e2[X] * v1[Y]);
            p2  = (e2[Y] * v2[X]) - (e2[X] * v2[Y]);
            rad = (std::fabs(e2[Y]) * m_half_width[X]) + (std::fabs(e2[X]) * m_half_width[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            auto find_min_max = [](const double x0, const double x1, const double x2, double& min, double& max)
            {
                min = max = x0;

                if (x1 < min)
                {
                    min = x1;
                }
                if (x1 > max)
                {
                    max = x1;
                }
                if (x2 < min)
                {
                    min = x2;
                }
                if (x2 > max)
                {
                    max = x2;
                }
            };

            double min, max;
            find_min_max(v0[X], v1[X], v2[X], min, max);
            if ((min > m_half_width[X]) || (max < -m_half_width[X]))
            {
                return (false);
            }

            find_min_max(v0[Y], v1[Y], v2[Y], min, max);
            if ((min > m_half_width[Y]) || (max < -m_half_width[Y]))
            {
                return (false);
            }

            find_min_max(v0[Z], v1[Z], v2[Z], min, max);
            if ((min > m_half_width[Z]) || (max < -m_half_width[Z]))
            {
                return (false);
            }

            return (plane_overlap(e0 ^ e1, v0));
        }

        /**
         *  Determine if a plane described by a given normal and point overlaps with the box centered at the origin.
         *
         *  @param  t_norm          Normal of the plane.
         *  @param  t_point         Point located on the plane.
         *
         *  @return True if the plane and box are intersecting.
         */
        bool Cell::plane_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point) const
        {
            math::Vec<3> min, max;

            for (size_t q = 0; q < 3; ++q)
            {
                double v = t_point[q];

                if (t_norm[q] > 0.0)
                {
                    min[q] = -m_half_width[q] - v;
                    max[q] = m_half_width[q] - v;
                }
                else
                {
                    min[q] = m_half_width[q] - v;
                    max[q] = -m_half_width[q] - v;
                }
            }

            return (((t_norm * min) <= 0.0) && ((t_norm * max) >= 0.0));
        }



    } // namespace tree
} // namespace arc
