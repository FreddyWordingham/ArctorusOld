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
