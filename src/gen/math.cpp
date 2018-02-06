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

        /**
         *  Create an orientation transformation matrix.
         *
         *  @param  t_theta Angle to rotate around the global  y-axis.
         *  @param  t_phi   Angle to then rotate around  the global z-axis.
         *  @param  t_spin  Angle to then rotate around the local z-axis.
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
         *  @return The created orientation matrix.
         */
        Mat<4, 4> create_orient_mat(const Vec<3>& t_dir, const double t_spin)
        {
            return (create_orient_mat(
                acos(t_dir[Z] / std::sqrt(math::square(t_dir[X]) + math::square(t_dir[Y]) + math::square(t_dir[Z]))),
                atan2(t_dir[Y], t_dir[X]), t_spin));
        }

        /**
         *  Create a position scaling transformation matrix.
         *
         *  @param  t_scale Vector of scaling values.
         *
         *  @return The created position scaling matrix.
         */
        Mat<4, 4> create_scale_pos_mat(const Vec<3>& t_scale)
        {
            return (Mat<4, 4>(
                {{{{t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }

        /**
         *  Create a direction scaling transformation matrix.
         *
         *  @param  t_scale Vector of scaling values.
         *
         *  @return The created direction scaling matrix.
         */
        Mat<4, 4> create_scale_dir_mat(const Vec<3>& t_scale)
        {
            return (Mat<4, 4>(
                {{{{1.0/t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, 1.0/t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, 1.0/t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }

        /**
         *  Create position transformation matrix from individual transformations.
         *
         *  @param  t_trans Vector of translation.
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *  @param  t_scale Vector of scaling values.
         *
         *  @return The created position transformation matrix.
         */
        Mat<4, 4> create_pos_mat(const Vec<3>& t_trans, const Vec<3>& t_dir, double t_spin, const Vec<3>& t_scale)
        {
            return (create_scale_pos_mat(t_scale) * create_orient_mat(t_dir, t_spin) * create_trans_mat(t_trans));
        }

        /**
         *  Create direction transformation matrix from individual transformations.
         *
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *  @param  t_scale Vector of scaling values.
         *
         *  @return The created direction transformation matrix.
         */
        Mat<4, 4> create_dir_mat(const Vec<3>& t_dir, double t_spin, const Vec<3>& t_scale)
        {
            return (create_scale_dir_mat(t_scale) * create_orient_mat(t_dir, t_spin));
        }



    } // namespace math
} // namespace arc
