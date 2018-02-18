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
          private:
            //  -- Getters --
            size_t get_num_cells() const { return (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z]); }
            size_t get_num_cells(const size_t t_dimension) const { return (m_num_cells[t_dimension]); }
        };



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_GRID_HPP
