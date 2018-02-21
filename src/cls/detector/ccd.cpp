/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/detector/ccd.hpp"



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
         *  @param  t_width     Width of the ccd in pixels.
         *  @param  t_height    Height of the ccd in pixels.
         *  @param  t_trans     Vector of translation.
         *  @param  t_dir       Direction to face.
         *  @param  t_spin      Spin angle.
         *  @param  t_scale     Vector of scaling values.
         */
        Ccd::Ccd(const size_t t_width, const size_t t_height, const math::Vec<3>& t_trans, const math::Vec<3>& t_dir,
                 const double t_spin, const math::Vec<3>& t_scale) :
            m_mesh(
                "v 1.000000 1.000000 0.000000\nv -1.000000 1.000000 0.000000\nv 1.000000 -1.000000 0.000000\nv -1.000000 -1.000000 0.000000\nvn 0.0000 0.0000 1.0000\ns off\nf 2//1 3//1 1//1\nf 2//1 4//1 3//1",
                t_trans, t_dir, t_spin, t_scale),
            m_image(t_width, t_height)
        {
        }



        //  == METHODS ==
        //  -- Setters --
        void Ccd::add_hit(const math::Vec<3>& t_pos, const double t_weight)
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

            const size_t pix_x = static_cast<size_t>(x * m_image.get_width());
            const size_t pix_y = static_cast<size_t>(y * m_image.get_height());

            m_image.add_to_pixel(pix_x, pix_y, {{t_weight, t_weight, t_weight}});
        }


        //  -- Save --
        /**
         *  Save the state of the image to a given file path.
         *
         *  @param  t_path  Path to the save location of the file.
         *  @param  t_norm  Normalisation value.
         */
        void Ccd::save(const std::string& t_path, double t_norm) const
        {
            m_image.save(t_path, t_norm);
        }



    } // namespace detector
} // namespace arc
