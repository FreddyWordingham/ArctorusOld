/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == HEADER ==
#include "cls/mesh/cell.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a cell with given bounds which may contain triangles of the given entities.
         *
         *  @param  t_min_bound     Minimum bound of the cell.
         *  @param  t_max_bound     Maximum bound of the cell.
         *  @param  t_entity        Vector of entities which may be contained within the cell.
         *  @param  t_light         Vector of lights which may be contained within the cell.
         *  @param  t_ccd           Vector of ccds which may be contained within the cell.
         *  @param  t_spectrometer  Vector of spectrometers which may be contained within the cell.
         */
        Cell::Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                   const std::vector<detector::Spectrometer>& t_spectrometer) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_entity(t_entity),
            m_light(t_light),
            m_ccd(t_ccd),
            m_spectrometer(t_spectrometer),
            m_entity_tri_list(init_entity_tri_list()),
            m_light_tri_list(init_light_tri_list()),
            m_ccd_tri_list(init_ccd_tri_list()),
            m_spectrometer_tri_list(init_spectrometer_tri_list()),
            m_empty(m_entity_tri_list.empty() && m_light_tri_list.empty() && m_ccd_tri_list.empty() && m_spectrometer_tri_list
                .empty())
        {
            assert(t_max_bound[X] > t_min_bound[X]);
            assert(t_max_bound[Y] > t_min_bound[Y]);
            assert(t_max_bound[Z] > t_min_bound[Z]);
        }

        /**
         *  Move construct a cell object.
         *
         *  @param  t_cell  Cell to be moved.
         */
        Cell::Cell(Cell&& t_cell) :
            m_min_bound(std::move(t_cell.m_min_bound)),
            m_max_bound(std::move(t_cell.m_max_bound)),
            m_entity(std::move(t_cell.m_entity)),
            m_light(std::move(t_cell.m_light)),
            m_ccd(std::move(t_cell.m_ccd)),
            m_spectrometer(std::move(t_cell.m_spectrometer)),
            m_entity_tri_list(std::move(t_cell.m_entity_tri_list)),
            m_light_tri_list(std::move(t_cell.m_light_tri_list)),
            m_ccd_tri_list(std::move(t_cell.m_ccd_tri_list)),
            m_spectrometer_tri_list(std::move(t_cell.m_spectrometer_tri_list)),
            m_empty(std::move(t_cell.m_empty)),
            m_energy(std::move(t_cell.m_energy))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the list of entity triangles found within the cell.
         *
         *  @return The initialised list of entity triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_entity_tri_list() const
        {
            std::vector<std::array<size_t, 2>> r_entity_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < m_entity.size(); ++i)
            {
                for (size_t j = 0; j < m_entity[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, m_entity[i].get_mesh().get_tri(j)))
                    {
                        r_entity_list.push_back({{i, j}});
                    }
                }
            }

            return (r_entity_list);
        }

        /**
         *  Initialise the list of light triangles found within the cell.
         *
         *  @return The initialised list of light triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_light_tri_list() const
        {
            std::vector<std::array<size_t, 2>> r_light_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < m_light.size(); ++i)
            {
                for (size_t j = 0; j < m_light[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, m_light[i].get_mesh().get_tri(j)))
                    {
                        r_light_list.push_back({{i, j}});
                    }
                }
            }

            return (r_light_list);
        }

        /**
         *  Initialise the list of ccd triangles found within the cell.
         *
         *  @return The initialised list of ccd triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_ccd_tri_list() const
        {
            std::vector<std::array<size_t, 2>> r_ccd_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < m_ccd.size(); ++i)
            {
                for (size_t j = 0; j < m_ccd[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, m_ccd[i].get_mesh().get_tri(j)))
                    {
                        r_ccd_list.push_back({{i, j}});
                    }
                }
            }

            return (r_ccd_list);
        }

        /**
         *  Initialise the list of spectrometer triangles found within the cell.
         *
         *  @return The initialised list of spectrometer triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_spectrometer_tri_list() const
        {
            std::vector<std::array<size_t, 2>> r_spectrometer_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < m_spectrometer.size(); ++i)
            {
                for (size_t j = 0; j < m_spectrometer[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, m_spectrometer[i].get_mesh().get_tri(j)))
                    {
                        r_spectrometer_list.push_back({{i, j}});
                    }
                }
            }

            return (r_spectrometer_list);
        }

        /**
         *  Determine if an axis-aligned bounding box is intersecting with a triangle.
         *  Box and triangle are considered to be overlapping even if the triangle is in the plane of the box.
         *
         *  @param  t_center    Center of the box.
         *  @param  t_half_size Half-size of the box.
         *  @param  t_tri       Triangle to test intersection with.
         *
         *  @return True if the box and triangle are intersecting.
         */
        bool Cell::tri_overlap(const math::Vec<3>& t_center, const math::Vec<3>& t_half_size, const geom::Triangle& t_tri) const
        {
            // Translate everything so the box center is at the origin.
            const math::Vec<3> v0 = t_tri.get_pos(0) - t_center;
            const math::Vec<3> v1 = t_tri.get_pos(1) - t_center;
            const math::Vec<3> v2 = t_tri.get_pos(2) - t_center;

            // Compute triangle edges.
            const math::Vec<3> e0 = v1 - v0;
            const math::Vec<3> e1 = v2 - v1;
            const math::Vec<3> e2 = v0 - v2;

            double p0, p2, rad;

            p0  = (e0[Z] * v0[Y]) - (e0[Y] * v0[Z]);
            p2  = (e0[Z] * v2[Y]) - (e0[Y] * v2[Z]);
            rad = (std::fabs(e0[Z]) * t_half_size[Y]) + (std::fabs(e0[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e0[Z] * v0[X]) + (e0[X] * v0[Z]);
            p2  = (-e0[Z] * v2[X]) + (e0[X] * v2[Z]);
            rad = (std::fabs(e0[Z]) * t_half_size[X]) + (std::fabs(e0[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e0[Y] * v1[X]) - (e0[X] * v1[Y]);
            p2  = (e0[Y] * v2[X]) - (e0[X] * v2[Y]);
            rad = (std::fabs(e0[Y]) * t_half_size[X]) + (std::fabs(e0[X]) * t_half_size[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Z] * v0[Y]) - (e1[Y] * v0[Z]);
            p2  = (e1[Z] * v2[Y]) - (e1[Y] * v2[Z]);
            rad = (std::fabs(e1[Z]) * t_half_size[Y]) + (std::fabs(e1[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e1[Z] * v0[X]) + (e1[X] * v0[Z]);
            p2  = (-e1[Z] * v2[X]) + (e1[X] * v2[Z]);
            rad = (std::fabs(e1[Z]) * t_half_size[X]) + (std::fabs(e1[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Y] * v0[X]) - (e1[X] * v0[Y]);
            p2  = (e1[Y] * v1[X]) - (e1[X] * v1[Y]);
            rad = (std::fabs(e1[Y]) * t_half_size[X]) + (std::fabs(e1[X]) * t_half_size[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Z] * v0[Y]) - (e2[Y] * v0[Z]);
            p2  = (e2[Z] * v1[Y]) - (e2[Y] * v1[Z]);
            rad = (std::fabs(e2[Z]) * t_half_size[Y]) + (std::fabs(e2[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e2[Z] * v0[X]) + (e2[X] * v0[Z]);
            p2  = (-e2[Z] * v1[X]) + (e2[X] * v1[Z]);
            rad = (std::fabs(e2[Z]) * t_half_size[X]) + (std::fabs(e2[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Y] * v1[X]) - (e2[X] * v1[Y]);
            p2  = (e2[Y] * v2[X]) - (e2[X] * v2[Y]);
            rad = (std::fabs(e2[Y]) * t_half_size[X]) + (std::fabs(e2[X]) * t_half_size[Y]);
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
            if ((min > t_half_size[X]) || (max < -t_half_size[X]))
            {
                return (false);
            }

            find_min_max(v0[Y], v1[Y], v2[Y], min, max);
            if ((min > t_half_size[Y]) || (max < -t_half_size[Y]))
            {
                return (false);
            }

            find_min_max(v0[Z], v1[Z], v2[Z], min, max);
            if ((min > t_half_size[Z]) || (max < -t_half_size[Z]))
            {
                return (false);
            }

            return plane_origin_overlap(e0 ^ e1, v0, t_half_size);
        }

        /**
         *  Determine if a plane described by a given normal and point overlaps with a given box centered at the origin.
         *
         *  @param  t_norm          Normal of the plane.
         *  @param  t_point         Point located on the plane.
         *  @param  t_half_width    Half sizes of the box.
         *
         *  @return True if the plane and box are intersecting.
         */
        bool Cell::plane_origin_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point,
                                        const math::Vec<3>& t_half_width) const
        {
            math::Vec<3> min, max;

            for (size_t q = 0; q < 3; ++q)
            {
                double v = t_point[q];

                if (t_norm[q] > 0.0)
                {
                    min[q] = -t_half_width[q] - v;
                    max[q] = t_half_width[q] - v;
                }
                else
                {
                    min[q] = t_half_width[q] - v;
                    max[q] = -t_half_width[q] - v;
                }
            }

            return (((t_norm * min) <= 0.0) && ((t_norm * max) >= 0.0));

        }



        //  == METHODS ==
        //  -- Getters --
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
                                                      : (m_min_bound[i] - t_pos[i]) / t_dir[i];
                dist[(i * 2) + 1] = (t_dir[i] == 0.0) ? std::numeric_limits<double>::max()
                                                      : (m_max_bound[i] - t_pos[i]) / t_dir[i];
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

            m_energy_mutex.lock();
            m_energy += t_energy;
            m_energy_mutex.unlock();
        }


        //  -- Testing --
        /**
         *  Test if a given position is located within the cell.
         *
         *  @param  t_pos   Position to be tested.
         *
         *  @return True if the position is located within the cell.
         */
        bool Cell::is_within(const math::Vec<3>& t_pos) const
        {
            return (t_pos[X] >= m_min_bound[X]) && (t_pos[X] <= m_max_bound[X]) && (t_pos[Y] >= m_min_bound[Y]) && (t_pos[Y] <= m_max_bound[Y]) && (t_pos[Z] >= m_min_bound[Z]) && (t_pos[Z] <= m_max_bound[Z]);
        }



    } // namespace mesh
} // namespace arc
