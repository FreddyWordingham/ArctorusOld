/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/vertex.hpp"



//  == INCLUDES ==
//  -- System --
#include <glm/gtx/rotate_vector.hpp>

//  -- General --



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
        void Vertex::translate(const math::Vec<3>& t_trans)
        {
            m_pos.x += t_trans[X];
            m_pos.y += t_trans[Y];
            m_pos.z += t_trans[Z];
        }

        /**
         *  Apply a rotation to the vertex.
         *  Rotations are performed in the order x-axis, y-axis, z-axis.
         *
         *  @param  t_rot   Rotation to be applied in each dimension.
         */
        void Vertex::rotate(const math::Vec<3>& t_rot)
        {
            m_pos = glm::rotateX(m_pos, static_cast<float>(t_rot[X]));
            m_pos = glm::rotateY(m_pos, static_cast<float>(t_rot[Y]));
            m_pos = glm::rotateZ(m_pos, static_cast<float>(t_rot[Z]));

            m_norm = glm::rotateX(m_norm, static_cast<float>(t_rot[X]));
            m_norm = glm::rotateY(m_norm, static_cast<float>(t_rot[Y]));
            m_norm = glm::rotateZ(m_norm, static_cast<float>(t_rot[Z]));
        }



    } // namespace graphical
} // namespace arc
