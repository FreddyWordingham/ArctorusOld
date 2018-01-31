/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_VERTEX_HPP
#define ARCTORUS_SRC_CLS_GEOM_VERTEX_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Vertices are the base of all geometry.
         *  Always three dimensional.
         */
        class Vertex
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            math::Vec<3> m_pos;     //! Position of the vertex.
            math::Vec<3> m_norm;    //! Normal associated with the vertex. Should always be normalised.


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
#endif // ARCTORUS_SRC_CLS_GEOM_VERTEX_HPP
