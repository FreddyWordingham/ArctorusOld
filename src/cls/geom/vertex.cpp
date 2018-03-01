/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == HEADER ==
#include "cls/geom/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vertex from a given position and normal.
         *
         *  @param  t_pos           Position of the vertex.
         *  @param  t_norm          Normal direction associated with the vertex.
         *  @param  t_plane_norm    Normal of the plane of the triangle.
         *
         *  @post   m_norm must be normalised.
         *  @post   t_plane_norm must be normalised.
         */
        Vertex::Vertex(const math::Vec<3>& t_pos, const math::Vec<3>& t_norm, const math::Vec<3>& t_plane_norm) :
            m_pos(t_pos),
            m_norm(t_norm)
        {
            assert(t_norm.is_normalised());
        }



    } // namespace geom
} // namespace arc
