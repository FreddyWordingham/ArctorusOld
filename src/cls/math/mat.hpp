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
            constexpr Mat();
            explicit constexpr Mat(double init_element);
            explicit constexpr Mat(const std::array<std::array<double, M>, N>& init_element);


            //  == OPERATORS ==
          public:
            //  -- Access --
            constexpr std::array<double, M>& operator[](size_t index);
            constexpr const std::array<double, M>& operator[](size_t index) const;

            //  -- Printing --
            template <size_t U, size_t V>
            friend std::ostream& operator<<(std::ostream& stream, const Mat<U, V>& mat);


            //  == METHODS ==
          private:
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a mat and initialise all of its elements to zero.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat()
        {
            std::fill(element.begin(), element.end(), 0.0);
        }

        /**
         *  Construct a mat and initialise all of its elements to the given initial value.
         *
         *  @param  init_element    Value to initialise all elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const double init_element)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    element[i][j] = init_element;
                }
            }
        }

        /**
         *  Construct a mat and initialise all of its elements using the given two-dimensional array.
         *
         *  @param  init_element    Two-dimensional array of values to initialise the vec elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const std::array<std::array<double, M>, N>& init_element) :
            element(init_element)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to a column element of the mat.
         *
         *  @param  index   Index of the element to access.
         *
         *  @return A reference to the mat element.
         */
        template <size_t N, size_t M>
        constexpr std::array<double, M>& Mat<N, M>::operator[](const size_t index)
        {
            return (element[index]);
        }

        /**
         *  Retrieve a reference to a const column element of the mat.
         *
         *  @param  index   Index of the element to access.
         *
         *  @return A reference to the const mat element.
         */
        template <size_t N, size_t M>
        constexpr const std::array<double, M>& Mat<N, M>::operator[](const size_t index) const
        {
            return (element[index]);
        }


        //  -- Printing --
        /**
         *  Enable printing of a mat to a given ostream.
         *
         *  @param  stream  Stream to write to.
         *  @param  mat     Mat to be written.
         *
         *  @return A reference to the stream post-write.
         */
        template <size_t N, size_t M>
        std::ostream& operator<<(std::ostream& stream, const Mat<N, M>& mat)
        {
            if (N == 0)
            {
                stream << "{{}}";

                return (stream);
            }
            if (M == 0)
            {
                stream << "{{}}";
                for (size_t i = 0; i < M; ++i)
                {
                    stream << ", {}";
                }
                stream << "}";

                return (stream);
            }

            stream << "{{" << mat.element[0][0];
            for (size_t i = 1; i < M; ++i)
            {
                stream << ", " << mat.element[0][i];
            }
            stream << "}";
            for (size_t i = 1; i < N; ++i)
            {
                stream << ", {" << mat.element[i][0];
                for (size_t j = 1; j < M; ++j)
                {
                    stream << ", " << mat.element[i][j];
                }
                stream << "}";
            }
            stream << "}";

            return (stream);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_MAT_HPP
