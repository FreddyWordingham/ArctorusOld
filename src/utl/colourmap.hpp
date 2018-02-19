/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_COLOURMAP_HPP
#define ARCTORUS_SRC_UTL_COLOURMAP_HPP



//  == INCLUDES ==
//  -- System --
#include <glm/glm.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {
        namespace colourmap
        {



            //  == FUNCTION PROTOTYPES ==
            //  -- Maps --
            glm::vec3 transform_rainbow(float t_x);



        } // namespace colourmap
    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_COLOURMAP_HPP
