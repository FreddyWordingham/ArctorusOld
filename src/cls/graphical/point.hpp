/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_POINT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_POINT_HPP



//  == INCLUDES ==
//  -- System --
#include <glm/glm.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Graphical point data.
         */
        class Point
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            const glm::vec3 m_pos;  //! Position of the point.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_POINT_HPP
