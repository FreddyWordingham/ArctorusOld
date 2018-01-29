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



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Class containing the information about a single vertex.
         */
        class Vertex
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::array<float, 3> m_pos;     //! Vertex position.
            std::array<float, 3> m_norm;    //! Vertex normal.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_VERTEX_HPP
