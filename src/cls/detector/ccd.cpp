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



    } // namespace detector
} // namespace arc
