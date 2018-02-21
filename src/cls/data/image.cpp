/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/data/image.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct an image with a given width and height.
         *
         *  @param  t_width     Width of the image.
         *  @param  t_height    Height of the image.
         */
        Image::Image(const size_t t_width, const size_t t_height) :
            m_data(std::vector<std::vector<std::array<double, 3>>>(t_width, std::vector<std::array<double, 3>>(t_height)))
        {
        }


        //  -- Initialisation --



    } // namespace data
} // namespace arc
