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
            const bool m_empty; //! True if the cell contains no triangles.


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
            bool empty() const { return (m_empty); }

            //  -- Testing --
            inline bool is_within(const math::Vec<3>& t_point) const;
        };



        //  -- Testing --
        /**
         *  Test if a given point is located within the cell.
         *
         *  @param  t_point Point to be tested.
         *
         *  @return True if the point is located within the cell.
         */
        bool Cell::is_within(const math::Vec<3>& t_point) const
        {
            return (t_point[X] >= m_min_bound[X]) && (t_point[X] <= m_max_bound[X]) && (t_point[Y] >= m_min_bound[Y]) && (t_point[Y] <= m_max_bound[Y]) && (t_point[Z] >= m_min_bound[Z]) && (t_point[Z] <= m_max_bound[Z]);
        }



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_CELL_HPP
