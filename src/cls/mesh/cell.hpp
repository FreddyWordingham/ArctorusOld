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
            //  -- Lists --
            const std::vector<std::array<size_t, 2>> m_entity_list; //! List of entity triangles with the cell.
            const std::vector<std::array<size_t, 2>> m_light_list;  //! List of light triangles with the cell.


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



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_CELL_HPP
