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
#include <vector>
#include <cassert>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == SETTINGS ==
        //  -- Defaults --
        constexpr const double DEFAULT_VEC_UNIFORM_TOL = std::numeric_limits<double>::epsilon();    //! Default uniform tol.



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        template <typename T>
        constexpr size_t min_index(const std::vector<T>& vec);
        template <typename T>
        constexpr size_t max_index(const std::vector<T>& vec);
        template <typename T>
        constexpr T min(const std::vector<T>& vec);
        template <typename T>
        constexpr T max(const std::vector<T>& vec);
        template <typename T>
        constexpr T total(const std::vector<T>& vec);
        template <typename T>
        constexpr double magnitude(const std::vector<T>& vec);

        //  -- Properties --
        template <typename T>
        constexpr bool is_ascending(const std::vector<T>& vec);
        template <typename T>
        constexpr bool is_descending(const std::vector<T>& vec);
        template <typename T>
        constexpr bool is_monotonic(const std::vector<T>& vec);
        template <typename T>
        constexpr bool is_uniform(const std::vector<T>& vec, double tol = DEFAULT_VEC_UNIFORM_TOL);



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Find the index of the vector which holds the smallest element.
         *  If multiple vector elements are equally the smallest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to search.
         *
         *  @pre    vec must not be empty.
         *
         *  @return The index of the smallest element within the vector.
         */
        template <typename T>
        constexpr size_t min_index(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            size_t index = 0;

            for (size_t i = 1; i < vec.size(); ++i)
            {
                if (vec[i] < vec[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Find the index of the vector which holds the largest element.
         *  If multiple vector elements are equally the largest, the index of the first will be returned.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to search.
         *
         *  @pre    vec must not be empty.
         *
         *  @return The index of the largest element within the vector.
         */
        template <typename T>
        constexpr size_t max_index(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            size_t index = 0;

            for (size_t i = 1; i < vec.size(); ++i)
            {
                if (vec[i] > vec[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Create a copy of the smallest element within a given vector.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to copy the minimum value of.
         *
         *  @pre    vec must not be empty.
         *
         * @return  A copy of the smallest value within the vector.
         */
        template <typename T>
        constexpr T min(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            return (vec[min_index(vec)]);
        }

        /**
         *  Create a copy of the largest element within a given vector.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to copy the maximum value of.
         *
         *  @pre    vec must not be empty.
         *
         * @return  A copy of the largest value within the vector.
         */
        template <typename T>
        constexpr T max(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            return (vec[max_index(vec)]);
        }

        /**
         *  Determine the total of all elements stored within a given vector.
         *  Empty vectors are considered to have a total of zero.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to find the total of.
         *
         *  @return The total of all elements stored within the vector.
         */
        template <typename T>
        constexpr T total(const std::vector<T>& vec)
        {
            T total = 0;

            for (size_t i = 0; i < vec.size(); ++i)
            {
                total += vec[i];
            }

            return (total);
        }

        /**
         *  Determine the magnitude of the given vector.
         *  Empty vectors are considered to have a magnitude of zero.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to find the magnitude of.
         *
         *  @return The magnitude of the vector.
         */
        template <typename T>
        constexpr double magnitude(const std::vector<T>& vec)
        {
            T squared_total = 0;

            for (size_t i = 0; i < vec.size(); ++i)
            {
                squared_total += vec[i] * vec[i];
            }

            return (std::sqrt(static_cast<double>(squared_total)));
        }


        //  -- Properties --
        /**
         *  Determine if a given vector's elements are sorted in ascending order.
         *  Vector is not considered ascending if two consecutive values are equal.
         *  Vector is considered ascending if the vector contains only one element.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to be analysed.
         *
         *  @pre    vec must not be empty.
         *
         *  @return True if the vector's elements are sorted in ascending order.
         */
        template <typename T>
        constexpr bool is_ascending(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            for (size_t i = 1; i < vec.size(); ++i)
            {
                if (vec[i] < vec[i - 1])
                {
                    return (false);
                }
            }

            return (true);
        }

        /**
         *  Determine if a given vector's elements are sorted in descending order.
         *  Vector is not considered descending if two consecutive values are equal.
         *  Vector is considered descending if the vector contains only one element.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to be analysed.
         *
         *  @pre    vec must not be empty.
         *
         *  @return True if the vector's elements are sorted in descending order.
         */
        template <typename T>
        constexpr bool is_descending(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            for (size_t i = 1; i < vec.size(); ++i)
            {
                if (vec[i] > vec[i - 1])
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
         *  Vector is considered monotonic if the vector contains only one element.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to be analysed.
         *
         *  @pre    vec must not be empty.
         *
         *  @return True if the vector's elements are sorted in monotonic order.
         */
        template <typename T>
        constexpr bool is_monotonic(const std::vector<T>& vec)
        {
            assert(!vec.empty());

            return (is_ascending(vec) || is_descending(vec));
        }

        /**
         *  Determine if a given vector's elements are uniformly separated to within a given tolerance.
         *  Vector must contain at more than one element.
         *
         *  @tparam T   Type stored by the vector.
         *
         *  @param  vec Vector to be analysed.
         *  @param  tol Maximum consecutive delta difference from the average delta where vector is considered uniform.
         *
         *  @pre    vec must contain more than one element.
         *
         *  @return True if the vector's elements are uniformly spaced.
         */
        template <typename T>
        constexpr bool is_uniform(const std::vector<T>& vec, double tol)
        {
            assert(vec.size() > 1);

            const double ave_delta = (vec.front() - vec.back()) / static_cast<double>(vec.size() - 1);

            for (size_t i = 1; i < vec.size(); ++i)
            {
                if ((std::fabs((vec[i - 1] - vec[i]) - ave_delta)) > tol)
                {
                    return (false);
                }
            }

            return (true);
        }



    } // namespace utl



    //  == OPERATORS PROTOTYPES ==
    //  -- Printing --
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec);



    //  == OPERATORS ==
    //  -- Printing --
    /**
     *  Enable writing of a vector to a given ostream.
     *
     *  @tparam T   Type stored by the vector.
     *
     *  @param  stream  Stream to write to.
     *  @param  vec     Vector to be written.
     *
     *  @return A reference to the stream post-write.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec)
    {
        if (vec.empty())
        {
            stream << "[]";

            return (stream);
        }

        stream << "[" << vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            stream << ", " << vec[i];
        }
        stream << "]";

        return (stream);
    }



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_VECTOR_HPP
