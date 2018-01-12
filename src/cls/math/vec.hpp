/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   12/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MATH_VEC_HPP
#define ARCTORUS_SRC_CLS_MATH_VEC_HPP



//  == INCLUDES ==
//  -- System --
#include <array>



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == CLASS ==
        /**
         *  Mathematical vector class.
         *  Acts as a mathematical vector of double values.
         *  Should not be used for general purpose storage.
         *
         *  @tparam N   Size of the vec.
         */
        template <size_t N>
        class Vec
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::array<double, N> elements; //! Array of element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec and initialise all of its elements to zero.
         *
         * @tparam N
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(elements.begin(), elements.end(), 0.0);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
