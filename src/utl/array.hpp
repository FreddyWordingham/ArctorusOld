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



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N>& arr);



        //  == FUNCTIONS ==
        //  -- Mathematical --

        template <typename T, size_t N>
        constexpr size_t min_index(const std::array<T, N> &arr)
        {
            static_assert(N != 0);
        };



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_ARRAY_HPP
