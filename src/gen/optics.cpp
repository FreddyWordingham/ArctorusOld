/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   20/02/2018.
 */



//  == HEADER ==
#include "gen/optics.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"



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
            assert((t_in * t_norm) < 0.0);

            const math::Vec<3> r_out = math::normalise(t_in - (t_norm * (2.0 * (t_in * t_norm))));

            assert(r_out.is_normalised());

            return (r_out);
        }

        /**
         *  Determine the refraction direction of an incoming ray on a surface with a given normal and refractive index ratio.
         *  Refractive index ratio = n_1 / n_2.
         *
         *  @param  t_in    Incoming direction vector.
         *  @param  t_norm  Normal of the plane.
         *  @param  t_n     Ratio of refractive indices across the boundary.
         *
         *  @pre    t_in must be normalised.
         *  @pre    t_norm must be normalised.
         *  @pre    Angle between t_in and t_norm must be less than pi/2.0.
         *
         *  @post   r_out must be normalised.
         *
         *  @return The reflected direction vector.
         */
        math::Vec<3> refraction_dir(const math::Vec<3>& t_in, const math::Vec<3>& t_norm, const double t_n)
        {
            assert(t_in.is_normalised());
            assert(t_norm.is_normalised());
            assert((t_in * t_norm) < 0.0);

            const double       cos_a_i    = -(t_in * t_norm);
            const double       sin_a_t_sq = math::square(t_n) * (1.0 - math::square(cos_a_i));
            const math::Vec<3> r_out      = (t_in * t_n) + (t_norm * ((t_n * cos_a_i) - std::sqrt(1.0 - sin_a_t_sq)));

            assert(r_out.is_normalised());

            return (r_out);
        }

        /**
         *  Determine the reflection probability for the given incident angle over a boundary with given refractive indices.
         *
         *  @param  t_a_i   Incident angle.
         *  @param  t_n_i   Refractive index of incident material.
         *  @param  t_n_t   Refractive index of transmission material.
         *
         *  @pre    a_i must be between zero and pi/2.0.
         *  @pre    n_i must be greater than, or equal to, one.
         *  @pre    n_t must be greater than, or equal to, one.
         *
         *  @post   r_ref_prob must be between zero and one.
         *
         *  @return The probability of reflection.
         */
        double reflection_prob(const double t_a_i, const double t_n_i, const double t_n_t)
        {
            assert((t_a_i >= 0.0) && (t_a_i < (M_PI / 2.0)));
            assert(t_n_i >= 1.0);
            assert(t_n_t >= 1.0);

            // Calculate transverse reflection probability.
            const double cos_a_i = std::cos(t_a_i);
            const double cos_a_t = std::cos((t_n_i / t_n_t) * std::sin(t_a_i));
            const double trans   = math::square(
                ((t_n_t * cos_a_i) - (t_n_i * cos_a_t)) / ((t_n_t * cos_a_i) + (t_n_i * cos_a_t)));
            const double paral   = math::square(
                ((t_n_t * cos_a_i) - (t_n_i * cos_a_t)) / ((t_n_t * cos_a_i) + (t_n_i * cos_a_t)));

            // Determine average reflection probability.
            const double r_ref_prob = 0.5 * (trans + paral);

            assert((r_ref_prob >= 0.0) && (r_ref_prob <= 1.0));

            return (r_ref_prob);
        }



    } // namespace optics
} // namespace arc
