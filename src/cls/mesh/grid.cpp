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
                (m_max_bound[X] - m_min_bound[X]) * (m_max_bound[Y] - m_min_bound[Y]) * (m_max_bound[Z] - m_min_bound[Z])),
            m_cell_size(
                {{(m_max_bound[X] - m_min_bound[X]) / m_num_cells[X], (m_max_bound[Y] - m_min_bound[Y]) / m_num_cells[Y], (m_max_bound[Z] - m_min_bound[Z]) / m_num_cells[Z]}}),
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
            // Calculate cell dimensions.
            math::Vec<3> cell_size = m_max_bound - m_min_bound;
            cell_size[X] /= m_num_cells[X];
            cell_size[Y] /= m_num_cells[Y];
            cell_size[Z] /= m_num_cells[Z];

            // Create three-dimensional vector of cells.
            std::vector<std::vector<std::vector<Cell>>> r_cell;

            // Create the cells.
            const double total_cells       = m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z];
            double       constructed_cells = 0;

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
                        r_cell[i][j].emplace_back(Cell(math::Vec<3>(
                            {{m_min_bound[X] + (i * cell_size[X]), m_min_bound[Y] + (j * cell_size[Y]), m_min_bound[Z] + (k * cell_size[Z])}}),
                                                       math::Vec<3>(
                                                           {{m_min_bound[X] + ((i + 1) * cell_size[X]), m_min_bound[Y] + ((j + 1) * cell_size[Y]), m_min_bound[Z] + ((k + 1) * cell_size[Z])}}),
                                                       t_entity, t_light));

                        // Report grid construction.
                        TEMP("Constructing grid", 100.0 * (constructed_cells / total_cells));
                        ++constructed_cells;
                    }
                }
            }

            return (r_cell);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Determine the maximum energy density of a single cell within the grid.
         *
         *  @post   r_max_energy_density must be non-negative.
         *
         *  @return The maximum energy density of any cell within the grid.
         */
        double Grid::get_max_energy_density() const
        {
            // Create return value.
            double r_max_energy_density = 0.0;

            // Loop over every cell.
            for (size_t i = 0; i < m_num_cells[X]; ++i)
            {
                for (size_t j = 0; j < m_num_cells[Y]; ++j)
                {
                    for (size_t k = 0; k < m_num_cells[Z]; ++K)
                    {
                        const double energy_density = m_cell[i][j][k].get_energy_density();

                        if (energy_density > r_max_energy_density)
                        {
                            r_max_energy_density = energy_density;
                        }
                    }
                }
            }

            assert(r_max_energy_density >= 0.0);

            return (r_max_energy_density);
        }
    }



} // namespace mesh
} // namespace arc
