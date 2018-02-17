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
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == CLASS ==
        /**
         *  Grid mesh class storing a three-dimensional array of uniform cells.
         */
        class Grid
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_min_bound; //! Minimum bound of the cell.
            const math::Vec<3> m_max_bound; //! Maximum bound of the cell.

            //  -- Data --
            const std::vector<std::vector<std::vector<Cell>>> m_cell;   //! Three-dimensional array of cells.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound);

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_GRID_HPP
