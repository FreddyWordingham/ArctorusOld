/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DETECTOR_CCD_HPP
#define ARCTORUS_SRC_CLS_DETECTOR_CCD_HPP



//  == INCLUDES ==
//  -- Classes --
#include <cls/file/handle.hpp>
#include "cls/data/image.hpp"
#include "cls/geom/mesh.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace detector
    {



        //  == CLASS ==
        /**
         *  CCD like detector.
         *  Rectangular in shape.
         */
        class Ccd
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const std::string  m_name;  //! Name of the ccd.
            const geom::Mesh   m_mesh;  //! Mesh describing the surface of the detector.
            const math::Vec<3> m_norm;  //! Normal direction.

            //  -- Settings --
            const bool m_col;   //! If true save the image as wavelength colours. Otherwise save as greyscale intensity.

            //  -- Data --
            data::Image m_image;        //! Ccd image data.
            //data::Image m_file;         //! CCD file data for benchmarking

            std::vector<math::Vec<3>> m_pos{};
            std::vector<double> m_wavelength{};


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Ccd(const std::string& t_name, size_t t_width, size_t t_height, bool t_col,
                         const math::Vec<3>& t_trans = math::Vec<3>(0.0, 0.0, 0.0),
                         const math::Vec<3>& t_dir = math::Vec<3>(0.0, 0.0, 1.0), double t_spin = 0.0,
                         const math::Vec<3>& t_scale = math::Vec<3>(1.0, 1.0, 1.0));


            //  == METHODS ==
          public:
            //  -- Getters --
            const geom::Mesh& get_mesh() const { return (m_mesh); }
            const math::Vec<3>& get_norm() const { return (m_norm); }
            std::array<double, 3> get_max_value() const { return (m_image.get_max_value()); }

            //  -- Setters --
            void add_hit(const math::Vec<3>& t_pos, double t_weight, double t_wavelength);

            void add_count(const math::Vec<3>& t_pos, const double t_wavelength)
            {
                m_pos.push_back(t_pos);
                m_wavelength.push_back(t_wavelength);
            }

            //  -- Save --
            void save(const std::string& t_output_dir, double t_norm) const;

            void save_pos_data(const std::string& t_path) const
            {
                assert(m_pos.size() == m_wavelength.size());
                //std::cout << m_pos.size() << "," << m_wavelength.size() << std::endl;

                file::Handle file(t_path, std::fstream::out);

                for (size_t i=0; i<m_pos.size(); ++i)
                {
                    file << m_pos[i][0] << "\t" << m_pos[i][1] <<"\t"<< m_wavelength[i] << "\n";
                }
            }
        };

    } // namespace detector
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DETECTOR_CCD_HPP
