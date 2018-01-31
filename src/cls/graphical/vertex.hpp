/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <glm/vec3.hpp>

//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Class containing the information about a single graphical vertex.
         */
        class Vertex
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            glm::vec3 m_pos;  //! Vertex position.
            glm::vec3 m_norm; //! Vertex normal.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Vertex(const glm::vec3& t_pos, const glm::vec3& t_norm);


            //  == METHODS ==
          public:
            //  -- Getters --
            glm::vec3 get_pos() const { return (m_pos); }
            glm::vec3 get_norm() const { return (m_norm); }

            //  -- Transformations --
            void translate(const math::Vec<3>& t_trans);
            void rotate(const math::Vec<3>& t_rot);
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
