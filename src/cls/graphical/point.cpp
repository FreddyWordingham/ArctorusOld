/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/point.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a graphical point at a given position.
         *
         *  @param  t_pos   Three dimensional position of the point.
         */
        Point::Point(const glm::vec3& t_pos) :
            m_pos(t_pos)
        {
        }



    } // namespace graphical
} // namespace arc
