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

//  -- Classes --
#include "cls/math/vec.hpp"



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
            std::array<std::array<double, M>, N> data;  //! Two-dimensional array of data element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Mat();
            explicit constexpr Mat(double init_data);
            explicit constexpr Mat(const std::array<std::array<double, M>, N>& init_data);


            //  == OPERATORS ==
          public:
            //  -- Access --
            constexpr std::array<double, M>& operator[](size_t index);
            constexpr const std::array<double, M>& operator[](size_t index) const;

            //  -- Mathematical --
            constexpr Mat<N, M>& operator+=(double rhs);
            constexpr Mat<N, M>& operator+=(const Mat<N, M>& rhs);
            constexpr Mat<N, M>& operator-=(double rhs);
            constexpr Mat<N, M>& operator-=(const Mat<N, M>& rhs);
            constexpr Mat<N, M>& operator*=(double rhs);
            constexpr Mat<N, M>& operator*=(const Mat<M, M>& rhs);
            constexpr Mat<N, M>& operator/=(double rhs);
            constexpr Mat<N, M>& operator++();
            constexpr Mat<N, M> operator++(int /*unused*/);
            constexpr Mat<N, M>& operator--();
            constexpr Mat<N, M> operator--(int /*unused*/);
            constexpr Mat<N, M> operator+() const;
            constexpr Mat<N, M> operator-() const;
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator+(const Mat<U, V>& lhs, double rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator+(const Mat<U, V>& lhs, const Mat<U, V>& rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator-(const Mat<U, V>& lhs, double rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator-(const Mat<U, V>& lhs, const Mat<U, V>& rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator*(const Mat<U, V>& lhs, double rhs);
            template <size_t U, size_t V>
            friend constexpr Vec<U> operator*(const Mat<U, V>& lhs, const Vec<V>& rhs);
            template <size_t U, size_t V, size_t W>
            friend constexpr Mat<U, W> operator*(const Mat<U, V>& lhs, const Mat<V, W>& rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator/(const Mat<U, V>& lhs, double rhs);

            //  -- Printing --
            template <size_t U, size_t V>
            friend std::ostream& operator<<(std::ostream& stream, const Mat<U, V>& mat);
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a mat and initialise all of its data elements to zero.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat()
        {
            for (size_t i = 0; i < N; ++i)
            {
                std::fill(data[i].begin(), data[i].end(), 0.0);
            }
        }

        /**
         *  Construct a mat and initialise all of its data elements to the given initial value.
         *
         *  @param  init_data    Value to initialise all data elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const double init_data)
        {
            for (size_t i = 0; i < N; ++i)
            {
                std::fill(data[i].begin(), data[i].end(), init_data);
            }
        }

        /**
         *  Construct a mat and initialise all of its data elements using the given two-dimensional array.
         *
         *  @param  init_data    Two-dimensional array of values to initialise the mat data elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const std::array<std::array<double, M>, N>& init_data) :
            data(init_data)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to a column data element of the mat.
         *
         *  @param  index   Index of the data element to access.
         *
         *  @return A reference to the mat data element.
         */
        template <size_t N, size_t M>
        constexpr std::array<double, M>& Mat<N, M>::operator[](const size_t index)
        {
            return (data[index]);
        }

        /**
         *  Retrieve a reference to a const column data element of the mat.
         *
         *  @param  index   Index of the data element to access.
         *
         *  @return A reference to the const mat data element.
         */
        template <size_t N, size_t M>
        constexpr const std::array<double, M>& Mat<N, M>::operator[](const size_t index) const
        {
            return (data[index]);
        }


        //  -- Mathematical --
        /**
         *  Add a value to all data elements of a mat.
         *
         *  @param  rhs Value to add to each mat data element.
         *
         *  @return A reference to this mat post-addition.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator+=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] += rhs;
                }
            }

            return (*this);
        }

        /**
         *  Add the data element values of another mat to this mat.
         *
         *  @param  rhs Mat of data elements to add to this mat.
         *
         *  @return A reference to this mat post-addition.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator+=(const Mat<N, M>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] += rhs.data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Subtract a value from all data elements of a mat.
         *
         *  @param  rhs Value to subtract from each mat data element.
         *
         *  @return A reference to this mat post-subtraction.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator-=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] -= rhs;
                }
            }

            return (*this);
        }

        /**
         *  Subtract the data element values of another mat from this mat.
         *
         *  @param  rhs Mat of data elements to subtract from this mat.
         *
         *  @return A reference to this mat post-subtraction.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator-=(const Mat<N, M>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] -= rhs.data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Multiply all data elements of a mat by a value.
         *
         *  @param  rhs Value to multiply each mat data element by.
         *
         *  @return A reference to this mat post-multiplication.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator*=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] *= rhs;
                }
            }

            return (*this);
        }

        /**
         *  Multiply this mat by another mat.
         *  Multiplying mat must be a square matrix with a number of rows and columns equal to this mat's number of columns.
         *
         *  @param  rhs Mat to multiply this mat by.
         *
         *  @return A reference to this mat post-multiplication.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator*=(const Mat<M, M>& rhs)
        {
            const std::array<std::array<double, M>, N> lhs = data;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] = 0.0;

                    for (size_t k = 0; k < M; ++k)
                    {
                        data[i][j] += lhs[i][k] * rhs.data[k][j];
                    }
                }
            }

            return (*this);
        }

        /**
         *  Divide all data elements of a mat by a value.
         *
         *  @param  rhs Value to divide each mat data element by.
         *
         *  @return A reference to this mat post-division.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator/=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data[i][j] /= rhs;
                }
            }

            return (*this);
        }

        /**
         *  Increment each data element stored by the mat.
         *
         *  @return A reference to this mat post-increment.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator++()
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    ++data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Increment each data element stored by the mat.
         *
         *  @return A copy of this mat post-increment.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator++(int /*unused*/)
        {
            const Mat<N, M> mat = *this;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    ++data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Decrement each data element stored by the mat.
         *
         *  @return A reference to this mat post-decrement.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator--()
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    --data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Decrement each data element stored by the mat.
         *
         *  @return A copy of this mat post-decrement.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator--(int /*unused*/)
        {
            const Mat<N, M> mat = *this;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    --data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Create a mat with a copy of the data element values.
         *
         *  @return A copy of this mat with the same data element values.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator+() const
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = +data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Create a mat with a copy of the negated data element values.
         *
         *  @return A copy of this mat with the negated data element values.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator-() const
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = -data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by adding a given value to the data elements of a given mat.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator+(const Mat<N, M>& lhs, const double rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] + rhs;
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by adding the data elements of a given mat to another mat.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side mat operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator+(const Mat<N, M>& lhs, const Mat<N, M>& rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] + rhs.data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by subtracting a given value form the data elements of a given mat.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator-(const Mat<N, M>& lhs, const double rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] - rhs;
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by subtracting the data elements of a given mat from another mat.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side mat operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator-(const Mat<N, M>& lhs, const Mat<N, M>& rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] - rhs.data[i][j];
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by multiplying data elements of a given mat by a value.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator*(const Mat<N, M>& lhs, const double rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] * rhs;
                }
            }

            return (mat);
        }

        /**
         *  Determine the matrix-vector vector product.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The matrix-vector vector product.
         */
        template <size_t N, size_t M>
        constexpr Vec<N> operator*(const Mat<N, M>& lhs, const Vec<M>& rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    vec[i] += lhs.data[i][j] * rhs.data[j];
                }
            }

            return (vec);
        }

        /**
         *  Determine the matrix-matrix product.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side mat operand.
         *
         *  @return The matrix-matrix matrix product.
         */
        template <size_t N, size_t M, size_t O>
        constexpr Mat<N, O> operator*(const Mat<N, M>& lhs, const Mat<M, O>& rhs)
        {
            Mat<N, O> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < O; ++j)
                {
                    for (size_t k = 0; k < M; ++k)
                    {
                        mat.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
                    }
                }
            }

            return (mat);
        }

        /**
         *  Create a new mat by dividing data elements of a given mat by a value.
         *
         *  @param  lhs Left hand side mat operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator/(const Mat<N, M>& lhs, const double rhs)
        {
            Mat<N, M> mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    mat.data[i][j] = lhs.data[i][j] / rhs;
                }
            }

            return (mat);
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

            stream << "{{" << mat.data[0][0];
            for (size_t i = 1; i < M; ++i)
            {
                stream << ", " << mat.data[0][i];
            }
            stream << "}";
            for (size_t i = 1; i < N; ++i)
            {
                stream << ", {" << mat.data[i][0];
                for (size_t j = 1; j < M; ++j)
                {
                    stream << ", " << mat.data[i][j];
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
