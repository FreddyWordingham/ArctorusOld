/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MESH_CELL_HPP
#define ARCTORUS_SRC_CLS_MESH_CELL_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <vector>

//  -- Classes --
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == CLASS ==
        /**
         *  Information about a single cell of the simulation.
         */
        class Cell
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_min_bound; //! Minimum bound of the cell.
            const math::Vec<3> m_max_bound; //! Maximum bound of the cell.

            //  -- Lists --
            const std::vector<std::array<size_t, 2>> m_entity_list; //! List of entity triangles with the cell.
            const std::vector<std::array<size_t, 2>> m_light_list;  //! List of light triangles with the cell.

            //  -- Data --
            const bool m_empty;         //! True if the cell contains no triangles.
            double     m_energy = 0.0;  //! Energy withihn the cell.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                 const std::vector<equip::Light>& t_light);

          private:
            //  -- Initialisation --
            std::vector<std::array<size_t, 2>> init_entity_list(const std::vector<equip::Entity>& t_entity) const;
            std::vector<std::array<size_t, 2>> init_light_list(const std::vector<equip::Light>& t_light) const;
            bool tri_overlap(const math::Vec<3>& t_center, const math::Vec<3>& t_half_size, const geom::Triangle& t_tri) const;
            bool plane_origin_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point,
                                      const math::Vec<3>& t_half_width) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_min_bound() const { return (m_min_bound); }
            const math::Vec<3>& get_max_bound() const { return (m_max_bound); }
            double get_volume() const { return ((m_max_bound[X] - m_min_bound[X]) * (m_max_bound[Y] - m_min_bound[Y]) * (m_max_bound[Z] - m_min_bound[Z])); }
            double get_energy_density() const { return (m_energy / get_volume()); }
            bool empty() const { return (m_empty); }
            double get_dist_to_wall(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            double get_dist_to_entity(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir,
                                      const std::vector<equip::Entity>& t_entity) const
            {
                // If cell contains no entity triangles, return a large dummy value.
                if (m_empty)
                {
                    return (std::numeric_limits<double>::max());
                }

                // Run through all entity triangles and determine the closest intersection distance.
                double      r_dist = std::numeric_limits<double>::max();
                for (size_t i      = 0; i < m_entity_list.size(); ++i)
                {
                    // Get the triangle.
                    const geom::Triangle& tri = t_entity[m_entity_list[i][0]].get_mesh().get_tri(m_entity_list[i][1]);

                    // Get distance to intersection.
                    const double tri_dist = tri.get_intersection_dist(t_pos, t_dir);

                    // If this distance is the closest so far, accept it.
                    if ((tri_dist < r_dist) && (tri_dist > 0.0))
                    {
                        r_dist = tri_dist;
                    }
                }

                return (r_dist);
            }

            //  -- Setters --
            void add_energy(double t_energy);

            //  -- Testing --
            bool is_within(const math::Vec<3>& t_pos) const;
        };



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_CELL_HPP
