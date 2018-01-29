/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vertex using a given position and normal.
         *
         *  @param  t_pos   Vertex position.
         *  @param  t_norm  Vertex normal.
         */
        Vertex::Vertex(const std::array<float, 3>& t_pos, const std::array<float, 3>& t_norm) :
            m_pos(t_pos),
            m_norm(t_norm)
        {
        }



    } // namespace graphical
} // namespace arc
