/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
#define ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP



//  == INCLUDES ==
//  -- System --

//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Triangle class used to form triangular meshes.
         */
        class Triangle
        {
            //  == FIELDS ==
          private:
            //  -- Vertices --
            const std::array<math::Vec<3>, 3> m_pos;    //! Vertex positions.
            const std::array<math::Vec<3>, 3> m_norm;   //! Vertex normals.

            //  -- Data --
            const double m_area;    //! Area of the triangle.


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



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
