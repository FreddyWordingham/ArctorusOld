/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == HEADER ==
#include "cls/mesh/cell.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        Cell::Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound)
        {
        }


        //  -- Initialisation --



    } // namespace mesh
} // namespace arc
