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
            const bool m_empty;                 //! True if the cell contains no triangles.
            double     m_energy_density = 0.0;  //! Energy density of the cell.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                 const std::vector<equip::Light>& t_light);

          private:
            //  -- Initialisation --
            std::vector<std::array<size_t, 2>> init_entity_list(const std::vector<equip::Entity>& t_entity) const;
            std::vector<std::array<size_t, 2>> init_light_list(const std::vector<equip::Light>& t_light) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_min_bound() const { return (m_min_bound); }
            const math::Vec<3>& get_max_bound() const { return (m_max_bound); }
            double get_energy_density() const { return (m_energy_density); }
            bool empty() const { return (m_empty); }

            //  -- Testing --
            inline bool is_within(const math::Vec<3>& t_pos) const;

            //  -- Simulation --
            inline double dist_to_boundary(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
        };



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


        //  -- Simulation --
        /**
         *  Determine the distance to the cell boundary from a given point along a given vector.
         *
         *  @param  t_pos   Position of the point.
         *  @param  t_dir   Direction of the path.
         *
         *  @pre    t_pos   Must be within this cell.
         *
         *  @post   r_dist must be positive.
         *
         *  @return The distance along the direction vector from the point until the boundary of the cell is reached.
         */
        double Cell::dist_to_boundary(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
        {
            assert(is_within(t_pos));

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



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_CELL_HPP
