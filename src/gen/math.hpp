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
        constexpr const double DEFAULT_EQUAL_TOL = std::numeric_limits<double>::epsilon(); //! Default maximum delta when equal.



        //  == FUNCTION PROTOTYPES ==
        //  -- Power --
        template <typename T>
        constexpr T square(T x);
        template <typename T>
        constexpr T cube(T x);

        //  -- Comparison --
        inline bool equal(double lhs, double rhs, double tol = DEFAULT_EQUAL_TOL);

        //  -- Matrix --
        inline Mat<4, 4> pos_trans(const Vec<3>& scale, const Vec<3>& rot, const Vec<3>& trans);
        inline Mat<4, 4> dir_trans(const Vec<3>& scale, const Vec<3>& rot);

        //  -- Geometry --
        template <size_t N>
        constexpr double dist(const math::Vec<N>& start, const math::Vec<N>& end);
        constexpr math::Vec<3> normal(const std::array<math::Vec<3>, 3>& pos);
        inline double area(const std::array<math::Vec<3>, 3>& pos);



        //  == FUNCTIONS ==
        //  -- Power --
        /**
         *  Square a given value.
         *
         *  @tparam T   Type being squared.
         *
         *  @param  x   Value to be squared.
         *
         *  @return The square of the given value.
         */
        template <typename T>
        constexpr T square(const T x)
        {
            return (x * x);
        }

        /**
         *  Cube a given value.
         *
         *  @tparam T   Type being cubed.
         *
         *  @param  x   Value to be cubed.
         *
         *  @return The cube of the given value.
         */
        template <typename T>
        constexpr T cube(const T x)
        {
            return (x * x * x);
        }


        //  -- Comparison --
        /**
         *  Determine if two double values can be considered equal to within a given tolerance.
         *  If the values differ by exactly the tolerance they are considered equal.
         *
         *  @param  lhs Left hand side double.
         *  @param  rhs Right hand side double.
         *  @param  tol Maximum tolerance to which the values are considered equal.
         *
         *  @return True if the values are equal within a given tolerance.
         */
        inline bool equal(const double lhs, const double rhs, const double tol)
        {
            return (std::fabs(lhs - rhs) <= tol);
        }


        //  -- Matrix --
        /**
         *  Create a position transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  scale   Scaling vector.
         *  @param  rot     Rotation vector.
         *  @param  trans   Translation vector.
         *
         *  @return The position transformation matrix.
         */
        inline Mat<4, 4> pos_trans(const Vec<3>& scale, const Vec<3>& rot, const Vec<3>& trans)
        {
            Mat<4, 4> scale_mat(
                {{{{scale[X], 0.0, 0.0, 0.0}}, {{0.0, scale[Y], 0.0, 0.0}}, {{0.0, 0.0, scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot_mat(
                {{{{cos(rot[Y]) * cos(rot[Z]), (cos(rot[Z]) * sin(rot[X]) * sin(rot[Y])) - (cos(rot[X]) * sin(rot[Z])), (cos(
                    rot[X]) * cos(rot[Z]) * sin(rot[Y])) - (sin(rot[X]) * sin(rot[Z])), 0.0}}, {{cos(rot[Y]) * sin(
                    rot[Z]), (cos(rot[X]) * cos(rot[Z])) + (sin(rot[X]) * sin(rot[Y]) * sin(rot[Z])), (cos(rot[X]) * sin(
                    rot[Y]) * sin(rot[Z])) - (cos(rot[Z]) * sin(rot[X])), 0.0}}, {{-sin(rot[Y]), cos(rot[Y]) * sin(rot[X]), cos(
                    rot[X]) * cos(rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> trans_mat(
                {{{{1.0, 0.0, 0.0, trans[X]}}, {{1.0, 0.0, 0.0, trans[Y]}}, {{1.0, 0.0, 0.0, trans[Z]}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (trans_mat * rot_mat * scale_mat);
        }

        /**
         *  Create a direction transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  scale   Scaling vector.
         *  @param  rot     Rotation vector.
         *
         *  @return The rotation transformation matrix.
         */
        inline Mat<4, 4> dir_trans(const Vec<3>& scale, const Vec<3>& rot)
        {
            Mat<4, 4> scale_mat(
                {{{{1.0 / scale[X], 0.0, 0.0, 0.0}}, {{0.0, 1.0 / scale[Y], 0.0, 0.0}}, {{0.0, 0.0, 1.0 / scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot_mat(
                {{{{cos(rot[Y]) * cos(rot[Z]), (cos(rot[Z]) * sin(rot[X]) * sin(rot[Y])) - (cos(rot[X]) * sin(rot[Z])), (cos(
                    rot[X]) * cos(rot[Z]) * sin(rot[Y])) - (sin(rot[X]) * sin(rot[Z])), 0.0}}, {{cos(rot[Y]) * sin(
                    rot[Z]), (cos(rot[X]) * cos(rot[Z])) + (sin(rot[X]) * sin(rot[Y]) * sin(rot[Z])), (cos(rot[X]) * sin(
                    rot[Y]) * sin(rot[Z])) - (cos(rot[Z]) * sin(rot[X])), 0.0}}, {{-sin(rot[Y]), cos(rot[Y]) * sin(rot[X]), cos(
                    rot[X]) * cos(rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (rot_mat * scale_mat);
        }


        //  -- Geometry --
        /**
         *  Determine the distance between two points.
         *
         *  @tparam N   Size of the vecs.
         *
         *  @param  start   Start point.
         *  @param  end     End point.
         *
         *  @return The distance between the two points.
         */
        template <size_t N>
        constexpr double dist(const math::Vec<N>& start, const math::Vec<N>& end)
        {
            return ((start - end).magnitude());
        }

        /**
         *  Determine the normal of a plane described by three points.
         *
         *  @param  pos Array of the three positional points lying within the plane.
         *
         *  @return The normal vector of the plane.
         */
        constexpr math::Vec<3> normal(const std::array<math::Vec<3>, 3>& pos)
        {
            math::Vec<3> norm = (pos[BETA] - pos[ALPHA]) ^(pos[GAMMA] - pos[ALPHA]);

            return (norm);
        }

        /**
         *  Determine the area described by three points.
         *
         *  @param  pos Array of three positional points describing the area.
         *
         *  @return The area described by the three points.
         */
        inline double area(const std::array<math::Vec<3>, 3>& pos)
        {
            const double alpha_beta  = dist(pos[ALPHA], pos[BETA]);
            const double beta_gamma  = dist(pos[BETA], pos[GAMMA]);
            const double gamma_alpha = dist(pos[GAMMA], pos[ALPHA]);

            const double half_perim = (alpha_beta + beta_gamma + gamma_alpha) / 2.0;

            return (std::sqrt(half_perim * (half_perim - alpha_beta) * (half_perim - beta_gamma) * (half_perim - gamma_alpha)));
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
