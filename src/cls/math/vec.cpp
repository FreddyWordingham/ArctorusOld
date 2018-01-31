/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/01/2018.
 */



//  == HEADER ==
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == FUNCTIONS ==
        //  -- Geometry --
        /**
         *  Determine the area described by three points.
         *
         *  @param  t_pos   Array of three positional points describing the area.
         *
         *  @return The area described by the three points.
         */
        double area(const std::array<math::Vec<3>, 3>& t_pos)
        {
            const double alpha_beta  = dist(t_pos[ALPHA], t_pos[BETA]);
            const double beta_gamma  = dist(t_pos[BETA], t_pos[GAMMA]);
            const double gamma_alpha = dist(t_pos[GAMMA], t_pos[ALPHA]);

            const double half_perim = (alpha_beta + beta_gamma + gamma_alpha) / 2.0;

            return (std::sqrt(half_perim * (half_perim - alpha_beta) * (half_perim - beta_gamma) * (half_perim - gamma_alpha)));
        }


        /**
         *  Determine the spherical value of rho for the vec.
         *
         *  @post   r_rho must be non-negative.
         *
         *  @return The value of rho in spherical coordinates.
         */
        template <>
        double Vec<3>::get_rho() const
        {
            const double r_rho = std::sqrt((m_data[X] * m_data[X]) + (m_data[Y] * m_data[Y]) + (m_data[Z] * m_data[Z]));

            assert(r_rho >= 0.0);

            return (r_rho);
        }

        /**
         *  Determine the spherical value of theta for the vec.
         *
         *  @post   r_theta must be between zero and pi.
         *
         *  @return The value of theta in spherical coordinates.
         */
        template <>
        double Vec<3>::get_theta() const
        {
            const double r_theta = std::acos(m_data[Z] / get_rho());

            assert((r_theta >= 0.0) && (r_theta <= M_PI));

            return (r_theta);
        }

        /**
         *  Determine the spherical value of phi for the vec.
         *
         *  @post   r_phi must be between -pi and pi.
         *
         *  @return The value of phi in spherical coordinates.
         */
        template <>
        double Vec<3>::get_phi() const
        {
            const double r_phi = std::atan2(m_data[Y], m_data[X]);

            assert((r_phi >= M_PI) && (r_phi <= M_PI));

            return (r_phi);
        }



    } // namespace math
} // namespace arc
