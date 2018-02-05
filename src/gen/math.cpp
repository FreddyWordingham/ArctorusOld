/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   05/02/2018.
 */



//  == HEADER ==
#include "gen/math.hpp"



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


        //  -- Transformation --
        /**
         *  Create a translation transformation matrix.
         *
         *  @param  t_trans Vector of translation.
         *
         *  @return The created translation matrix.
         */
        Mat<4, 4> create_trans_mat(const Vec<3>& t_trans)
        {
            return (Mat<4, 4>(
                {{{{1.0, 0.0, 0.0, t_trans[X]}}, {{0.0, 1.0, 0.0, t_trans[Y]}}, {{0.0, 0.0, 1.0, t_trans[Z]}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }



    } // namespace math
} // namespace arc
