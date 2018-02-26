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
        double area(const std::array<Vec<3>, 3>& t_pos)
        {
            // Calculate the edge lengths.
            const double alpha_beta  = dist(t_pos[ALPHA], t_pos[BETA]);
            const double beta_gamma  = dist(t_pos[BETA], t_pos[GAMMA]);
            const double gamma_alpha = dist(t_pos[GAMMA], t_pos[ALPHA]);

            // Calculate the half perimeter.
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

        /**
         *  Create an orientation transformation matrix.
         *  Rotate the object around the global z-axis by the spin.
         *  Then rotate the object around the global y-axis by the theta angle.
         *  Then rotate the object around the global z-axis by the phi angle.
         *
         *  @param  t_theta Angle to rotate around the global  y-axis.
         *  @param  t_phi   Angle to then rotate around  the global z-axis.
         *  @param  t_spin  Angle to initially rotate around the global z-axis.
         *
         *  @return The created orientation matrix.
         */
        Mat<4, 4> create_orient_mat(const double t_theta, const double t_phi, const double t_spin)
        {
            return (Mat<4, 4>({{{{std::cos(t_phi), sin(t_phi), 0.0, 0.0}}, {{-std::sin(t_phi), cos(
                t_phi), 0.0, 0.0}}, {{0.0, 0.0, 1.0, 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}) * Mat<4, 4>(
                {{{{std::cos(t_theta), 0.0, -std::sin(t_theta), 0.0}}, {{0.0, 1.0, 0.0, 0.0}}, {{std::sin(
                    t_theta), 0.0, std::cos(t_theta), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}) * Mat<4, 4>(
                {{{{std::cos(t_spin), std::sin(t_spin), 0.0, 0.0}}, {{-std::sin(t_spin), std::cos(
                    t_spin), 0.0, 0.0}}, {{0.0, 0.0, 1.0, 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }

        /**
         *  Create an orientation transformation matrix.
         *
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *
         *  @pre    t_dir's magnitude must be greater than zero.
         *
         *  @return The created orientation matrix.
         */
        Mat<4, 4> create_orient_mat(const Vec<3>& t_dir, const double t_spin)
        {
            assert(t_dir.magnitude() > 0.0);

            return (create_orient_mat(acos(t_dir[Z] / std::sqrt(square(t_dir[X]) + square(t_dir[Y]) + square(t_dir[Z]))),
                                      atan2(t_dir[Y], t_dir[X]), t_spin));
        }

        /**
         *  Create a scaling transformation matrix.
         *
         *  @param  t_scale Vector of scaling values.
         *
         *  @pre    t_scale elements must all be non-zero.
         *
         *  @return The created position scaling matrix.
         */
        Mat<4, 4> create_scale_mat(const Vec<3>& t_scale)
        {
            assert(t_scale[X] != 0.0);
            assert(t_scale[Y] != 0.0);
            assert(t_scale[Z] != 0.0);

            return (Mat<4, 4>(
                {{{{t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }

        /**
         *  Create position transformation matrix from individual transformations.
         *
         *  @param  t_trans Vector of translation.
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *  @param  t_scale Vector of scaling values.
         *
         *  @pre    t_dir's magnitude must be greater than zero.
         *  @pre    t_scale elements must all be non-zero.
         *
         *  @return The created position transformation matrix.
         */
        Mat<4, 4> create_trans_mat(const Vec<3>& t_trans, const Vec<3>& t_dir, double t_spin, const Vec<3>& t_scale)
        {
            assert(t_dir.magnitude() > 0.0);
            assert(t_scale[X] != 0.0);
            assert(t_scale[Y] != 0.0);
            assert(t_scale[Z] != 0.0);

            return (create_trans_mat(t_trans) * create_orient_mat(t_dir, t_spin) * create_scale_mat(t_scale));
        }



    } // namespace math
} // namespace arc
