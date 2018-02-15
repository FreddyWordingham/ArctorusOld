/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   10/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_CONVERSION_HPP
#define ARCTORUS_SRC_UTL_CONVERSION_HPP



//  == INCLUDES ==
//  -- System --
#include <glm/glm.hpp>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        constexpr double rad_to_deg(double t_x);

        //  -- Colour --
        glm::vec3 wavelength_to_rgb(double t_wavelength);
        glm::vec3 colour_chart(double t_x);



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Convert a value in radians to a value in degrees.
         *
         *  @param  t_x Value to convert in units of radians.
         *
         *  @return The value in degrees.
         */
        constexpr double rad_to_deg(const double t_x)
        {
            return (t_x * 180.0 / M_PI);
        }


    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_CONVERSION_HPP
