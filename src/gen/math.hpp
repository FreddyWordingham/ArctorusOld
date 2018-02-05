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

//  -- General --
#include "gen/log.hpp"

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

        //  -- Conversion --
        template <typename T>
        inline T str_to(const std::string& t_str);

        //  -- Transformation --
        Mat<4, 4> create_trans_mat(const Vec<3>& t_trans);



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


        //  -- Conversion --
        /**
         *  Parse the string into a numerical value.
         *
         *  @tparam T   Type to parse the string into.
         *
         *  @param  t_str   String to be parsed.
         *
         *  @pre  t_str may not be empty.
         *
         *  @post string_stream read may not fail.
         *  @post string_stream may not have left over characters.
         *
         *  @return The parsed value of the string.
         */
        template <typename T>
        inline T str_to(const std::string& t_str)
        {
            assert(!t_str.empty());

            std::stringstream string_stream(t_str);

            T x;
            string_stream >> x;

            if (string_stream.fail())
            {
                ERROR("Unable to parse string to type.",
                      "String: '" << t_str << "' can not be parsed to type: '" << typeid(T).name() << "'.");
            }

            if (string_stream.rdbuf()->in_avail() != 0)
            {
                ERROR("Unable to parse string to type.",
                      "String: '" << t_str << "' contains leftover characters after parsing to type: '" << typeid(T).name()
                                  << "'.");
            }

            return (x);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
