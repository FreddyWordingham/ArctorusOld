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
        Vertex::Vertex(const glm::vec3& t_pos, const glm::vec3& t_norm) :
            m_pos(t_pos),
            m_norm(t_norm)
        {
        }



        //  == METHODS ==
        //  -- Transformations --
        /**
         *  Apply a translation to the vertex.
         *
         *  @param  t_trans Translations to be applied in each dimension.
         */
        void Vertex::translate(const std::array<float, 3>& t_trans)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                m_pos[static_cast<int>(i)] += t_trans[i];
            }
        }



    } // namespace graphical
} // namespace arc
