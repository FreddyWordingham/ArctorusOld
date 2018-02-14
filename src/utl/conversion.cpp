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

            // Calculate base rgb component.
            double red, green, blue;
            if ((t_wavelength >= 380E-9) && (t_wavelength < 440E-9))
            {
                red   = -(t_wavelength - 440E-9) / (440E-9 - 380E-9);
                green = 0.0;
                blue  = 1.0;
            }
            else if ((t_wavelength >= 440E-9) && (t_wavelength < 490E-9))
            {
                red   = 0.0;
                green = (t_wavelength - 440E-9) / (490E-9 - 440E-9);
                blue  = 1.0;
            }
            else if ((t_wavelength >= 490E-9) && (t_wavelength < 510E-9))
            {
                red   = 0.0;
                green = 1.0;
                blue  = -(t_wavelength - 510E-9) / (510E-9 - 490E-9);
            }
            else if ((t_wavelength >= 510E-9) && (t_wavelength < 580E-9))
            {
                red   = (t_wavelength - 510E-9) / (580E-9 - 510E-9);
                green = 1.0;
                blue  = 0.0;
            }
            else if ((t_wavelength >= 580E-9) && (t_wavelength < 645E-9))
            {
                red   = 1.0;
                green = -(t_wavelength - 645E-9) / (645E-9 - 580E-9);
                blue  = 0.0;
            }
            else if ((t_wavelength >= 645E-9) && (t_wavelength < 781E-9))
            {
                red   = 1.0;
                green = 0.0;
                blue  = 0.0;
            }
            else
            {
                red   = 1.0;
                green = 0.0;
                blue  = 1.0;
            };

            // Decrease intensity near vision limits.
            double factor;
            if ((t_wavelength >= 380E-9) && (t_wavelength < 420E-9))
            {
                factor = 0.3 + 0.7 * (t_wavelength - 380E-9) / (420E-9 - 380E-9);
            }
            else if ((t_wavelength >= 420E-9) && (t_wavelength < 701E-9))
            {
                factor = 1.0;
            }
            else if ((t_wavelength >= 701E-9) && (t_wavelength < 781E-9))
            {
                factor = 0.3 + 0.7 * (780E-9 - t_wavelength) / (780E-9 - 700E-9);
            }
            else
            {
                factor = 0.0;
            };

            // Gamma correction.
            double gamma = 0.8;
            red   = std::pow(red * factor, gamma);
            green = std::pow(green * factor, gamma);
            blue  = std::pow(blue * factor, gamma);

            return (glm::vec3(red, green, blue));
        }

        glm::vec3 colour_chart(const double t_x)
        {
            assert(t_x >= 0.0);
            assert(t_x <= 1.0);

            double red, green, blue;
            if (t_x <= (2.0 / 12.0))
            {
                red   = 1.0;
                green = 0.0;
                blue  = 1.0 - (t_x / (2.0 / 12.0));
            }
            else if ((t_x > (2.0 / 12.0)) && (t_x <= (4.0 / 12.0)))
            {
                red   = 1.0;
                green = (t_x - (2.0 / 12.0)) / (2.0 / 12.0);
                blue  = 0.0;
            }
            else if ((t_x > (4.0 / 12.0)) && (t_x <= (6.0 / 12.0)))
            {
                red   = 1.0 - (t_x - (4.0 / 12.0)) / (2.0 / 12.0);
                green = 1.0;
                blue  = 0.0;
            }
            else if ((t_x > (6.0 / 12.0)) && (t_x <= (8.0 / 12.0)))
            {
                red   = 0.0;
                green = 1.0;
                blue  = (t_x - (6.0 / 12.0)) / (2.0 / 12.0);
            }
            else if ((t_x > (8.0 / 12.0)) && (t_x <= (10.0 / 12.0)))
            {
                red   = 0.0;
                green = 1.0 - (t_x - (8.0 / 12.0)) / (2.0 / 12.0);
                blue  = 1.0;
            }
            else
            {
                red   = (t_x - (10.0 / 12.0)) / (2.0 / 12.0);
                green = 0.0;
                blue  = 1.0;
            }

            return (glm::vec3(red, green, blue));
        }



    } // namespace utl
} // namespace arc
