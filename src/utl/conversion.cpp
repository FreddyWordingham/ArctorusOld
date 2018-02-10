/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   10/02/2018.
 */



//  == HEADER ==
#include "utl/conversion.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTIONS ==
        //  -- Colour --
        /**
         *  Convert a given wavelength to an rgb colour vector.
         *
         *  @param  t_wavelength    Wavelength to convert.
         *
         *  @pre    t_wavelength must be greater than zero.
         *
         *  @return The rgb colour vector.
         */
        glm::vec3 wavelength_to_rgb(const double t_wavelength)
        {
            assert(t_wavelength > 0.0);

            return (glm::vec3(1.0, 0.0, 1.0));
        }


    } // namespace utl
} // namespace arc
