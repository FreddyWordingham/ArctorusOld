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
        inline Mat<4, 4> create_pos_trans(const Vec<3>& scale, const Vec<3>& rot, const Vec<3>& tran);



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
        inline Mat<4, 4> create_pos_trans(const Vec<3>& scale, const Vec<3>& rot, const Vec<3>& tran)
        {
            return (Mat<4, 4>(
                {{{{scale[X], 0.0, 0.0, 0.0}}, {{0.0, scale[Y], 0.0, 0.0}}, {{0.0, 0.0, scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}}));

/*            Mat<4, 4> rotate(
                {{cos(rot[Y]) * cos(rot[Z]),
                     (cos(rot[Z]) * sin(rot[X]) * sin(rot[Y])) - (cos(rot[X]) * sin(rot[Z])),
                     (cos(rot[X]) * cos(rot[Z]) * sin(rot[Y])) - (sin(rot[X]) * sin(rot[Z])), 0.0},
                 {cos(rot[Y]) * sin(rot[Z]),
                     (cos(rot[X]) * cos(rot[Z])) + (sin(rot[X]) * sin(rot[Y]) * sin(rot[Z])),
                     (cos(rot[X]) * sin(rot[Y]) * sin(rot[Z])) - (cos(rot[Z]) * sin(rot[X])), 0.0},
                 {-sin(rot[Y]), cos(rot[Y]) * sin(rot[X]), cos(rot[X]) * cos(rot[Y]), 0.0},
                 {0.0, 0.0, 0.0, 1.0}});

            Mat<4, 4> translate({{1.0, 0.0, 0.0, t_translate[X]},
                                 {1.0, 0.0, 0.0, t_translate[Y]},
                                 {1.0, 0.0, 0.0, t_translate[Z]},
                                 {0.0, 0.0, 0.0, 1.0}});

            return (translate * rotate * scale);*/
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
