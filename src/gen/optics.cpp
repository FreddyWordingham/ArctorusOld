/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   20/02/2018.
 */



//  == HEADER ==
#include "gen/optics.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace optics
    {



        //  == FUNCTIONS ==
        //  -- Boundary --
        /**
         *  Determine the reflection direction of an incoming ray on a surface with a given normal.
         *
         *  @param  t_in    Incoming direction vector.
         *  @param  t_norm  Normal of the plane.
         *
         *  @pre    t_in must be normalised.
         *  @pre    t_norm must be normalised.
         *  @pre    Angle between t_in and t_norm must be less than pi/2.0.
         *
         *  @post   r_out must be normalised.
         *
         *  @return The reflected direction vector.
         */
        math::Vec<3> reflection_dir(const math::Vec<3>& t_in, const math::Vec<3>& t_norm)
        {
            assert(t_in.is_normalised());
            assert(t_norm.is_normalised());
            assert(std::acos(t_in * t_norm) < (M_PI / 2.0));

            const math::Vec<3> r_out = t_in + (t_norm * (2.0 * (t_in * t_norm)));

            assert(r_out.is_normalised());

            return (r_out);
        }



    } // namespace optics
} // namespace arc
