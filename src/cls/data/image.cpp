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
#include "gen/log.hpp"



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



        //  == METHODS ==
        //  -- Serialisation --
        /**
         *  Create a string representation of the image in ppm format.
         *
         *  @return A string representation of the image.
         */
        std::string Image::serialise() const
        {
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

            // Determine the normalisation value.
            double      max = 0.0;
            for (size_t i   = 0; i < get_width(); ++i)
            {
                for (size_t j = 0; j < get_height(); ++j)
                {
                    for (size_t k = 0; k < 3; ++k)
                    {
                        if (m_data[i][j][k] > max)
                        {
                            max = m_data[i][j][k];
                        }
                    }
                }
            }

            // Normalise and print each pixel.
            if (max > 0.0)
            {
                // Normalise the pixels.
                for (size_t i = 0; i < get_height(); ++i)
                {
                    for (size_t j = 0; j < get_width(); ++j)
                    {
                        for (size_t k = 0; k < 3; ++k)
                        {
                            stream << static_cast<int>(225 * (m_data[j][i][k] / max)) << "\t";
                        }
                        stream << "\t";
                    }
                    stream << "\n";
                }
            }

            return (stream.str());
        }



    } // namespace data
} // namespace arc
