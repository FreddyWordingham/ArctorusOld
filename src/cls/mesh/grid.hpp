/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MESH_GRID_HPP
#define ARCTORUS_SRC_CLS_MESH_GRID_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/math/vec.hpp"
#include "cls/mesh/cell.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == CLASS ==
        /**
         *  Grid mesh class storing a three-dimensional vector of uniform cells.
         */
        class Grid
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_min_bound; //! Minimum bound of the grid.
            const math::Vec<3> m_max_bound; //! Maximum bound of the grid.

            //  -- Information --
            const std::array<size_t, 3> m_num_cells;    //! Number of cells in each dimension.
            const double                m_grid_vol;     //! Volume of the total grid.
            const double                m_cell_vol;     //! Volume of each cell.

            //  -- Data --
            const std::vector<std::vector<std::vector<Cell>>> m_cell;   //! Three-dimensional vector of cells.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, std::array<size_t, 3> t_num_cells,
                 const std::vector<equip::Entity>& t_entity, const std::vector<equip::Light>& t_light);

          private:
            //  -- Initialisation --
            std::vector<std::vector<std::vector<Cell>>> init_cell(const std::vector<equip::Entity>& t_entity,
                                                                  const std::vector<equip::Light>& t_light) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_min_bound() const { return (m_min_bound); }
            const math::Vec<3>& get_max_bound() const { return (m_max_bound); }
            size_t get_num_cells() const { return (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z]); }
            size_t get_num_cells(const size_t t_dimension) const { return (m_num_cells[t_dimension]); }
            const Cell& get_cell(const size_t t_i, const size_t t_j, const size_t t_k) const { return (m_cell[t_i][t_j][t_k]); }

            //  -- Testing --
            inline bool is_within(const math::Vec<3>& t_point) const;
        };



        //  == METHODS ==
        //  -- Testing --
        /**
         *  Test if a given point is located within the grid.
         *
         *  @param  t_point Point to be tested.
         *
         *  @return True if the point is located within the grid.
         */
        bool Grid::is_within(const math::Vec<3>& t_point) const
        {
            return (t_point[X] >= m_min_bound[X]) && (t_point[X] <= m_max_bound[X]) && (t_point[Y] >= m_min_bound[Y]) && (t_point[Y] <= m_max_bound[Y]) && (t_point[Z] >= m_min_bound[Z]) && (t_point[Z] <= m_max_bound[Z]);
        }



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_GRID_HPP
