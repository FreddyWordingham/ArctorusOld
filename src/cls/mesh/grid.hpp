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
//  -- System --



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
            const std::array<double, 3> m_min_bound;    //! Minimum bound of the cell.
            const std::array<double, 3> m_max_bound;    //! Maximum bound of the cell.

            //  -- Triangles --
            const std::vector <std::array<size_t, 2>> m_entity_tri; //! List of entity triangles contained within the cell.
            const std::vector <std::array<size_t, 2>> m_light_tri;  //! List of light triangles contained within the cell.


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
#endif // ARCTORUS_SRC_CLS_MESH_GRID_HPP
