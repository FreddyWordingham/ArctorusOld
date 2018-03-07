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

        /**
         *  Determine if an axis-aligned bounding box is intersecting with a triangle.
         *  Box and triangle are considered to be overlapping even if the triangle is in the plane of the box.
         *
         *  @param  t_center    Center of the box.
         *  @param  t_half_size Half-size of the box.
         *  @param  t_tri       Triangle to test intersection with.
         *
         *  @return True if the box and triangle are intersecting.
         */
        bool tri_overlap(const math::Vec<3>& t_center, const math::Vec<3>& t_half_size, const geom::Triangle& t_tri) const
        {
            // Translate everything so the box center is at the origin.
            const math::Vec<3> v0 = t_tri.get_pos(0) - t_center;
            const math::Vec<3> v1 = t_tri.get_pos(1) - t_center;
            const math::Vec<3> v2 = t_tri.get_pos(2) - t_center;

            // Compute triangle edges.
            const math::Vec<3> e0 = v1 - v0;
            const math::Vec<3> e1 = v2 - v1;
            const math::Vec<3> e2 = v0 - v2;

            double p0, p2, rad;

            p0  = (e0[Z] * v0[Y]) - (e0[Y] * v0[Z]);
            p2  = (e0[Z] * v2[Y]) - (e0[Y] * v2[Z]);
            rad = (std::fabs(e0[Z]) * t_half_size[Y]) + (std::fabs(e0[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e0[Z] * v0[X]) + (e0[X] * v0[Z]);
            p2  = (-e0[Z] * v2[X]) + (e0[X] * v2[Z]);
            rad = (std::fabs(e0[Z]) * t_half_size[X]) + (std::fabs(e0[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e0[Y] * v1[X]) - (e0[X] * v1[Y]);
            p2  = (e0[Y] * v2[X]) - (e0[X] * v2[Y]);
            rad = (std::fabs(e0[Y]) * t_half_size[X]) + (std::fabs(e0[X]) * t_half_size[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Z] * v0[Y]) - (e1[Y] * v0[Z]);
            p2  = (e1[Z] * v2[Y]) - (e1[Y] * v2[Z]);
            rad = (std::fabs(e1[Z]) * t_half_size[Y]) + (std::fabs(e1[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e1[Z] * v0[X]) + (e1[X] * v0[Z]);
            p2  = (-e1[Z] * v2[X]) + (e1[X] * v2[Z]);
            rad = (std::fabs(e1[Z]) * t_half_size[X]) + (std::fabs(e1[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e1[Y] * v0[X]) - (e1[X] * v0[Y]);
            p2  = (e1[Y] * v1[X]) - (e1[X] * v1[Y]);
            rad = (std::fabs(e1[Y]) * t_half_size[X]) + (std::fabs(e1[X]) * t_half_size[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Z] * v0[Y]) - (e2[Y] * v0[Z]);
            p2  = (e2[Z] * v1[Y]) - (e2[Y] * v1[Z]);
            rad = (std::fabs(e2[Z]) * t_half_size[Y]) + (std::fabs(e2[Y]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (-e2[Z] * v0[X]) + (e2[X] * v0[Z]);
            p2  = (-e2[Z] * v1[X]) + (e2[X] * v1[Z]);
            rad = (std::fabs(e2[Z]) * t_half_size[X]) + (std::fabs(e2[X]) * t_half_size[Z]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            p0  = (e2[Y] * v1[X]) - (e2[X] * v1[Y]);
            p2  = (e2[Y] * v2[X]) - (e2[X] * v2[Y]);
            rad = (std::fabs(e2[Y]) * t_half_size[X]) + (std::fabs(e2[X]) * t_half_size[Y]);
            if ((std::min(p0, p2) > rad) || (std::max(p0, p2) < -rad))
            {
                return (false);
            }

            auto find_min_max = [](const double x0, const double x1, const double x2, double& min, double& max)
            {
                min = max = x0;

                if (x1 < min)
                {
                    min = x1;
                }
                if (x1 > max)
                {
                    max = x1;
                }
                if (x2 < min)
                {
                    min = x2;
                }
                if (x2 > max)
                {
                    max = x2;
                }
            };

            double min, max;
            find_min_max(v0[X], v1[X], v2[X], min, max);
            if ((min > t_half_size[X]) || (max < -t_half_size[X]))
            {
                return (false);
            }

            find_min_max(v0[Y], v1[Y], v2[Y], min, max);
            if ((min > t_half_size[Y]) || (max < -t_half_size[Y]))
            {
                return (false);
            }

            find_min_max(v0[Z], v1[Z], v2[Z], min, max);
            if ((min > t_half_size[Z]) || (max < -t_half_size[Z]))
            {
                return (false);
            }

            return (plane_origin_overlap(e0 ^ e1, v0, t_half_size));
        }

        /**
         *  Determine if a plane described by a given normal and point overlaps with a given box centered at the origin.
         *
         *  @param  t_norm          Normal of the plane.
         *  @param  t_point         Point located on the plane.
         *  @param  t_half_width    Half sizes of the box.
         *
         *  @return True if the plane and box are intersecting.
         */
        bool plane_origin_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point,
                                  const math::Vec<3>& t_half_width) const
        {
            math::Vec<3> min, max;

            for (size_t q = 0; q < 3; ++q)
            {
                double v = t_point[q];

                if (t_norm[q] > 0.0)
                {
                    min[q] = -t_half_width[q] - v;
                    max[q] = t_half_width[q] - v;
                }
                else
                {
                    min[q] = t_half_width[q] - v;
                    max[q] = -t_half_width[q] - v;
                }
            }

            return (((t_norm * min) <= 0.0) && ((t_norm * max) >= 0.0));

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
         *  @param  t_theta Angle to rotate around the global y-axis.
         *  @param  t_phi   Angle to then rotate around the global z-axis.
         *  @param  t_spin  Angle to initially rotate around the global z-axis.
         *
         *  @return The created orientation matrix.
         */
        Mat<4, 4> create_orient_mat(const double t_theta, const double t_phi, const double t_spin)
        {
            const Mat<4, 4> theta_mat({{{{std::cos(t_theta), 0.0, std::sin(t_theta), 0.0}}, {{0.0, 1.0, 0.0, 0.0}}, {{-std::sin(
                t_theta), 0.0, std::cos(t_theta), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            const Mat<4, 4> phi_mat({{{{std::cos(t_phi), -std::sin(t_phi), 0.0, 0.0}}, {{std::sin(t_phi), std::cos(
                t_phi), 0.0, 0.0}}, {{0.0, 0.0, 1.0, 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            const Mat<4, 4> spin_mat({{{{std::cos(t_spin), -std::sin(t_spin), 0.0, 0.0}}, {{std::sin(t_spin), std::cos(
                t_spin), 0.0, 0.0}}, {{0.0, 0.0, 1.0, 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (spin_mat * phi_mat * theta_mat);
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

            // Calculate spherical angles.
            const double theta = std::acos(t_dir[Z] / std::sqrt(square(t_dir[X]) + square(t_dir[Y]) + square(t_dir[Z])));
            const double phi   = std::atan2(t_dir[Y], t_dir[X]);

            return (create_orient_mat(theta, phi, t_spin));
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
