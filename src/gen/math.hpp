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



//  == NAMESPACE ==
namespace arc
{



    //  == FUNCTION PROTOTYPES ==
    //  -- Power --
    template <typename T>
    constexpr T square(T x);
    template <typename T>
    constexpr T cube(T x);



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



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_MATH_HPP
