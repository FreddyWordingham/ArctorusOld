/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   20/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_OPTICS_HPP
#define ARCTORUS_SRC_GEN_OPTICS_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace optics
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Boundary --
        math::Vec<3> reflection_dir(const math::Vec<3>& t_in, const math::Vec<3>& t_norm);



    } // namespace optics
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_OPTICS_HPP
