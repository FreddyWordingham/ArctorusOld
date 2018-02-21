/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == HEADER ==
#include "utl/colourmap.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {
        namespace colourmap
        {



            //  == FUNCTIONS ==
            //  -- Maps --
            /**
             *  Create a rainbow colour mapping for a value between zero and unity.
             *
             *  @param  t_x Value to be mapped.
             *
             *  @return The colour mapping of the value.
             */
            std::array<double, 3> transform_rainbow(const double t_x)
            {
                // Check for value out of range.
                if ((t_x < 0.0) || (t_x > 1.0))
                {
                    return (std::array<double, 3>({{1.0, 0.0, 1.0}}));
                }

                assert((t_x >= 0.0) && (t_x <= 1.0));

                // Calculate the red component.
                double red = 0.0;
                if (t_x < 0.0)
                {
                    red = 127.0 / 255.0;
                }
                else if (t_x <= 1.0 / 9.0)
                {
                    red = 1147.5 * (1.0 / 9.0 - t_x) / 255.0;
                }
                else if (t_x <= 5.0 / 9.0)
                {
                    red = 0.0;
                }
                else if (t_x <= 7.0 / 9.0)
                {
                    red = 1147.5 * (t_x - 5.0 / 9.0) / 255.0;
                }
                else
                {
                    red = 1.0;
                }

                // Calculate the green component.
                double green = 0.0;
                if (t_x <= 1.0 / 9.0)
                {
                    green = 0.0;
                }
                else if (t_x <= 3.0 / 9.0)
                {
                    green = 1147.5 * (t_x - 1.0 / 9.0) / 255.0;
                }
                else if (t_x <= 7.0 / 9.0)
                {
                    green = 1.0;
                }
                else if (t_x <= 1.0)
                {
                    green = 1.0 - 1147.5 * (t_x - 7.0 / 9.0) / 255.0;
                }
                else
                {
                    green = 0.0;
                }

                // Calculate the blue component.
                double blue = 0.0;
                if (t_x <= 3.0 / 9.0)
                {
                    blue = 1.0;
                }
                else if (t_x <= 5.0 / 9.0)
                {
                    blue = 1.0 - 1147.5 * (t_x - 3.0 / 9.0) / 255.0;
                }
                else
                {
                    blue = 0.0;
                }

                return (std::array<double, 3>({{red, green, blue}}));
            }



        } // namespace colourmap
    } // namespace utl
} // namespace arc
