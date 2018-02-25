/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/detector/ccd.hpp"



//  == INCLUDES ==
//  -- General --

//  -- Utility --
#include "utl/colourmap.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace detector
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a ccd detector with a given number of pixels and a given transformation from a base square mesh.
         *
         *  @param  t_name      Name of the ccd camera.
         *  @param  t_width     Width of the ccd in pixels.
         *  @param  t_height    Height of the ccd in pixels.
         *  @param  t_col       If true, save a coloured image.
         *  @param  t_trans     Vector of translation.
         *  @param  t_dir       Direction to face.
         *  @param  t_spin      Spin angle.
         *  @param  t_scale     Vector of scaling values.
         */
        Ccd::Ccd(const std::string& t_name, const size_t t_width, const size_t t_height, const bool t_col,
                 const math::Vec<3>& t_trans, const math::Vec<3>& t_dir, const double t_spin, const math::Vec<3>& t_scale) :
            m_name(t_name),
            m_mesh(file::read(std::string(config::ARCTORUS_DIR) + "res/meshes/square.obj"), t_trans, t_dir, t_spin, t_scale),
            m_norm(t_dir),
            m_col(t_col),
            m_image(t_width, t_height)
        {
        }



        //  == METHODS ==
        //  -- Setters --
        void Ccd::add_hit(const math::Vec<3>& t_pos, const double t_weight, const double t_wavelength)
        {
            const math::Vec<3> alpha = m_mesh.get_tri(1).get_vert(1).get_pos();
            const math::Vec<3> beta  = m_mesh.get_tri(1).get_vert(2).get_pos();
            const math::Vec<3> gamma = m_mesh.get_tri(1).get_vert(0).get_pos();

            const double theta = std::acos(
                ((t_pos - alpha) * (gamma - alpha)) / ((t_pos - alpha).magnitude() * (gamma - alpha).magnitude()));

            assert(theta <= (M_PI / 2.0));

            const double h = (t_pos - alpha).magnitude();
            const double x = (h * std::cos(theta)) / (beta - alpha).magnitude();
            const double y = (h * std::sin(theta)) / (gamma - alpha).magnitude();

            assert ((x >= 0.0) && (x <= 1.0));
            assert ((y >= 0.0) && (y <= 1.0));

            const auto pix_x = static_cast<size_t>(x * m_image.get_width());
            const auto pix_y = static_cast<size_t>(y * m_image.get_height());

            const std::array<double, 3> col = m_col ? utl::colourmap::transform_rainbow((t_wavelength - 400E-9) / 300E-9)
                                                    : std::array<double, 3>({{1.0, 1.0, 1.0}});

            m_image.add_to_pixel(pix_x, pix_y, {{t_weight * col[R], t_weight * col[G], t_weight * col[B]}});
        }


        //  -- Save --
        /**
         *  Save the state of the image.
         *
         *  @param  t_norm  Normalisation value.
         */
        void Ccd::save(double t_norm) const
        {
            m_image.save(m_name + ".ppm", t_norm);
        }



    } // namespace detector
} // namespace arc
