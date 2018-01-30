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
            //  -- Transformations --
            void translate(const std::array<float, 3>& t_trans);
            void rotate(const std::array<float, 3>& t_trans);
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
