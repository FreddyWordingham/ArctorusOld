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
            m_entity_list(init_entity_list(t_entity)),
            m_light_list(init_light_list(t_light)),
            m_ccd_list(init_ccd_list(t_ccd)),
            m_spectrometer_list(init_spectrometer_list(t_spectrometer)),
            m_empty(m_entity_list.empty() && m_light_list.empty() && m_ccd_list.empty() && m_spectrometer_list.empty())
        {
            assert(t_max_bound[X] > t_min_bound[X]);
            assert(t_max_bound[Y] > t_min_bound[Y]);
            assert(t_max_bound[Z] > t_min_bound[Z]);
        }


        //  -- Initialisation --
        /**
         *  Initialise the list of entity triangles found within the cell.
         *
         *  @param  t_entity    Vector of entities which may be contained within the cell.
         *
         *  @return The initialised list of entity triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_entity_list(const std::vector<equip::Entity>& t_entity) const
        {
            std::vector<std::array<size_t, 2>> r_entity_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_entity.size(); ++i)
            {
                for (size_t j = 0; j < t_entity[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, t_entity[i].get_mesh().get_tri(j)))
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
         *  @param  t_light Vector of lights which may be contained within the cell.
         *
         *  @return The initialised list of light triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_light_list(const std::vector<equip::Light>& t_light) const
        {
            std::vector<std::array<size_t, 2>> r_light_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_light.size(); ++i)
            {
                for (size_t j = 0; j < t_light[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, t_light[i].get_mesh().get_tri(j)))
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
         *  @param  t_ccd   Vector of ccds which may be contained within the cell.
         *
         *  @return The initialised list of ccd triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_ccd_list(const std::vector<detector::Ccd>& t_ccd) const
        {
            std::vector<std::array<size_t, 2>> r_ccd_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_ccd.size(); ++i)
            {
                for (size_t j = 0; j < t_ccd[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, t_ccd[i].get_mesh().get_tri(j)))
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
         *  @param  t_spectrometer  Vector of spectrometers which may be contained within the cell.
         *
         *  @return The initialised list of spectrometer triangles found within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_spectrometer_list(
            const std::vector<detector::Spectrometer>& t_spectrometer) const
        {
            std::vector<std::array<size_t, 2>> r_spectrometer_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_spectrometer.size(); ++i)
            {
                for (size_t j = 0; j < t_spectrometer[i].get_mesh().get_num_tri(); ++j)
                {
                    if (tri_overlap(center, half_size, t_spectrometer[i].get_mesh().get_tri(j)))
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
            const math::Vec<3> v0 = t_tri.get_vert(0).get_pos() - t_center;
            const math::Vec<3> v1 = t_tri.get_vert(1).get_pos() - t_center;
            const math::Vec<3> v2 = t_tri.get_vert(2).get_pos() - t_center;

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
         *  Determine the distance along the given ray to the nearest entity triangle.
         *  Also return the index of the entity, as well as the normal of the entity triangle.
         *
         *  @param  t_pos       Initial position of the ray.
         *  @param  t_dir       Direction of the ray.
         *  @param  t_entity    Vector of entities within the simulation.
         *
         *  @return A tuple containing the entity index, distance to the entity triangle and the normal at the intersection.
         */
        std::tuple<size_t, double, math::Vec<3>> Cell::get_dist_to_entity(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir,
                                                                          const std::vector<equip::Entity>& t_entity) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no triangles, return a large dummy value.
            if (m_empty)
            {
                return (std::tuple<size_t, double, math::Vec<3>>(0, std::numeric_limits<double>::max(),
                                                                 math::Vec<3>({{0.0, 0.0, 0.0}})));
            }

            // Run through all entity triangles and determine the closest intersection distance.
            size_t       r_index;
            double       r_dist = std::numeric_limits<double>::max();
            math::Vec<3> r_norm;
            for (size_t  i      = 0; i < m_entity_list.size(); ++i)
            {
                // Get distance to intersection.
                double       tri_dist;
                math::Vec<3> tri_norm;
                std::tie(tri_dist, tri_norm) = t_entity[m_entity_list[i][0]].get_mesh().get_tri(m_entity_list[i][1])
                                                                            .get_intersection(t_pos, t_dir);

                // If this distance is the closest so far, accept it.
                if ((tri_dist < r_dist) && (tri_dist > 0.0))
                {
                    r_index = m_entity_list[i][0];
                    r_dist  = tri_dist;
                    r_norm  = tri_norm;
                }
            }

            assert(r_dist > 0.0);

            return (std::tuple<size_t, double, math::Vec<3>>(r_index, r_dist, r_norm));
        }

        /**
         *  Determine the distance along the given ray to the nearest ccd triangle.
         *  Also return the index of the ccd, as well as the normal of the ccd triangle.
         *
         *  @param  t_pos   Initial position of the ray.
         *  @param  t_dir   Direction of the ray.
         *  @param  t_ccd   Vector of ccds within the simulation.
         *
         *  @return A tuple containing the ccd index, distance to the ccd triangle and the normal at the intersection.
         */
        std::tuple<size_t, double, math::Vec<3>> Cell::get_dist_to_ccd(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir,
                                                                       const std::vector<detector::Ccd>& t_ccd) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no triangles, return a large dummy value.
            if (m_empty)
            {
                return (std::tuple<size_t, double, math::Vec<3>>(0, std::numeric_limits<double>::max(),
                                                                 math::Vec<3>({{0.0, 0.0, 0.0}})));
            }

            // Run through all ccd triangles and determine the closest intersection distance.
            size_t       r_index;
            double       r_dist = std::numeric_limits<double>::max();
            math::Vec<3> r_norm;
            for (size_t  i      = 0; i < m_ccd_list.size(); ++i)
            {
                // Get distance to intersection.
                double       tri_dist;
                math::Vec<3> tri_norm;
                std::tie(tri_dist, tri_norm) = t_ccd[m_ccd_list[i][0]].get_mesh().get_tri(m_ccd_list[i][1])
                                                                      .get_intersection(t_pos, t_dir);

                // If this distance is the closest so far, accept it.
                if ((tri_dist < r_dist) && (tri_dist > 0.0))
                {
                    r_index = m_ccd_list[i][0];
                    r_dist  = tri_dist;
                    r_norm  = tri_norm;
                }
            }

            assert(r_dist > 0.0);

            return (std::tuple<size_t, double, math::Vec<3>>(r_index, r_dist, r_norm));
        }

        /**
         *  Determine the distance along the given ray to the nearest spectrometer triangle.
         *  Also return the index of the spectrometer, as well as the normal of the spectrometer triangle.
         *
         *  @param  t_pos           Initial position of the ray.
         *  @param  t_dir           Direction of the ray.
         *  @param  t_spectrometer  Vector of spectrometers within the simulation.
         *
         *  @return A tuple containing the spectrometer index, distance to the spectrometer triangle and the normal at the
         *  intersection.
         */
        std::tuple<size_t, double, math::Vec<3>> Cell::get_dist_to_spectrometer(const math::Vec<3>& t_pos,
                                                                                const math::Vec<3>& t_dir, const std::vector<
            detector::Spectrometer>& t_spectrometer) const
        {
            assert(t_dir.is_normalised());

            // If cell contains no triangles, return a large dummy value.
            if (m_empty)
            {
                return (std::tuple<size_t, double, math::Vec<3>>(0, std::numeric_limits<double>::max(),
                                                                 math::Vec<3>({{0.0, 0.0, 0.0}})));
            }

            // Run through all spectrometer triangles and determine the closest intersection distance.
            size_t       r_index;
            double       r_dist = std::numeric_limits<double>::max();
            math::Vec<3> r_norm;
            for (size_t  i      = 0; i < m_spectrometer_list.size(); ++i)
            {
                // Get distance to intersection.
                double       tri_dist;
                math::Vec<3> tri_norm;
                std::tie(tri_dist, tri_norm) = t_spectrometer[m_spectrometer_list[i][0]].get_mesh()
                                                                                        .get_tri(m_spectrometer_list[i][1])
                                                                                        .get_intersection(t_pos, t_dir);

                // If this distance is the closest so far, accept it.
                if ((tri_dist < r_dist) && (tri_dist > 0.0))
                {
                    r_index = m_spectrometer_list[i][0];
                    r_dist  = tri_dist;
                    r_norm  = tri_norm;
                }
            }

            assert(r_dist > 0.0);

            return (std::tuple<size_t, double, math::Vec<3>>(r_index, r_dist, r_norm));
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
