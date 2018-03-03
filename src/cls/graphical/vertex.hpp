/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <glm/glm.hpp>



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
            glm::vec3 m_pos;    //! Position of the vertex.
            glm::vec3 m_norm;   //! Normal associated with the vertex.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Vertex(const glm::vec3& t_pos, const glm::vec3& t_norm);


            //  == METHODS ==
          private:
            //  -- Getters --
            glm::vec3 get_pos() const { return (m_pos); }
            glm::vec3 get_norm() const { return (m_norm); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP



//  == MODULE END ==
#endif
