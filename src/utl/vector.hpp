/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   08/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_VECTOR_HPP
#define ARCTORUS_SRC_UTL_VECTOR_HPP



//  == INCLUDES ==
//  -- System --
#include <cassert>
#include <cmath>
#include <ostream>
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        template <typename T>
        constexpr size_t min_index(const std::vector<T>& t_vec);
        template <typename T>
        constexpr size_t max_index(const std::vector<T>& t_vec);
        template <typename T>
        constexpr T min(const std::vector<T>& t_vec);
        template <typename T>
        constexpr T max(const std::vector<T>& t_vec);
        template <typename T>
        constexpr T total(const std::vector<T>& t_vec);
        template <typename T>
        constexpr double magnitude(const std::vector<T>& t_vec);

        //  -- Properties --
        template <typename T>
        constexpr bool is_ascending(const std::vector<T>& t_vec);
        template <typename T>
        constexpr bool is_descending(const std::vector<T>& t_vec);
        template <typename T>
        constexpr bool is_monotonic(const std::vector<T>& t_vec);
        template <typename T>
        constexpr bool is_uniform(const std::vector<T>& t_vec, double t_tol = std::numeric_limits<double>::epsilon());
        template <typename T, typename S>
        constexpr bool is_always_less_than(const std::vector<T>& t_vec, S t_limit);
        template <typename T, typename S>
        constexpr bool is_always_less_than_or_equal_to(const std::vector<T>& t_vec, S t_limit);
        template <typename T, typename S>
        constexpr bool is_always_greater_than(const std::vector<T>& t_vec, S t_limit);
        template <typename T, typename S>
        constexpr bool is_always_greater_than_or_equal_to(const std::vector<T>& t_vec, S t_limit);

        //  -- Searching --
        template <typename T, typename S>
        size_t lower_index(const std::vector<T>& t_vec, S t_val, size_t t_init_guess = 0);
        template <typename T, typename S>
        size_t upper_index(const std::vector<T>& t_vec, S t_val, size_t t_init_guess = 1);



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Find the index of the vector which holds the smallest element.
         *  If multiple vector elements are equally the smallest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to search.
         *
         *  @pre    t_vec must not be empty.
         *
         *  @return The index of the smallest element within the vector.
         */
        template <typename T>
        constexpr size_t min_index(const std::vector<T>& t_vec)
        {
            assert(!t_vec.empty());

            size_t r_index = 0;

            for (size_t i = 1; i < t_vec.size(); ++i)
            {
                if (t_vec[i] < t_vec[r_index])
                {
                    r_index = i;
                }
            }

            return (r_index);
        }

        /**
         *  Find the index of the vector which holds the largest element.
         *  If multiple vector elements are equally the largest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to search.
         *
         *  @pre    t_vec must not be empty.
         *
         *  @return The index of the largest element within the vector.
         */
        template <typename T>
        constexpr size_t max_index(const std::vector<T>& t_vec)
        {
            assert(!t_vec.empty());

            size_t r_index = 0;

            for (size_t i = 1; i < t_vec.size(); ++i)
            {
                if (t_vec[i] > t_vec[r_index])
                {
                    r_index = i;
                }
            }

            return (r_index);
        }

        /**
         *  Create a copy of the smallest element within a given vector.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to copy the minimum value of.
         *
         *  @pre    t_vec must not be empty.
         *
         * @return  A copy of the smallest value within the vector.
         */
        template <typename T>
        constexpr T min(const std::vector<T>& t_vec)
        {
            assert(!t_vec.empty());

            return (t_vec[min_index(t_vec)]);
        }

        /**
         *  Create a copy of the largest element within a given vector.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to copy the maximum value of.
         *
         *  @pre    t_vec must not be empty.
         *
         * @return  A copy of the largest value within the vector.
         */
        template <typename T>
        constexpr T max(const std::vector<T>& t_vec)
        {
            assert(!t_vec.empty());

            return (t_vec[max_index(t_vec)]);
        }

        /**
         *  Determine the total of all elements stored within a given vector.
         *  Empty vectors are considered to have a total of zero.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to find the total of.
         *
         *  @return The total of all elements stored within the vector.
         */
        template <typename T>
        constexpr T total(const std::vector<T>& t_vec)
        {
            T r_total = 0;

            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                r_total += t_vec[i];
            }

            return (r_total);
        }

        /**
         *  Determine the magnitude of the given vector.
         *  Empty vectors are considered to have a magnitude of zero.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to find the magnitude of.
         *
         *  @return The magnitude of the vector.
         */
        template <typename T>
        constexpr double magnitude(const std::vector<T>& t_vec)
        {
            T squared_total = 0;

            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                squared_total += t_vec[i] * t_vec[i];
            }

            return (std::sqrt(static_cast<double>(squared_total)));
        }


        //  -- Properties --
        /**
         *  Determine if a given vector's elements are sorted in ascending order.
         *  Vector is not considered ascending if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to be analysed.
         *
         *  @pre    t_vec must contain more than one element.
         *
         *  @return True if the vector's elements are sorted in ascending order.
         */
        template <typename T>
        constexpr bool is_ascending(const std::vector<T>& t_vec)
        {
            assert(t_vec.size() > 1);

            for (size_t i = 1; i < t_vec.size(); ++i)
            {
                if (t_vec[i] < t_vec[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are sorted in descending order.
         *  Vector is not considered descending if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to be analysed.
         *
         *  @pre    t_vec must contain more than one element.
         *
         *  @return True if the vector's elements are sorted in descending order.
         */
        template <typename T>
        constexpr bool is_descending(const std::vector<T>& t_vec)
        {
            assert(t_vec.size() > 1);

            for (size_t i = 1; i < t_vec.size(); ++i)
            {
                if (t_vec[i] > t_vec[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are sorted in monotonic order.
         *  Determine if the vector's elements are sorted in ascending or descending order.
         *  Vector is not considered monotonic if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to be analysed.
         *
         *  @pre    t_vec must contain more than one element.
         *
         *  @return True if the vector's elements are sorted in monotonic order.
         */
        template <typename T>
        constexpr bool is_monotonic(const std::vector<T>& t_vec)
        {
            assert(t_vec.size() > 1);

            return (is_ascending(t_vec) || is_descending(t_vec));
        }

        /**
         *  Determine if a given vector's elements are uniformly separated to within a given tolerance.
         *  Vector must contain at more than one element.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  t_vec   Vector to be analysed.
         *  @param  t_tol   Maximum consecutive delta difference from the average delta where vector is considered uniform.
         *
         *  @pre    t_vec must contain more than one element.
         *
         *  @return True if the vector's elements are uniformly spaced.
         */
        template <typename T>
        constexpr bool is_uniform(const std::vector<T>& t_vec, double t_tol)
        {
            assert(t_vec.size() > 1);

            const double ave_delta = (t_vec.front() - t_vec.back()) / static_cast<double>(t_vec.size() - 1);

            for (size_t i = 1; i < t_vec.size(); ++i)
            {
                if ((std::fabs((t_vec[i - 1] - t_vec[i]) - ave_delta)) > t_tol)
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are always less than a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_vec   Vector to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vector's elements are all less than the given limit.
         */
        template <typename T, typename S>
        constexpr bool is_always_less_than(const std::vector<T>& t_vec, const S t_limit)
        {
            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                if (!(t_vec[i] < t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_vec   Vector to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vector's elements are all less than, or equal to, the given limit.
         */
        template <typename T, typename S>
        constexpr bool is_always_less_than_or_equal_to(const std::vector<T>& t_vec, const S t_limit)
        {
            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                if (!(t_vec[i] <= t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are always greater than a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_vec   Vector to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vector's elements are all greater than the given limit.
         */
        template <typename T, typename S>
        constexpr bool is_always_greater_than(const std::vector<T>& t_vec, const S t_limit)
        {
            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                if (!(t_vec[i] > t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_vec   Vector to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vector's elements are all greater than, or equal to, the given limit.
         */
        template <typename T, typename S>
        constexpr bool is_always_greater_than_or_equal_to(const std::vector<T>& t_vec, const S t_limit)
        {
            for (size_t i = 0; i < t_vec.size(); ++i)
            {
                if (!(t_vec[i] >= t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }


        //  -- Searching --
        /**
         *  Determine the lower index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the vector then the lower index is that index, unless it is the last
         *  element.
         *
         *  @tparam T   Type stored by the vector.
         *  @tparam S   Type of the value to be found within the vector.
         *
         *  @param  t_vec           Vector to hunt got the value placement.
         *  @param  t_val           Value to locate within the vector.
         *  @param  t_init_guess    Initial guess for the lower index.
         *
         *  @pre    t_vec must contain more than one element.
         *  @pre    t_vec must be sorted in monotonic order.
         *  @pre    t_val must be within the vec limits.
         *  @pre    t_init_guess must be a valid index of the vector.
         *
         *  @return The lower index of the element pair which encapsulates the value.
         */
        template <typename T, typename S>
        size_t lower_index(const std::vector<T>& t_vec, S t_val, const size_t t_init_guess)
        {
            assert(t_vec.size() > 1);
            assert(is_monotonic(t_vec));
            assert(
                ((t_val >= t_vec.front()) && (t_val <= t_vec.back())) || ((t_val <= t_vec.front()) && (t_val >= t_vec.back())));
            assert(t_init_guess < t_vec.size());

            bool ascending = t_vec.front() < t_vec.back();

            size_t r_lower_index = t_init_guess;
            size_t upper_index;

            size_t jump = 1;
            if ((t_val >= t_vec[r_lower_index]) == ascending)
            {
                if (r_lower_index == (t_vec.size() - 1))
                {
                    return (r_lower_index);
                }

                upper_index = r_lower_index + 1;
                while ((t_val >= t_vec[upper_index]) == ascending)
                {
                    r_lower_index = upper_index;
                    jump += jump;
                    upper_index   = r_lower_index + jump;
                    if (upper_index >= (t_vec.size() - 1))
                    {
                        upper_index = t_vec.size();

                        break;
                    }
                }
            }
            else
            {
                upper_index = r_lower_index--;
                while ((t_val < t_vec[r_lower_index]) == ascending)
                {
                    upper_index = r_lower_index;
                    jump <<= 1;
                    if (jump >= upper_index)
                    {
                        r_lower_index = 0;

                        break;
                    }

                    r_lower_index = upper_index - jump;
                }
            }

            while ((upper_index - r_lower_index) != 1)
            {
                size_t mid_index = (upper_index + r_lower_index) >> 1;
                if ((t_val >= t_vec[mid_index]) == ascending)
                {
                    r_lower_index = mid_index;
                }
                else
                {
                    upper_index = mid_index;
                }
            }

            if (std::fabs(t_val - t_vec.front()) <= std::numeric_limits<double>::epsilon())
            {
                return (0);
            }

            if (std::fabs(t_val - t_vec.back()) <= std::numeric_limits<double>::epsilon())
            {
                return (t_vec.size() - 2);
            }

            return (r_lower_index);
        }

        /**
         *  Determine the upper index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the vector then the upper index is that index, unless it is the first
         *  element.
         *
         *  @tparam T   Type stored by the vector.
         *  @tparam S   Type of the value to be found within the vector.
         *
         *  @param  t_vec           Vector to hunt for the value placement.
         *  @param  t_val           Value to locate within the vector.
         *  @param  t_init_guess    Initial guess for the upper index.
         *
         *  @pre    t_vec must contain more than one element.
         *  @pre    t_vec must be sorted in monotonic order.
         *  @pre    t_val must be within the vec limits.
         *  @pre    t_init_guess must be a valid index of the vector.
         *
         *  @return The upper index of the element pair which encapsulates the value.
         */
        template <typename T, typename S>
        size_t upper_index(const std::vector<T>& t_vec, S t_val, const size_t t_init_guess)
        {
            assert(t_vec.size() > 1);
            assert(is_monotonic(t_vec));
            assert(
                ((t_val >= t_vec.front()) && (t_val <= t_vec.back())) || ((t_val <= t_vec.front()) && (t_val >= t_vec.back())));
            assert(t_init_guess < t_vec.size());

            return (lower_index(t_vec, t_val, t_init_guess - 1) + 1);
        }



    } // namespace utl



    //  == OPERATORS PROTOTYPES ==
    //  -- Mathematical --
    template <typename T, typename S>
    constexpr std::vector<T> operator+(const std::vector<T>& t_lhs, S t_rhs);
    template <typename T, typename S>
    constexpr std::vector<T> operator-(const std::vector<T>& t_lhs, S t_rhs);
    template <typename T, typename S>
    constexpr std::vector<T> operator*(const std::vector<T>& t_lhs, S t_rhs);
    template <typename T, typename S>
    constexpr std::vector<T> operator/(const std::vector<T>& t_lhs, S t_rhs);

    //  -- Printing --
    template <typename T>
    std::ostream& operator<<(std::ostream& t_stream, const std::vector<T>& t_vec);



    //  == OPERATORS ==
    //  -- Mathematical --
    /**
     *  Create a new vector by adding a given value to the elements of a given vector.
     *
     *  @tparam T   Type stored by the vector.
     *  @tparam S   Type being added to the elements of the vector.
     *
     *  @param  t_lhs   Left hand side vector operand.
     *  @param  t_rhs   Right hand side value operand.
     *
     *  @return The created vector.
     */
    template <typename T, typename S>
    constexpr std::vector<T> operator+(const std::vector<T>& t_lhs, const S t_rhs)
    {
        std::vector<T> r_vec(t_lhs.size());

        for (size_t i = 0; i < t_lhs.size(); ++i)
        {
            r_vec[i] = t_lhs[i] + t_rhs;
        }

        return (r_vec);
    }

    /**
     *  Create a new vector by subtracting a given value form the elements of a given vector.
     *
     *  @tparam T   Type stored by the vector.
     *  @tparam S   Type being subtracted from the elements of the vector.
     *
     *  @param  t_lhs   Left hand side vector operand.
     *  @param  t_rhs   Right hand side value operand.
     *
     *  @return The created vector.
     */
    template <typename T, typename S>
    constexpr std::vector<T> operator-(const std::vector<T>& t_lhs, const S t_rhs)
    {
        std::vector<T> r_vec(t_lhs.size());

        for (size_t i = 0; i < t_lhs.size(); ++i)
        {
            r_vec[i] = t_lhs[i] - t_rhs;
        }

        return (r_vec);
    }

    /**
     *  Create a new vector by multiplying the elements of a given vector by a value.
     *
     *  @tparam T   Type stored by the vector.
     *  @tparam S   Type multiplying the elements of the vector.
     *
     *  @param  t_lhs   Left hand side vector operand.
     *  @param  t_rhs   Right hand side value operand.
     *
     *  @return The created vector.
     */
    template <typename T, typename S>
    constexpr std::vector<T> operator*(const std::vector<T>& t_lhs, const S t_rhs)
    {
        std::vector<T> r_vec(t_lhs.size());

        for (size_t i = 0; i < t_lhs.size(); ++i)
        {
            r_vec[i] = t_lhs[i] * t_rhs;
        }

        return (r_vec);
    }

    /**
     *  Create a new vector by dividing the elements of a given vector by a value.
     *
     *  @tparam T   Type stored by the vector.
     *  @tparam S   Type dividing the elements of the vector.
     *
     *  @param  t_lhs   Left hand side vector operand.
     *  @param  t_rhs   Right hand side value operand.
     *
     *  @return The created vector.
     */
    template <typename T, typename S>
    constexpr std::vector<T> operator/(const std::vector<T>& t_lhs, const S t_rhs)
    {
        std::vector<T> r_vec(t_lhs.size());

        for (size_t i = 0; i < t_lhs.size(); ++i)
        {
            r_vec[i] = t_lhs[i] / t_rhs;
        }

        return (r_vec);
    }


    //  -- Printing --
    /**
     *  Enable writing of a vector to a given ostream.
     *
     *  @tparam T   Type stored by the vector.
     *
     *  @param  t_stream    Stream to write to.
     *  @param  t_vec       Vector to be written.
     *
     *  @return A reference to the stream post-write.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& t_stream, const std::vector<T>& t_vec)
    {
        if (t_vec.empty())
        {
            t_stream << "()";

            return (t_stream);
        }

        t_stream << "(" << t_vec[0];
        for (size_t i = 1; i < t_vec.size(); ++i)
        {
            t_stream << ", " << t_vec[i];
        }
        t_stream << ")";

        return (t_stream);
    }



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_VECTOR_HPP
