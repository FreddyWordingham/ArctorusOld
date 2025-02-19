/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



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
            explicit Point(const glm::vec3& t_pos);


            //  == METHODS ==
          public:
            //  -- Getters --
            const glm::vec3& get_pos() const { return (m_pos); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_POINT_HPP



//  == MODULE END ==
#endif
