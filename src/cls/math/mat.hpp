/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MATH_MAT_HPP
#define ARCTORUS_SRC_CLS_MATH_MAT_HPP



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
         *  Mathematical matrix class.
         *  Acts as a mathematical matrix of double values.
         *  Should not be used for general purpose storage.
         *
         *  @tparam N   Number of matrix rows.
         *  @tparam M   Number of matrix columns.
         */
        template <size_t N, size_t M>
        class Mat
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::array<std::array<double, M>, N> element;   //! Two-dimensional array of element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();
            explicit constexpr Vec(double init_element);
            explicit constexpr Vec(const std::array<double, N>& init_element);


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_MAT_HPP
