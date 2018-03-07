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
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
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

            //  -- Depth Data --
            const unsigned int m_depth; //! Depth of the cell within the tree.
            const bool         m_leaf;  //! True if the cell is a terminal cell.

            //  -- Children --
            const std::array<std::shared_ptr<Cell>, 8> m_child; //! Array of child cell pointers.

            //  -- Equipment References --
            const std::vector<equip::Entity>         & m_entity;        //! Reference to vector of sim entities.
            const std::vector<equip::Light>          & m_light;         //! Reference to vector of sim lights.
            const std::vector<detector::Ccd>         & m_ccd;           //! Reference to vector of sim ccds.
            const std::vector<detector::Spectrometer>& m_spectrometer;  //! Reference to vector of sim spectrometers.

            //  -- Lists --
            const std::vector<std::array<size_t, 2>> m_entity_tri_list; //! List of entity triangles inside cell.
            const std::vector<std::array<size_t, 2>> m_light_tri_list;  //! List of light triangles inside cell.


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
