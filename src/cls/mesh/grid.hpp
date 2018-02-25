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
#include "cls/data/image.hpp"
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
            const std::array<double, 3> m_cell_size;    //! Size of each cell.
            const double                m_cell_vol;     //! Volume of each cell.

            //  -- Data --
            std::vector<std::vector<std::vector<Cell>>> m_cell;   //! Three-dimensional vector of cells.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, std::array<size_t, 3> t_num_cells,
                 const std::vector<equip::Entity>& t_entity, const std::vector<equip::Light>& t_light,
                 const std::vector<detector::Ccd>& t_ccd);

          private:
            //  -- Initialisation --
            std::vector<std::vector<std::vector<Cell>>> init_cell(const std::vector<equip::Entity>& t_entity,
                                                                  const std::vector<equip::Light>& t_light,
                                                                  const std::vector<detector::Ccd>& t_ccd) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_min_bound() const { return (m_min_bound); }
            const math::Vec<3>& get_max_bound() const { return (m_max_bound); }
            size_t get_num_cells() const { return (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z]); }
            size_t get_num_cells(const size_t t_dimension) const { return (m_num_cells[t_dimension]); }
            const Cell& get_cell(const size_t t_i, const size_t t_j, const size_t t_k) const { return (m_cell[t_i][t_j][t_k]); }
            inline Cell& get_cell(const math::Vec<3>& t_point);
            double get_max_energy_density() const;

            //  -- Testing --
            inline bool is_within(const math::Vec<3>& t_pos) const;

            //  -- Saving --
            void save_images(const std::string& t_dir) const;
        };



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get a reference to the cell containing the given point.
         *
         *  @param  t_point Point which grid cell must contain.
         *
         *  @pre    t_point must fall within the bounds of the grid.
         *
         *  @post   x index must be a valid cell index.
         *  @post   y index must be a valid cell index.
         *  @post   z index must be a valid cell index.
         *  @post   t_point must fall within the determined cell.
         *
         *  @return A reference to the cell containing the given point.
         */
        Cell& Grid::get_cell(const math::Vec<3>& t_point)
        {
            assert(is_within(t_point));

            // Calculate cell indices.
            const auto x = static_cast<size_t>((t_point[X] - m_min_bound[X]) / m_cell_size[X]);
            const auto y = static_cast<size_t>((t_point[Y] - m_min_bound[Y]) / m_cell_size[Y]);
            const auto z = static_cast<size_t>((t_point[Z] - m_min_bound[Z]) / m_cell_size[Z]);

            assert(x < m_num_cells[X]);
            assert(y < m_num_cells[Y]);
            assert(z < m_num_cells[Z]);
            assert(m_cell[x][y][z].is_within(t_point));

            return (m_cell[x][y][z]);
        }


        //  -- Testing --
        /**
         *  Test if a given position is located within the grid.
         *
         *  @param  t_pos   Position to be tested.
         *
         *  @return True if the position is located within the grid.
         */
        bool Grid::is_within(const math::Vec<3>& t_pos) const
        {
            return ((t_pos[X] >= m_min_bound[X]) && (t_pos[X] <= m_max_bound[X]) && (t_pos[Y] >= m_min_bound[Y]) && (t_pos[Y] <= m_max_bound[Y]) && (t_pos[Z] >= m_min_bound[Z]) && (t_pos[Z] <= m_max_bound[Z]));
        }



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_GRID_HPP
