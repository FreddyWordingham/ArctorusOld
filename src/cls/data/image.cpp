/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/data/image.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/enum.hpp"
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"



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



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of an image to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_image     Image to be written.
         *
         *  @return A reference to the stream post-write.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Image& t_image)
        {
            // Determine the maximum of the file.
            double      max = 0.0;
            for (size_t i   = 0; i < t_image.get_height(); ++i)
            {
                for (size_t j = 0; j < t_image.get_width(); ++j)
                {
                    for (size_t k = 0; k < 3; ++k)
                    {
                        if (t_image.m_data[i][j][k] > max)
                        {
                            max = t_image.m_data[i][j][k];
                        }
                    }
                }
            }

            t_stream << t_image.serialise(max);

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Determine the maximum rgb pixel value within the data.
         *
         *  @return The maximum rgb pixel values within the image.
         */
        std::array<double, 3> Image::get_max_value() const
        {
            // Create the return array.
            std::array<double, 3> r_max({{0.0, 0.0, 0.0}});

            // Check each pixel for the maximum.
            for (size_t i = 0; i < get_width(); ++i)
            {
                for (size_t j = 0; j < get_height(); ++j)
                {
                    for (size_t k = 0; k < 3; ++k)
                    {
                        if (m_data[i][j][k] > r_max[k])
                        {
                            r_max[k] = m_data[i][j][k];
                        }
                    }
                }
            }

            return (r_max);
        }


        //  -- Setters --
        /**
         *  Add a value to a given pixel.
         *
         *  @param  t_row   Row to add to.
         *  @param  t_col   Column to add to.
         *  @param  t_data  Data array to add.
         *
         *  @pre    t_row must be less than get_width.
         *  @pre    t_col must be less than get_height.
         */
        void Image::add_to_pixel(const size_t t_row, const size_t t_col, const std::array<double, 3>& t_data)
        {
            assert(t_row < get_width());
            assert(t_col < get_height());

            m_data[t_row][t_col][R] += t_data[R];
            m_data[t_row][t_col][G] += t_data[G];
            m_data[t_row][t_col][B] += t_data[B];
        }


        //  -- Serialisation --
        /**
         *  Create a string representation of the image in ppm format.
         *  Data is normalised against a given value.
         *
         *  @param  t_norm  Normalisation value.
         *
         *  @pre    t_norm must be greater than zero.
         *
         *  @return A string representation of the image.
         */
        std::string Image::serialise(const double t_norm) const
        {
            assert(t_norm > 0.0);

            // Check there is data to be written.
            if (m_data.empty())
            {
                WARN("Unable to serialise data::Image.", "No data to form into image.");
            }
            if (m_data.front().empty())
            {
                WARN("Unable to serialise data::Image.", "No data to form into image.");
            }

            // Create a stream to write to.
            std::stringstream stream;

            // Write the file header.
            stream << "P3\n" << get_width() << " " << get_height() << "\n255\n";

            // Normalise and print each pixel.
            for (size_t i = 0; i < get_height(); ++i)
            {
                for (size_t j = 0; j < get_width(); ++j)
                {
                    for (size_t k = 0; k < 3; ++k)
                    {
                        stream << std::min(255, static_cast<int>(225 * (m_data[j][i][k] / t_norm))) << "\t";
                    }
                    stream << "\t";
                }
                stream << "\n";
            }

            return (stream.str());
        }


        //  -- Saving --
        /**
         *  Save the state of the image to a given file path.
         *
         *  @param  t_path  Path to the save location of the file.
         *  @param  t_norm  Normalisation value.
         */
        void Image::save(const std::string& t_path, const double t_norm) const
        {
            file::Handle file(t_path, std::fstream::out, false);

            file << serialise(t_norm);
        }



    } // namespace data
} // namespace arc
