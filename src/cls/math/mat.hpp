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
#include <cmath>
#include <iostream>
#include <utility>



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == CLASS PROTOTYPES ==
        template <size_t N>
        class Vec;



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
            std::array<std::array<double, M>, N> m_data;    //! Two-dimensional array of data element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Mat();
            explicit constexpr Mat(double t_data);
            explicit constexpr Mat(const std::array<std::array<double, M>, N>& t_data);


            //  == OPERATORS ==
          public:
            //  -- Access --
            constexpr std::array<double, M>& operator[](size_t t_index);
            constexpr const std::array<double, M>& operator[](size_t t_index) const;

            //  -- Mathematical --
            constexpr Mat<N, M>& operator+=(double t_rhs);
            constexpr Mat<N, M>& operator+=(const Mat<N, M>& t_rhs);
            constexpr Mat<N, M>& operator-=(double t_rhs);
            constexpr Mat<N, M>& operator-=(const Mat<N, M>& t_rhs);
            constexpr Mat<N, M>& operator*=(double t_rhs);
            constexpr Mat<N, M>& operator*=(const Mat<M, M>& t_rhs);
            constexpr Mat<N, M>& operator/=(double t_rhs);
            constexpr Mat<N, M>& operator++();
            constexpr Mat<N, M> operator++(int /*unused*/);
            constexpr Mat<N, M>& operator--();
            constexpr Mat<N, M> operator--(int /*unused*/);
            constexpr Mat<N, M> operator+() const;
            constexpr Mat<N, M> operator-() const;
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator+(const Mat<U, V>& t_lhs, double t_rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator+(const Mat<U, V>& t_lhs, const Mat<U, V>& t_rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator-(const Mat<U, V>& t_lhs, double t_rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator-(const Mat<U, V>& t_lhs, const Mat<U, V>& t_rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator*(const Mat<U, V>& t_lhs, double t_rhs);
            template <size_t U, size_t V, size_t W>
            friend constexpr Mat<U, W> operator*(const Mat<U, V>& t_lhs, const Mat<V, W>& t_rhs);
            template <size_t U, size_t V>
            friend constexpr Vec<U> operator*(const Mat<U, V>& t_lhs, const Vec<V>& t_rhs);
            template <size_t U, size_t V>
            friend constexpr Mat<U, V> operator/(const Mat<U, V>& t_lhs, double t_rhs);

            //  -- Printing --
            template <size_t U, size_t V>
            friend std::ostream& operator<<(std::ostream& t_stream, const Mat<U, V>& t_mat);
        };



        //  == FUNCTION PROTOTYPES ==
        //  -- Mathematical --
        constexpr double determinant(const Mat<2, 2>& t_mat);
        template <size_t N>
        constexpr double determinant(const Mat<N, N>& t_mat);
        template <size_t N, size_t M>
        constexpr Mat<M, N> transpose(const Mat<N, M>& t_mat);
        template <size_t N>
        constexpr Mat<N, N> minor(const Mat<N, N>& t_mat);



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
                std::fill(m_data[i].begin(), m_data[i].end(), 0.0);
            }
        }

        /**
         *  Construct a mat and initialise all of its data elements to the given initial value.
         *
         *  @param  t_data  Value to initialise all data elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const double t_data)
        {
            for (size_t i = 0; i < N; ++i)
            {
                std::fill(m_data[i].begin(), m_data[i].end(), t_data);
            }
        }

        /**
         *  Construct a mat and initialise all of its data elements using the given two-dimensional array.
         *
         *  @param  t_data  Two-dimensional array of values to initialise the mat data elements to.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>::Mat(const std::array<std::array<double, M>, N>& t_data) :
            m_data(t_data)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to a column data element of the mat.
         *
         *  @param  t_index Index of the data element to access.
         *
         *  @return A reference to the mat data element.
         */
        template <size_t N, size_t M>
        constexpr std::array<double, M>& Mat<N, M>::operator[](const size_t t_index)
        {
            return (m_data[t_index]);
        }

        /**
         *  Retrieve a reference to a const column data element of the mat.
         *
         *  @param  t_index Index of the data element to access.
         *
         *  @return A reference to the const mat data element.
         */
        template <size_t N, size_t M>
        constexpr const std::array<double, M>& Mat<N, M>::operator[](const size_t t_index) const
        {
            return (m_data[t_index]);
        }


        //  -- Mathematical --
        /**
         *  Add a value to all data elements of a mat.
         *
         *  @param  t_rhs   Value to add to each mat data element.
         *
         *  @return A reference to this mat post-addition.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator+=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] += t_rhs;
                }
            }

            return (*this);
        }

        /**
         *  Add the data element values of another mat to this mat.
         *
         *  @param  t_rhs   Mat of data elements to add to this mat.
         *
         *  @return A reference to this mat post-addition.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator+=(const Mat<N, M>& t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] += t_rhs.m_data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Subtract a value from all data elements of a mat.
         *
         *  @param  t_rhs   Value to subtract from each mat data element.
         *
         *  @return A reference to this mat post-subtraction.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator-=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] -= t_rhs;
                }
            }

            return (*this);
        }

        /**
         *  Subtract the data element values of another mat from this mat.
         *
         *  @param  t_rhs   Mat of data elements to subtract from this mat.
         *
         *  @return A reference to this mat post-subtraction.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator-=(const Mat<N, M>& t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] -= t_rhs.m_data[i][j];
                }
            }

            return (*this);
        }

        /**
         *  Multiply all data elements of a mat by a value.
         *
         *  @param  t_rhs   Value to multiply each mat data element by.
         *
         *  @return A reference to this mat post-multiplication.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator*=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] *= t_rhs;
                }
            }

            return (*this);
        }

        /**
         *  Multiply this mat by another mat.
         *  Multiplying mat must be a square matrix with a number of rows and columns equal to this mat's number of columns.
         *
         *  @param  t_rhs   Mat to multiply this mat by.
         *
         *  @return A reference to this mat post-multiplication.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator*=(const Mat<M, M>& t_rhs)
        {
            const std::array<std::array<double, M>, N> lhs = m_data;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] = 0.0;

                    for (size_t k = 0; k < M; ++k)
                    {
                        m_data[i][j] += lhs[i][k] * t_rhs.m_data[k][j];
                    }
                }
            }

            return (*this);
        }

        /**
         *  Divide all data elements of a mat by a value.
         *
         *  @param  t_rhs   Value to divide each mat data element by.
         *
         *  @return A reference to this mat post-division.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M>& Mat<N, M>::operator/=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    m_data[i][j] /= t_rhs;
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
                    ++m_data[i][j];
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
            const Mat<N, M> r_mat = *this;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    ++m_data[i][j];
                }
            }

            return (r_mat);
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
                    --m_data[i][j];
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
            const Mat<N, M> r_mat = *this;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    --m_data[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create a mat with a copy of the data element values.
         *
         *  @return A copy of this mat with the same data element values.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator+() const
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = +m_data[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create a mat with a copy of the negated data element values.
         *
         *  @return A copy of this mat with the negated data element values.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> Mat<N, M>::operator-() const
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = -m_data[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by adding a given value to the data elements of a given mat.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator+(const Mat<N, M>& t_lhs, const double t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] + t_rhs;
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by adding the data elements of a given mat to another mat.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side mat operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator+(const Mat<N, M>& t_lhs, const Mat<N, M>& t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] + t_rhs.m_data[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by subtracting a given value form the data elements of a given mat.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator-(const Mat<N, M>& t_lhs, const double t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] - t_rhs;
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by subtracting the data elements of a given mat from another mat.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side mat operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator-(const Mat<N, M>& t_lhs, const Mat<N, M>& t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] - t_rhs.m_data[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by multiplying data elements of a given mat by a value.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator*(const Mat<N, M>& t_lhs, const double t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] * t_rhs;
                }
            }

            return (r_mat);
        }

        /**
         *  Determine the matrix-matrix product.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side mat operand.
         *
         *  @return The matrix-matrix matrix product.
         */
        template <size_t N, size_t M, size_t O>
        constexpr Mat<N, O> operator*(const Mat<N, M>& t_lhs, const Mat<M, O>& t_rhs)
        {
            Mat<N, O> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < O; ++j)
                {
                    for (size_t k = 0; k < M; ++k)
                    {
                        r_mat.m_data[i][j] += t_lhs.m_data[i][k] * t_rhs.m_data[k][j];
                    }
                }
            }

            return (r_mat);
        }

        /**
         *  Create a new mat by dividing data elements of a given mat by a value.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created mat.
         */
        template <size_t N, size_t M>
        constexpr Mat<N, M> operator/(const Mat<N, M>& t_lhs, const double t_rhs)
        {
            Mat<N, M> r_mat;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat.m_data[i][j] = t_lhs.m_data[i][j] / t_rhs;
                }
            }

            return (r_mat);
        }


        //  -- Printing --
        /**
         *  Enable printing of a mat to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_mat       Mat to be written.
         *
         *  @return A reference to the stream post-write.
         */
        template <size_t N, size_t M>
        std::ostream& operator<<(std::ostream& t_stream, const Mat<N, M>& t_mat)
        {
            if (N == 0)
            {
                t_stream << "{{}}";

                return (t_stream);
            }
            if (M == 0)
            {
                t_stream << "{{}}";
                for (size_t i = 0; i < M; ++i)
                {
                    t_stream << ", {}";
                }
                t_stream << "}";

                return (t_stream);
            }

            t_stream << "{{" << t_mat.m_data[0][0];
            for (size_t i = 1; i < M; ++i)
            {
                t_stream << ", " << t_mat.m_data[0][i];
            }
            t_stream << "}";
            for (size_t i = 1; i < N; ++i)
            {
                t_stream << ", {" << t_mat.m_data[i][0];
                for (size_t j = 1; j < M; ++j)
                {
                    t_stream << ", " << t_mat.m_data[i][j];
                }
                t_stream << "}";
            }
            t_stream << "}";

            return (t_stream);
        }



        //  == FUNCTIONS ==
        //  -- Mathematical --
        /**
         *  Determine the determinant of a 2 by 2 matrix.
         *
         *  @param  t_mat   Matrix to determine the determinant of.
         *
         *  @return The determinant of the given matrix.
         */
        constexpr double determinant(const Mat<2, 2>& t_mat)
        {
            return ((t_mat[0][0] * t_mat[1][1]) - (t_mat[0][1] * t_mat[1][0]));
        }

        /**
         *  Determine in the determinant of a square matrix, larger than 2 by 2, through recursion.
         *
         *  @tparam N   Number of matrix rows and columns.
         *
         *  @param  t_mat   Matrix whose determinant is to be determined.
         *
         *  @pre    N must be greater than 2.
         *
         *  @return The determinant of the given matrix.
         */
        template <size_t N>
        constexpr double determinant(const Mat<N, N>& t_mat)
        {
            static_assert(N > 2);

            // Create return determinant.
            double r_det = 0.0;

            // Calculate the determinant.
            for (size_t i = 0; i < N; ++i)
            {
                // Create the sub-matrix.
                Mat<N - 1, N - 1> sub;

                size_t      n = 0;
                for (size_t j = 0; j < N; ++j)
                {
                    if (j == 0)
                    {
                        continue;
                    }

                    size_t      m = 0;
                    for (size_t k = 0; k < N; ++k)
                    {
                        if (k == i)
                        {
                            continue;
                        }

                        sub[n][m] = t_mat[j][k];

                        ++m;
                    }

                    ++n;
                }

                // Mutiply cofactor by the determinant of the minor matrix.
                r_det += std::pow(-1, 0 + i) * t_mat[0][i] * determinant(sub);
            }

            return (r_det);
        }

        /**
         *  Transpose a given matrix.
         *
         *  @tparam N   Number of matrix rows.
         *  @tparam M   Number of matrix columns.
         *
         *  @param  t_mat   Matrix to determine the transpose of.
         *
         *  @return The transpose of the given matrix.
         */
        template <size_t N, size_t M>
        constexpr Mat<M, N> transpose(const Mat<N, M>& t_mat)
        {
            // Create a the return matrix.
            Mat<M, N> r_mat;

            // Determine the transpose elements.
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_mat[j][i] = t_mat[i][j];
                }
            }

            return (r_mat);
        }

        /**
         *  Create the matrix of minors for a given square matrix of size 3 or greater.
         *
         *  @tparam N
         *
         *  @param t_mat
         *
         *  @pre    N must be greater than 2.
         *
         * @return
         */
        template <size_t N>
        constexpr Mat<N, N> minor(const Mat<N, N>& t_mat)
        {
            static_assert(N > 2);

            // Create the return matrix.
            Mat<N, N> r_minor;

            // Calculate the minors of the matrix.
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < N; ++j)
                {
                    // Create the sub-matrix.
                    Mat<N - 1, N - 1> sub;

                    size_t      n = 0;
                    for (size_t k = 0; k < N; ++k)
                    {
                        if (k == i)
                        {
                            continue;
                        }

                        size_t      m = 0;
                        for (size_t l = 0; l < N; ++l)
                        {
                            if (l == i)
                            {
                                continue;
                            }

                            sub[n][m] = t_mat[k][l];

                            ++m;
                        }

                        ++n;
                    }

                    r_minor[i][j] = determinant(sub);
                }
            }

            return (r_minor);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_MAT_HPP
