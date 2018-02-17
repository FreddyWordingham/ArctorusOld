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
#include <cls/geom/triangle.hpp>

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
        template <typename T>
        constexpr int sign(T val);

        //  -- Conversion --
        constexpr double deg_to_rad(double t_x);
        constexpr double rad_to_deg(double t_x);
        template <typename T>
        T str_to(const std::string& t_str);


        //  -- Geometry --
        template <size_t N>
        constexpr double dist(const Vec<N>& t_start, const Vec<N>& t_end);
        constexpr Vec<3> normal(const std::array<Vec<3>, 3>& t_pos);
        double area(const std::array<Vec<3>, 3>& t_pos);
        bool tri_box_overlap(const Vec<3>& t_max_vert, const Vec<3>& t_min_vert, const geom::Triangle& t_tri);

        //  -- Transformation --
        Mat<4, 4> create_trans_mat(const Vec<3>& t_trans);
        Mat<4, 4> create_orient_mat(double t_theta, double t_phi, double t_spin = 0.0);
        Mat<4, 4> create_orient_mat(const Vec<3>& t_dir, double t_spin = 0.0);
        Mat<4, 4> create_scale_pos_mat(const Vec<3>& t_scale);
        Mat<4, 4> create_scale_dir_mat(const Vec<3>& t_scale);
        Mat<4, 4> create_pos_trans_mat(const Vec<3>& t_trans, const Vec<3>& t_dir, double t_spin, const Vec<3>& t_scale);
        Mat<4, 4> create_dir_trans_mat(const Vec<3>& t_dir, double t_spin, const Vec<3>& t_scale);



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

        /**
         *  Determine the sign of a given value.
         *
         *  @tparam T   Type to determine the sign of.
         *
         *  @param  val Value to determine the sign of.
         *
         *  @return The sign of the given value.
         */
        template <typename T>
        constexpr int sign(const T val)
        {
            return (T(0) < val) - (val < T(0));
        }


        //  -- Conversion --
        /**
         *  Convert a value in degrees to a value in radians.
         *
         *  @param  t_x Value to convert in units of degrees.
         *
         *  @return The value in radians.
         */
        constexpr double deg_to_rad(const double t_x)
        {
            return (t_x * M_PI / 180.0);
        }

        /**
         *  Convert a value in radians to a value in degrees.
         *
         *  @param  t_x Value to convert in units of radians.
         *
         *  @return The value in degrees.
         */
        constexpr double rad_to_deg(const double t_x)
        {
            return (t_x * 180.0 / M_PI);
        }

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
        T str_to(const std::string& t_str)
        {
            assert(!t_str.empty());

            // Convert string to a stringstream.
            std::stringstream string_stream(t_str);

            // Attempt to pass the value into the stringstream.
            T x;
            string_stream >> x;

            // Report error if parsing failed.
            if (string_stream.fail())
            {
                ERROR("Unable to parse string to type.",
                      "String: '" << t_str << "' can not be parsed to type: '" << typeid(T).name() << "'.");
            }

            // Report error if there are characters left over in the stream.
            if (string_stream.rdbuf()->in_avail() != 0)
            {
                ERROR("Unable to parse string to type.",
                      "String: '" << t_str << "' contains leftover characters after parsing to type: '" << typeid(T).name()
                                  << "'.");
            }

            return (x);
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
        constexpr double dist(const Vec<N>& t_start, const Vec<N>& t_end)
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
        constexpr Vec<3> normal(const std::array<Vec<3>, 3>& t_pos)
        {
            // Determine the normal from the cross product.
            Vec<3> r_norm = (t_pos[BETA] - t_pos[ALPHA]) ^(t_pos[GAMMA] - t_pos[ALPHA]);

            // Normalise the vector.
            r_norm.normalise();

            return (r_norm);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
