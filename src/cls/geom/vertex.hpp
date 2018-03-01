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
            const math::Vec<3> m_pos;   //! Position of the vertex.
            const math::Vec<3> m_norm;  //! Normal associated with the vertex. Should always be normalised.
            const math::Vec<3> m_cons;  //! Consistent normal. Used to stop reflection into the surface.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Vertex(const math::Vec<3>& t_pos, const math::Vec<3>& t_norm, const math::Vec<3>& t_plane_norm);


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_pos() const { return (m_pos); }
            const math::Vec<3>& get_norm() const { return (m_norm); }
            const math::Vec<3>& get_cons() const { return (m_cons); }
        };



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_VERTEX_HPP
