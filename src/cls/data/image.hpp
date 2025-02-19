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
            Image(size_t t_width, size_t t_height);


            //  == OPERATORS ==
          public:
            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const Image& t_image);


            //  == METHODS ==
          public:
            //  -- Getters --
            size_t get_width() const { return (m_data.size()); }
            size_t get_height() const { return (m_data.front().size()); }
            std::array<double, 3> get_max_value() const;

            //  -- Setters --
            void add_to_pixel(size_t t_row, size_t t_col, const std::array<double, 3>& t_data);

            //  -- Serialisation --
            std::string serialise(double t_norm) const;

            //  -- Saving --
            void save(const std::string& t_path, double t_nor = 1.0) const;
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_IMAGE_HPP
