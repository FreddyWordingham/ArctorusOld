/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   08/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_ARRAY_HPP
#define ARCTORUS_SRC_UTL_ARRAY_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <cassert>
#include <cmath>
#include <ostream>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr size_t max_index(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr T min(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr T max(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr T total(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr double magnitude(const std::array<T, N>& t_arr);

        //  -- Properties --
        template <typename T, size_t N>
        constexpr bool is_ascending(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr bool is_descending(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr bool is_monotonic(const std::array<T, N>& t_arr);
        template <typename T, size_t N>
        constexpr bool is_uniform(const std::array<T, N>& t_arr, double t_tol = std::numeric_limits<double>::epsilon());
        template <typename T, size_t N, typename S>
        constexpr bool is_always_less_than(const std::array<T, N>& t_arr, S t_limit);
        template <typename T, size_t N, typename S>
        constexpr bool is_always_less_than_or_equal_to(const std::array<T, N>& t_arr, S t_limit);
        template <typename T, size_t N, typename S>
        constexpr bool is_always_greater_than(const std::array<T, N>& t_arr, S t_limit);
        template <typename T, size_t N, typename S>
        constexpr bool is_always_greater_than_or_equal_to(const std::array<T, N>& t_arr, S t_limit);

        //  -- Searching --
        template <typename T, size_t N, typename S>
        size_t lower_index(const std::array<T, N>& t_arr, S t_val, size_t t_init_guess = 0);
        template <typename T, size_t N, typename S>
        size_t upper_index(const std::array<T, N>& t_arr, S t_val, size_t t_init_guess = 1);



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Find the index of the array which holds the smallest element.
         *  If multiple array elements are equally the smallest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to search.
         *
         *  @pre    N must not be zero.
         *
         *  @return The index of the smallest element within the array.
         */
        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N>& t_arr)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (t_arr[i] < t_arr[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Find the index of the array which holds the largest element.
         *  If multiple array elements are equally the largest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to search.
         *
         *  @pre    N must not be zero.
         *
         *  @return The index of the largest element within the array.
         */
        template <typename T, size_t N>
        constexpr size_t max_index(const std::array<T, N>& t_arr)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (t_arr[i] > t_arr[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Create a copy of the smallest element within a given array.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to copy the minimum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the smallest value within the array.
         */
        template <typename T, size_t N>
        constexpr T min(const std::array<T, N>& t_arr)
        {
            static_assert(N != 0);

            return (t_arr[min_index(t_arr)]);
        }

        /**
         *  Create a copy of the largest element within a given array.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to copy the maximum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the largest value within the array.
         */
        template <typename T, size_t N>
        constexpr T max(const std::array<T, N>& t_arr)
        {
            static_assert(N != 0);

            return (t_arr[max_index(t_arr)]);
        }

        /**
         *  Determine the total of all elements stored within a given array.
         *  Empty arrays are considered to have a total of zero.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to find the total of.
         *
         *  @return The total of all elements stored within the array.
         */
        template <typename T, size_t N>
        constexpr T total(const std::array<T, N>& t_arr)
        {
            T total = 0;

            for (size_t i = 0; i < N; ++i)
            {
                total += t_arr[i];
            }

            return (total);
        }

        /**
         *  Determine the magnitude of the given array.
         *  Empty arrays are considered to have a magnitude of zero.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to find the magnitude of.
         *
         *  @return The magnitude of the array.
         */
        template <typename T, size_t N>
        constexpr double magnitude(const std::array<T, N>& t_arr)
        {
            T squared_total = 0;

            for (size_t i = 0; i < N; ++i)
            {
                squared_total += t_arr[i] * t_arr[i];
            }

            return (std::sqrt(static_cast<double>(squared_total)));
        }


        //  -- Properties --
        /**
         *  Determine if a given array's elements are sorted in ascending order.
         *  Array is not considered ascending if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to be analysed.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the array's elements are sorted in ascending order.
         */
        template <typename T, size_t N>
        constexpr bool is_ascending(const std::array<T, N>& t_arr)
        {
            static_assert(N > 1);

            for (size_t i = 1; i < N; ++i)
            {
                if (t_arr[i] < t_arr[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are sorted in descending order.
         *  Array is not considered descending if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to be analysed.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the array's elements are sorted in descending order.
         */
        template <typename T, size_t N>
        constexpr bool is_descending(const std::array<T, N>& t_arr)
        {
            static_assert(N > 1);

            for (size_t i = 1; i < N; ++i)
            {
                if (t_arr[i] > t_arr[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are sorted in monotonic order.
         *  Determine if the array's elements are sorted in ascending or descending order.
         *  Array is not considered monotonic if two consecutive values are equal.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to be analysed.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the array's elements are sorted in monotonic order.
         */
        template <typename T, size_t N>
        constexpr bool is_monotonic(const std::array<T, N>& t_arr)
        {
            static_assert(N > 1);

            return (is_ascending(t_arr) || is_descending(t_arr));
        }

        /**
         *  Determine if a given array's elements are uniformly separated to within a given tolerance.
         *  Array must contain at more than one element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  t_arr   Array to be analysed.
         *  @param  t_tol   Maximum consecutive delta difference from the average delta where array is considered uniform.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the array's elements are uniformly spaced.
         */
        template <typename T, size_t N>
        constexpr bool is_uniform(const std::array<T, N>& t_arr, const double t_tol)
        {
            static_assert(N > 1);

            const double ave_delta = (t_arr.front() - t_arr.back()) / static_cast<double>(N - 1);

            for (size_t i = 1; i < N; ++i)
            {
                if ((std::fabs((t_arr[i - 1] - t_arr[i]) - ave_delta)) > t_tol)
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are always less than a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_arr   Array to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the array's elements are all less than the given limit.
         */
        template <typename T, size_t N, typename S>
        constexpr bool is_always_less_than(const std::array<T, N>& t_arr, const S t_limit)
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (!(t_arr[i] < t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_arr   Array to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the array's elements are all less than, or equal to, the given limit.
         */
        template <typename T, size_t N, typename S>
        constexpr bool is_always_less_than_or_equal_to(const std::array<T, N>& t_arr, const S t_limit)
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (!(t_arr[i] <= t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are always greater than a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_arr   Array to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the array's elements are all greater than the given limit.
         */
        template <typename T, size_t N, typename S>
        constexpr bool is_always_greater_than(const std::array<T, N>& t_arr, const S t_limit)
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (!(t_arr[i] > t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the limit.
         *
         *  @param  t_arr   Array to be analysed.
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the array's elements are all greater than, or equal to, the given limit.
         */
        template <typename T, size_t N, typename S>
        constexpr bool is_always_greater_than_or_equal_to(const std::array<T, N>& t_arr, const S t_limit)
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (!(t_arr[i] >= t_limit))
                {
                    return (false);
                }
            }

            return (true);
        }


        //  -- Searching --
        /**
         *  Determine the lower index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the array then the lower index is that index, unless it is the last element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  t_arr           Array to hunt got the value placement.
         *  @param  t_val           Value to locate within the array.
         *  @param  t_init_guess    Initial guess for the lower index.
         *
         *  @pre    N must be greater than one.
         *  @pre    arr must be sorted in monotonic order.
         *  @pre    val must be within the array limits.
         *  @pre    init_guess must be a valid index of the array.
         *
         *  @return The lower index of the element pair which encapsulates the value.
         */
        template <typename T, size_t N, typename S>
        size_t lower_index(const std::array<T, N>& t_arr, S t_val, const size_t t_init_guess)
        {
            static_assert(N > 1);
            assert(is_monotonic(t_arr));
            assert(
                ((t_val >= t_arr.front()) && (t_val <= t_arr.back())) || ((t_val <= t_arr.front()) && (t_val >= t_arr.back())));
            assert(t_init_guess < N);

            bool ascending = t_arr.front() < t_arr.back();

            size_t lower_index = t_init_guess;
            size_t upper_index;

            size_t jump = 1;
            if (t_val >= t_arr[lower_index] == ascending)
            {
                if (lower_index == (N - 1))
                {
                    return (lower_index);
                }

                upper_index = lower_index + 1;
                while (t_val >= t_arr[upper_index] == ascending)
                {
                    lower_index = upper_index;
                    jump += jump;
                    upper_index = lower_index + jump;
                    if (upper_index >= (N - 1))
                    {
                        upper_index = N;

                        break;
                    }
                }
            }
            else
            {
                upper_index = lower_index--;
                while (t_val < t_arr[lower_index] == ascending)
                {
                    upper_index = lower_index;
                    jump <<= 1;
                    if (jump >= upper_index)
                    {
                        lower_index = 0;

                        break;
                    }

                    lower_index = upper_index - jump;
                }
            }

            while ((upper_index - lower_index) != 1)
            {
                size_t mid_index = (upper_index + lower_index) >> 1;
                if (t_val >= t_arr[mid_index] == ascending)
                {
                    lower_index = mid_index;
                }
                else
                {
                    upper_index = mid_index;
                }
            }

            if (std::fabs(t_val - t_arr.front()) <= std::numeric_limits<double>::epsilon())
            {
                return (0);
            }

            if (std::fabs(t_val - t_arr.back()) <= std::numeric_limits<double>::epsilon())
            {
                return (N - 2);
            }

            return (lower_index);
        }

        /**
         *  Determine the upper index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the array then the upper index is that index, unless it is the first element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  t_arr           Array to hunt got the value placement.
         *  @param  t_val           Value to locate within the array.
         *  @param  t_init_guess    Initial guess for the upper index.
         *
         *  @pre    N must be greater than one.
         *  @pre    arr must be sorted in monotonic order.
         *  @pre    val must be within the array limits.
         *  @pre    init_guess must be a valid index of the array.
         *
         *  @return The upper index of the element pair which encapsulates the value.
         */
        template <typename T, size_t N, typename S>
        size_t upper_index(const std::array<T, N>& t_arr, S t_val, const size_t t_init_guess)
        {
            static_assert(N > 1);
            assert(is_monotonic(t_arr));
            assert(
                ((t_val >= t_arr.front()) && (t_val <= t_arr.back())) || ((t_val <= t_arr.front()) && (t_val >= t_arr.back())));
            assert(t_init_guess < N);

            return (lower_index(t_arr, t_val, t_init_guess - 1) + 1);
        }



    } // namespace utl



    //  == OPERATORS PROTOTYPES ==
    //  -- Printing --
    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& t_stream, const std::array<T, N>& t_arr);



    //  == OPERATORS ==
    //  -- Printing --
    /**
     *  Enable writing of an array to a given ostream.
     *
     *  @tparam T   Type stored by the array.
     *  @tparam N   Size of the array.
     *
     *  @param  t_stream    Stream to write to.
     *  @param  t_arr       Array to be written.
     *
     *  @return A reference to the stream post-write.
     */
    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& t_stream, const std::array<T, N>& t_arr)
    {
        if (N == 0)
        {
            t_stream << "[]";

            return (t_stream);
        }

        t_stream << "[" << t_arr[0];
        for (size_t i = 1; i < N; ++i)
        {
            t_stream << ", " << t_arr[i];
        }
        t_stream << "]";

        return (t_stream);
    }



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_ARRAY_HPP
