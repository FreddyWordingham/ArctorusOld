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



        //  == FUNCTIONS ==
        //  -- Maps --
        /**
         *  Create a rainbow colour mapping for a value between zero and unity.
         *
         *  @param  t_x Value to be mapped.
         *
         *  @pre    t_x must be between zero and one.
         *
         *  @return The colour mapping of the value.
         */
        glm::vec3 transform_rainbow(const float t_x)
        {
            assert((t_x >= 0.0f) && (t_x <= 1.0f));

            // Calculate the red component.
            float red = 0.0f;
            if (t_x < 0.0f) {
                red = 127.0f / 255.0f;
            } else if (t_x <= 1.0f / 9.0f) {
                red = 1147.5f * (1.0f / 9.0f - t_x) / 255.0f;
            } else if (t_x <= 5.0 / 9.0) {
                red = 0.0;
            } else if (t_x <= 7.0 / 9.0) {
                red = 1147.5f * (t_x - 5.0f / 9.0f) / 255.0f;
            } else {
                red = 1.0;
            }

            // Calculate the green component.
            float green = 0.0f;
            if (t_x <= 1.0f / 9.0f) {
                green = 0.0f;
            } else if (t_x <= 3.0f / 9.0f) {
                green = 1147.5f * (t_x - 1.0f / 9.0f) / 255.0f;
            } else if (t_x <= 7.0f / 9.0f) {
                green = 1.0f;
            } else if (t_x <= 1.0f) {
                green = 1.0f - 1147.5f * (t_x - 7.0f / 9.0f) / 255.0f;
            } else {
                green = 0.0f;
            }

            // Calculate the blue component.
            float blue = 0.0f;
            if (t_x <= 3.0f / 9.0f) {
                blue = 1.0f;
            } else if (t_x <= 5.0f / 9.0f) {
                blue = 1.0f - 1147.5f * (t_x - 3.0f / 9.0f) / 255.0f;
            } else {
                blue = 0.0f;
            }

            return glm::vec3(red, green, blue);
        }



    } // namespace utl
} // namespace arc
