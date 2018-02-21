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
            const geom::Mesh m_mesh;    //! Mesh describing the surface of the detector.

            //  -- Data --
            data::Image m_image;    //! Ccd image data.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Ccd(const math::Vec<3>& t_trans = math::Vec<3>({{0.0, 0.0, 0.0}}),
                         const math::Vec<3>& t_dir = math::Vec<3>({{0.0, 0.0, 1.0}}), double t_spin = 0.0,
                         const math::Vec<3>& t_scale = math::Vec<3>({{1.0, 1.0, 1.0}}));


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace detector
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DETECTOR_CCD_HPP
