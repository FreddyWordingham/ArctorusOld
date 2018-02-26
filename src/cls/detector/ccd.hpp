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
            data::Image m_image;    //! Ccd image data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Ccd(const std::string& t_name, size_t t_width, size_t t_height, bool t_col,
                         const math::Vec<3>& t_trans = math::Vec<3>({{0.0, 0.0, 0.0}}),
                         const math::Vec<3>& t_dir = math::Vec<3>({{0.0, 0.0, 1.0}}), double t_spin = 0.0,
                         const math::Vec<3>& t_scale = math::Vec<3>({{1.0, 1.0, 1.0}}));


            //  == METHODS ==
          public:
            //  -- Getters --
            const geom::Mesh& get_mesh() const { return (m_mesh); }
            const math::Vec<3>& get_norm() const { return (m_norm); }
            std::array<double, 3> get_max_value() const { return (m_image.get_max_value()); }

            //  -- Setters --
            void add_hit(const math::Vec<3>& t_pos, double t_weight, double t_wavelength);

            //  -- Save --
            void save(double t_norm) const;
        };



    } // namespace detector
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DETECTOR_CCD_HPP
