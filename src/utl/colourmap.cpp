/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == HEADER ==
#include "utl/colourmap.hpp"



//  == INCLUDES ==
//  -- System --
#include <cassert>



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
             *  @post   r_red must be between zero and unity.
             *  @post   r_green must be between zero and unity.
             *  @post   r_blue must be between zero and unity.
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
                double r_red;
                if (t_x < 0.0)
                {
                    r_red = 127.0 / 255.0;
                }
                else if (t_x <= 1.0 / 9.0)
                {
                    r_red = 1147.5 * (1.0 / 9.0 - t_x) / 255.0;
                }
                else if (t_x <= 5.0 / 9.0)
                {
                    r_red = 0.0;
                }
                else if (t_x <= 7.0 / 9.0)
                {
                    r_red = 1147.5 * (t_x - 5.0 / 9.0) / 255.0;
                }
                else
                {
                    r_red = 1.0;
                }

                // Calculate the green component.
                double r_green;
                if (t_x <= 1.0 / 9.0)
                {
                    r_green = 0.0;
                }
                else if (t_x <= 3.0 / 9.0)
                {
                    r_green = 1147.5 * (t_x - 1.0 / 9.0) / 255.0;
                }
                else if (t_x <= 7.0 / 9.0)
                {
                    r_green = 1.0;
                }
                else if (t_x <= 1.0)
                {
                    r_green = 1.0 - 1147.5 * (t_x - 7.0 / 9.0) / 255.0;
                }
                else
                {
                    r_green = 0.0;
                }

                // Calculate the blue component.
                double r_blue;
                if (t_x <= 3.0 / 9.0)
                {
                    r_blue = 1.0;
                }
                else if (t_x <= 5.0 / 9.0)
                {
                    r_blue = 1.0 - 1147.5 * (t_x - 3.0 / 9.0) / 255.0;
                }
                else
                {
                    r_blue = 0.0;
                }

                assert((r_red >= 0.0) && (r_red <= 1.0));
                assert((r_green >= 0.0) && (r_green <= 1.0));
                assert((r_blue >= 0.0) && (r_blue <= 1.0));

                return (std::array<double, 3>({{r_red, r_green, r_blue}}));
            }



        } // namespace colourmap
    } // namespace utl
} // namespace arc
