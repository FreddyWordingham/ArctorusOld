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
         *  @param  t_min_bound Minimum grid bound.
         *  @param  t_max_bound Maximum grid bound.
         *  @param  t_num_cells Number of cells across each dimension.
         *  @param  t_entity    Vector of entities which may be contained within the grid.
         *  @param  t_light     Vector of lights which may be contained within the grid.
         */
        Grid::Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::array<size_t, 3> t_num_cells,
                   const std::vector<equip::Entity>& t_entity, const std::vector<equip::Light>& t_light) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_num_cells(t_num_cells),
            m_grid_vol(
                (t_max_bound[X] - t_min_bound[X]) * (t_max_bound[Y] - t_min_bound[Y]) * (t_max_bound[Z] - t_min_bound[Z])),
            m_cell_vol(m_grid_vol / (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z])),
            m_cell(init_cell(t_entity, t_light))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the three-dimensional vector of cells.
         *
         *  @param  t_entity    Vector of entities which may be contained within the grid.
         *  @param  t_light     Vector of lights which may be contained within the grid.
         *
         *  @return The initialised three-dimensional vector of cells.
         */
        std::vector<std::vector<std::vector<Cell>>> Grid::init_cell(const std::vector<equip::Entity>& t_entity,
                                                                    const std::vector<equip::Light>& t_light) const
        {
            // Create three-dimensional vector of cells.
            std::vector<std::vector<std::vector<Cell>>> r_cell;

            // Create the cells.
            r_cell.reserve(m_num_cells[X]);
            for (size_t i = 0; i < m_num_cells[X]; ++i)
            {
                r_cell.emplace_back(std::vector<std::vector<Cell>>());
                r_cell[i].reserve(m_num_cells[Y]);
                for (size_t j = 0; j < m_num_cells[Y]; ++j)
                {
                    r_cell[i].emplace_back(std::vector<Cell>());
                    r_cell[i][j].reserve(m_num_cells[Z]);
                    for (size_t k = 0; k < m_num_cells[Z]; ++k)
                    {
                        r_cell[i][j].emplace_back(Cell(math::Vec<3>({{0.0, 0.0, 0.0}}), math::Vec<3>({{0.0, 0.0, 0.0}})));
                    }
                }
            }

            return (r_cell);
        }



    } // namespace mesh
} // namespace arc
