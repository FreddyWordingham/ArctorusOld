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



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == SETTINGS ==
        //  -- Defaults --
        constexpr const double DEFAULT_ARR_UNIFORM_TOL = std::numeric_limits<double>::epsilon();    //! Default uniform tol.



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr size_t max_index(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr T min(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr T max(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr T total(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr double magnitude(const std::array<T, N>& arr);

        //  -- Properties --
        template <typename T, size_t N>
        constexpr bool is_ascending(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr bool is_descending(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr bool is_monotonic(const std::array<T, N>& arr);
        template <typename T, size_t N>
        constexpr bool is_uniform(const std::array<T, N>& arr, double tol = DEFAULT_ARR_UNIFORM_TOL);



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Find the index of the array which holds the smallest element within the array.
         *  If multiple array elements are equally the smallest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to search.
         *
         *  @pre    N must not be zero.
         *
         *  @return The index of the smallest element within the array.
         */
        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (arr[i] < arr[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Find the index of the array which holds the largest element within the array.
         *  If multiple array elements are equally the largest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to search.
         *
         *  @pre    N must not be zero.
         *
         *  @return The index of the largest element within the array.
         */
        template <typename T, size_t N>
        constexpr size_t max_index(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (arr[i] > arr[index])
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
         *  @param  arr Array to copy the minimum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the smallest value within the array.
         */
        template <typename T, size_t N>
        constexpr T min(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            return (arr[min_index(arr)]);
        }

        /**
         *  Create a copy of the largest element within a given array.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to copy the maximum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the largest value within the array.
         */
        template <typename T, size_t N>
        constexpr T max(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            return (arr[max_index(arr)]);
        }

        /**
         *  Determine the total of all elements stored within a given array.
         *  Empty arrays are considered to have a total of zero.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to find the total of.
         *
         *  @return The total of all elements stored within the array.
         */
        template <typename T, size_t N>
        constexpr T total(const std::array<T, N>& arr)
        {
            T total = 0;

            for (size_t i = 0; i < N; ++i)
            {
                total += arr[i];
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
         *  @param  arr Array to find the magnitude of.
         *
         *  @return The magnitude of the array.
         */
        template <typename T, size_t N>
        constexpr double magnitude(const std::array<T, N>& arr)
        {
            T squared_total = 0;

            for (size_t i = 0; i < N; ++i)
            {
                squared_total += arr[i] * arr[i];
            }

            return (sqrt(static_cast<double>(squared_total)));
        }


        //  -- Properties --
        /**
         *  Determine if a given array's elements are sorted in ascending order.
         *  Array is not considered ascending if two consecutive values are equal.
         *  Array is considered ascending if the array contains only one element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to be analysed.
         *
         *  @pre    N must not be zero.
         *
         *  @return True if the array's elements are sorted in ascending order.
         */
        template <typename T, size_t N>
        constexpr bool is_ascending(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            for (size_t i = 1; i < N; ++i)
            {
                if (arr[i] < arr[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given array's elements are sorted in descending order.
         *  Array is not considered descending if two consecutive values are equal.
         *  Array is considered descending if the array contains only one element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to be analysed.
         *
         *  @pre    N must not be zero.
         *
         *  @return True if the array's elements are sorted in descending order.
         */
        template <typename T, size_t N>
        constexpr bool is_descending(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            for (size_t i = 1; i < N; ++i)
            {
                if (arr[i] > arr[i - 1])
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
         *  Array is considered monotonic if the array contains only one element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to be analysed.
         *
         *  @pre    N must not be zero.
         *
         *  @return True if the array's elements are sorted in monotonic order.
         */
        template <typename T, size_t N>
        constexpr bool is_monotonic(const std::array<T, N>& arr)
        {
            static_assert(N != 0);

            return (is_ascending(arr) || is_descending(arr));
        }

        /**
         *  Determine if a given array's elements are uniformly separated to within a given tolerance.
         *  Array must contain at more than one element.
         *
         *  @tparam T   Type stored by the array.
         *  @tparam N   Size of the array.
         *
         *  @param  arr Array to be analysed.
         *  @param  tol Maximum consecutive delta difference from the average delta where array is considered uniform.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the array's elements are uniformly spaced.
         */
        template <typename T, size_t N>
        constexpr bool is_uniform(const std::array<T, N>& arr, double tol)
        {
            static_assert(N >= 2);

            const double ave_delta = (arr.front() - arr.back()) / static_cast<double>(N - 1);

            for (size_t i = 1; i < N; ++i)
            {
                if ((fabs(arr[i - 1] - arr[i]) - ave_delta) > tol)
                {
                    return (false);
                }
            }

            return (true);
        }



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_ARRAY_HPP
