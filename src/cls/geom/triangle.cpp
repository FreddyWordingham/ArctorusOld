/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/geom/triangle.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a triangle from a list of given positions and normals.
         *  Triangle normals must be normalised.
         *
         *  @param  t_pos   Vertex positions of the triangle.
         *  @param  t_norm  Vertex normals of the triangle.
         */
        Triangle::Triangle(const std::array<math::Vec<3>, 3>& t_pos, const std::array<math::Vec<3>, 3>& t_norm) :
            m_pos(t_pos),
            m_norm(t_norm),
            m_area(math::area(t_pos))
        {
            for (size_t i = 0; i < 3; ++i)
            {
                assert(t_norm[i].is_normalised());
            }
        }



    } // namespace geom
} // namespace arc
