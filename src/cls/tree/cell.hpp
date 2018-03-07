/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/03/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_TREE_CELL_HPP
#define ARCTORUS_SRC_CLS_TREE_CELL_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace tree
    {



        //  == CLASS ==
        /**
         *  Adaptive regular mesh tree forming octal cuboid cells.
         */
        class Cell
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_center;        //! Center of the cell.
            const math::Vec<3> m_half_width;    //! Half width of the cell.

            //  -- Cell Data --
            const unsigned int m_depth; //! Depth of the cell within the tree.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace tree
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_TREE_CELL_HPP
