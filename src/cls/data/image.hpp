/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DATA_IMAGE_HPP
#define ARCTORUS_SRC_CLS_DATA_IMAGE_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == CLASS ==
        /**
         *  Image data writer.
         */
        class Image
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::vector<std::vector<std::array<double, 3>>> m_data; //! Pixel data of the image.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Image(const size_t t_width, const size_t t_height);

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_IMAGE_HPP
