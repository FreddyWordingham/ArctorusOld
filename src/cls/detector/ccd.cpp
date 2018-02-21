/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/detector/ccd.hpp"



//  == INCLUDES ==
//  -- System --



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
         *  @param  t_trans Vector of translation.
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *  @param  t_scale Vector of scaling values.
         */
        Ccd::Ccd(const math::Vec<3>& t_trans, const math::Vec<3>& t_dir, const double t_spin, const math::Vec<3>& t_scale) :
            m_mesh("thing", t_trans, t_dir, t_spin, t_scale)
        {
        }


        //  -- Initialisation --



    } // namespace detector
} // namespace arc
