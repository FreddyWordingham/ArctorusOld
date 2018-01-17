/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   08/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_MATH_HPP
#define ARCTORUS_SRC_GEN_MATH_HPP



//  == INCLUDES ==
//  -- System --
#include <cmath>

//  -- Classes --
#include "cls/math/mat.hpp"
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == SETTINGS ==
        //  -- Defaults --
        constexpr const double DEFAULT_EQUAL_TOL = std::numeric_limits<double>::epsilon();  //! Default max delta when equal.



        //  == FUNCTION PROTOTYPES ==
        //  -- Power --
        template <typename T>
        constexpr T square(T t_x);
        template <typename T>
        constexpr T cube(T t_x);

        //  -- Comparison --
        inline bool equal(double t_lhs, double t_rhs, double t_tol = DEFAULT_EQUAL_TOL);

        //  -- Matrix --
        inline Mat<4, 4> pos_trans(const Vec<3>& t_scale, const Vec<3>& t_rot, const Vec<3>& t_trans);
        inline Mat<4, 4> dir_trans(const Vec<3>& t_scale, const Vec<3>& t_rot);

        //  -- Geometry --
        template <size_t N>
        constexpr double dist(const math::Vec<N>& t_start, const math::Vec<N>& t_end);
        constexpr math::Vec<3> normal(const std::array<math::Vec<3>, 3>& t_pos);
        inline double area(const std::array<math::Vec<3>, 3>& t_pos);



        //  == FUNCTIONS ==
        //  -- Power --
        /**
         *  Square a given value.
         *
         *  @tparam T   Type being squared.
         *
         *  @param  t_x Value to be squared.
         *
         *  @return The square of the given value.
         */
        template <typename T>
        constexpr T square(const T t_x)
        {
            return (t_x * t_x);
        }

        /**
         *  Cube a given value.
         *
         *  @tparam T   Type being cubed.
         *
         *  @param  t_x Value to be cubed.
         *
         *  @return The cube of the given value.
         */
        template <typename T>
        constexpr T cube(const T t_x)
        {
            return (t_x * t_x * t_x);
        }


        //  -- Comparison --
        /**
         *  Determine if two double values can be considered equal to within a given tolerance.
         *  If the values differ by exactly the tolerance they are considered equal.
         *
         *  @param  t_lhs   Left hand side double.
         *  @param  t_rhs   Right hand side double.
         *  @param  t_tol   Maximum tolerance to which the values are considered equal.
         *
         *  @return True if the values are equal within a given tolerance.
         */
        inline bool equal(const double t_lhs, const double t_rhs, const double t_tol)
        {
            return (std::fabs(t_lhs - t_rhs) <= t_tol);
        }


        //  -- Matrix --
        /**
         *  Create a position transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  t_scale Scaling vector.
         *  @param  t_rot   Rotation vector.
         *  @param  t_trans Translation vector.
         *
         *  @return The position transformation matrix.
         */
        inline Mat<4, 4> pos_trans(const Vec<3>& t_scale, const Vec<3>& t_rot, const Vec<3>& t_trans)
        {
            Mat<4, 4> scale(
                {{{{t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot(
                {{{{cos(t_rot[Y]) * cos(t_rot[Z]), (cos(t_rot[Z]) * sin(t_rot[X]) * sin(t_rot[Y])) - (cos(t_rot[X]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * cos(t_rot[Z]) * sin(t_rot[Y])) - (sin(t_rot[X]) * sin(t_rot[Z])), 0.0}}, {{cos(
                    t_rot[Y]) * sin(t_rot[Z]), (cos(t_rot[X]) * cos(t_rot[Z])) + (sin(t_rot[X]) * sin(t_rot[Y]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * sin(t_rot[Y]) * sin(t_rot[Z])) - (cos(t_rot[Z]) * sin(
                    t_rot[X])), 0.0}}, {{-sin(t_rot[Y]), cos(t_rot[Y]) * sin(t_rot[X]), cos(t_rot[X]) * cos(
                    t_rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> trans(
                {{{{1.0, 0.0, 0.0, t_trans[X]}}, {{1.0, 0.0, 0.0, t_trans[Y]}}, {{1.0, 0.0, 0.0, t_trans[Z]}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (trans * rot * scale);
        }

        /**
         *  Create a direction transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  t_scale Scaling vector.
         *  @param  t_rot   Rotation vector.
         *
         *  @return The rotation transformation matrix.
         */
        inline Mat<4, 4> dir_trans(const Vec<3>& t_scale, const Vec<3>& t_rot)
        {
            Mat<4, 4> scale(
                {{{{1.0 / t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, 1.0 / t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, 1.0 / t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot(
                {{{{cos(t_rot[Y]) * cos(t_rot[Z]), (cos(t_rot[Z]) * sin(t_rot[X]) * sin(t_rot[Y])) - (cos(t_rot[X]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * cos(t_rot[Z]) * sin(t_rot[Y])) - (sin(t_rot[X]) * sin(t_rot[Z])), 0.0}}, {{cos(
                    t_rot[Y]) * sin(t_rot[Z]), (cos(t_rot[X]) * cos(t_rot[Z])) + (sin(t_rot[X]) * sin(t_rot[Y]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * sin(t_rot[Y]) * sin(t_rot[Z])) - (cos(t_rot[Z]) * sin(
                    t_rot[X])), 0.0}}, {{-sin(t_rot[Y]), cos(t_rot[Y]) * sin(t_rot[X]), cos(t_rot[X]) * cos(
                    t_rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (rot * scale);
        }


        //  -- Geometry --
        /**
         *  Determine the distance between two points.
         *
         *  @tparam N   Size of the vecs.
         *
         *  @param  t_start Start point.
         *  @param  t_end   End point.
         *
         *  @return The distance between the two points.
         */
        template <size_t N>
        constexpr double dist(const math::Vec<N>& t_start, const math::Vec<N>& t_end)
        {
            return ((t_start - t_end).magnitude());
        }

        /**
         *  Determine the normal of a plane described by three points.
         *
         *  @param  t_pos   Array of the three positional points lying within the plane.
         *
         *  @return The normal vector of the plane.
         */
        constexpr math::Vec<3> normal(const std::array<math::Vec<3>, 3>& t_pos)
        {
            math::Vec<3> norm = (t_pos[BETA] - t_pos[ALPHA]) ^(t_pos[GAMMA] - t_pos[ALPHA]);

            return (norm);
        }

        /**
         *  Determine the area described by three points.
         *
         *  @param  t_pos   Array of three positional points describing the area.
         *
         *  @return The area described by the three points.
         */
        inline double area(const std::array<math::Vec<3>, 3>& t_pos)
        {
            const double alpha_beta  = dist(t_pos[ALPHA], t_pos[BETA]);
            const double beta_gamma  = dist(t_pos[BETA], t_pos[GAMMA]);
            const double gamma_alpha = dist(t_pos[GAMMA], t_pos[ALPHA]);

            const double half_perim = (alpha_beta + beta_gamma + gamma_alpha) / 2.0;

            return (std::sqrt(half_perim * (half_perim - alpha_beta) * (half_perim - beta_gamma) * (half_perim - gamma_alpha)));
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
