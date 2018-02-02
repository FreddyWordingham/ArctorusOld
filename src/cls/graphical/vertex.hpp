/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP



//  == INCLUDES ==
//  -- System --



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


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
