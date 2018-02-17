/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == HEADER ==
#include "cls/mesh/grid.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a grid within given bounds.
         *
         *  @param  t_min_bound     Minimum grid bound.
         *  @param  t_max_bound     Maximum grid bound.
         *  @param  t_num_x_cells   Number of cells across the x-dimension.
         *  @param  t_num_y_cells   Number of cells across the y-dimension.
         *  @param  t_num_z_cells   Number of cells across the z-dimension.
         */
        Grid::Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const size_t t_num_x_cells,
                   const size_t t_num_y_cells, const size_t t_num_z_cells) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_num_cells({{t_num_x_cells, t_num_y_cells, t_num_z_cells}}),
            m_grid_vol(
                (t_max_bound[X] - t_min_bound[X]) * (t_max_bound[Y] - t_min_bound[Y]) * (t_max_bound[Z] - t_min_bound[Z])),
            m_cell_vol(m_grid_vol / (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z]))
        {
        }



        //  -- Initialisation --



    } // namespace mesh
} // namespace arc
