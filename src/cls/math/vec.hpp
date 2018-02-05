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
#include <initializer_list>
#include <ostream>

//  -- General --
#include "gen/enum.hpp"

//  -- Utility --
#include "utl/array.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == CLASS PROTOTYPES ==
        template <size_t N, size_t M>
        class Mat;



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
            std::array<double, N> m_data;   //! Array of data element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();
            explicit constexpr Vec(double t_data);
            explicit constexpr Vec(const std::array<double, N>& t_data);


            //  == OPERATORS ==
          public:
            //  -- Access --
            constexpr double& operator[](size_t t_index);
            constexpr const double& operator[](size_t t_index) const;

            //  -- Mathematical --
            constexpr Vec<N>& operator+=(double t_rhs);
            constexpr Vec<N>& operator+=(const Vec<N>& t_rhs);
            constexpr Vec<N>& operator-=(double t_rhs);
            constexpr Vec<N>& operator-=(const Vec<N>& t_rhs);
            constexpr Vec<N>& operator*=(double t_rhs);
            constexpr Vec<N>& operator*=(const Mat<N, N>& t_lhs);
            constexpr Vec<N>& operator/=(double t_rhs);
            constexpr Vec<N>& operator^=(const Vec<3>& t_rhs);
            constexpr Vec<N>& operator++();
            constexpr Vec<N> operator++(int /*unused*/);
            constexpr Vec<N>& operator--();
            constexpr Vec<N> operator--(int /*unused*/);
            constexpr Vec<N> operator+() const;
            constexpr Vec<N> operator-() const;
            template <size_t U>
            friend constexpr Vec<U> operator+(const Vec<U>& t_lhs, double t_rhs);
            template <size_t U>
            friend constexpr Vec<U> operator+(const Vec<U>& t_lhs, const Vec<U>& t_rhs);
            template <size_t U>
            friend constexpr Vec<U> operator-(const Vec<U>& t_lhs, double t_rhs);
            template <size_t U>
            friend constexpr Vec<U> operator-(const Vec<U>& t_lhs, const Vec<U>& t_rhs);
            template <size_t U>
            friend constexpr Vec<U> operator*(const Vec<U>& t_lhs, double t_rhs);
            template <size_t U>
            friend constexpr double operator*(const Vec<U>& t_lhs, const Vec<U>& t_rhs);
            template <size_t U, size_t V>
            friend constexpr Vec<U> operator*(const Mat<U, V>& t_lhs, const Vec<V>& t_rhs);
            template <size_t U>
            friend constexpr Vec<U> operator/(const Vec<U>& t_lhs, double t_rhs);
            friend constexpr Vec<3> operator^(const Vec<3>& t_lhs, const Vec<3>& t_rhs);

            //  -- Printing --
            template <size_t U>
            friend std::ostream& operator<<(std::ostream& t_stream, const Vec<U>& t_vec);


            //  == METHODS ==
          public:
            //  -- Mathematical --
            constexpr size_t min_index() const;
            constexpr size_t max_index() const;
            constexpr double min() const;
            constexpr double max() const;
            constexpr double total() const;
            constexpr double magnitude() const;
            constexpr void normalise();
            double get_rho() const;
            double get_theta() const;
            double get_phi() const;

            //  -- Properties --
            constexpr bool is_normalised(double t_tol = std::numeric_limits<double>::epsilon()) const;
            constexpr bool is_ascending() const;
            constexpr bool is_descending() const;
            constexpr bool is_monotonic() const;
            constexpr bool is_uniform(double t_tol = std::numeric_limits<double>::epsilon()) const;
            template <typename T>
            constexpr bool is_always_less_than(T t_limit) const;
            template <typename T>
            constexpr bool is_always_less_than_or_equal_to(T t_limit) const;
            template <typename T>
            constexpr bool is_always_greater_than(T t_limit) const;
            template <typename T>
            constexpr bool is_always_greater_than_or_equal_to(T t_limit) const;

            //  -- Searching --
            template <typename S>
            size_t lower_index(S t_val, size_t t_init_guess = 0) const;
            template <typename S>
            size_t upper_index(S t_val, size_t t_init_guess = 1) const;
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec and initialise all of its data elements to zero.
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(m_data.begin(), m_data.end(), 0.0);
        }

        /**
         *  Construct a vec and initialise all of its data elements to the given initial value.
         *
         *  @param  t_data  Value to initialise all data elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const double t_data)
        {
            std::fill(m_data.begin(), m_data.end(), t_data);
        }

        /**
         *  Construct a vec and initialise all of its data elements using the given array.
         *
         *  @param  t_data  Array of values to initialise the vec data elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const std::array<double, N>& t_data) :
            m_data(t_data)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to an data element of the vec.
         *
         *  @param  t_index Index of the data element to access.
         *
         *  @return A reference to the vec data element.
         */
        template <size_t N>
        constexpr double& Vec<N>::operator[](const size_t t_index)
        {
            return (m_data[t_index]);
        }

        /**
         *  Retrieve a reference to a const data element of the vec.
         *
         *  @param  t_index Index of the data element to access.
         *
         *  @return A reference to the const vec data element.
         */
        template <size_t N>
        constexpr const double& Vec<N>::operator[](const size_t t_index) const
        {
            return (m_data[t_index]);
        }


        //  -- Mathematical --
        /**
         *  Add a value to all data elements of a vec.
         *
         *  @param  t_rhs   Value to add to each vec data element.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] += t_rhs;
            }

            return (*this);
        }

        /**
         *  Add the data element values of another vec to this vec.
         *
         *  @param  t_rhs   Vec of data elements to add to this vec.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const Vec<N>& t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] += t_rhs.m_data[i];
            }

            return (*this);
        }

        /**
         *  Subtract a value from all data elements of a vec.
         *
         *  @param  t_rhs   Value to subtract from each vec data element.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] -= t_rhs;
            }

            return (*this);
        }

        /**
         *  Subtract the data element values of another vec from this vec.
         *
         *  @param  t_rhs   Vec of data elements to subtract from this vec.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const Vec<N>& t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] -= t_rhs.m_data[i];
            }

            return (*this);
        }

        /**
         *  Multiply all data elements of a vec by a value.
         *
         *  @param  t_rhs   Value to multiply each vec data element by.
         *
         *  @return A reference to this vec post-multiplication.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator*=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] *= t_rhs;
            }

            return (*this);
        }

        /**
         *  Determine the matrix-vector vector product of this vector and a square matrix of the same size.
         *  Note that unlike all other assignment operators, this vector is treated as the right hand side operand.
         *
         *  @param  t_lhs   Matrix to the form the lhs of the matrix-vector calculation.
         *
         *  @return A reference to this vec post-multiplication.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator*=(const Mat<N, N>& t_lhs)
        {
            std::array<double, N> t_rhs = m_data;

            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] = 0.0;

                for (size_t j = 0; j < N; ++j)
                {
                    m_data[i] += t_lhs[i][j] * t_rhs[j];
                }
            }

            return (*this);
        }

        /**
         *  Divide all data elements of a vec by a value.
         *
         *  @param  t_rhs   Value to divide each vec data element by.
         *
         *  @return A reference to this vec post-division.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator/=(const double t_rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] /= t_rhs;
            }

            return (*this);
        }


        /**
         *  Determine the cross-product of this vec and another given vec.
         *  This vec acts as the left hand side operand.
         *
         *  @param  t_rhs   Vec to perform cross product with.
         *
         *  @pre    N must equal three.
         *
         *  @return A reference to this vec post-operation.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator^=(const Vec<3>& t_rhs)
        {
            static_assert(N == 3);

            const std::array<double, 3> lhs = m_data;

            m_data[X] = (lhs[Y] * t_rhs[Z]) - (lhs[Z] * t_rhs[Y]);
            m_data[Y] = (lhs[Z] * t_rhs[X]) - (lhs[X] * t_rhs[Z]);
            m_data[Z] = (lhs[X] * t_rhs[Y]) - (lhs[Y] * t_rhs[X]);

            return (*this);
        }

        /**
         *  Increment each data element stored by the vec.
         *
         *  @return A reference to this vec post-increment.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator++()
        {
            for (size_t i = 0; i < N; ++i)
            {
                ++m_data[i];
            }

            return (*this);
        }

        /**
         *  Increment each data element stored by the vec.
         *
         *  @return A copy of this vec post-increment.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator++(const int /*unused*/)
        {
            const Vec<N> r_vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                ++m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Decrement each data element stored by the vec.
         *
         *  @return A reference to this vec post-decrement.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator--()
        {
            for (size_t i = 0; i < N; ++i)
            {
                --m_data[i];
            }

            return (*this);
        }

        /**
         *  Decrement each data element stored by the vec.
         *
         *  @return A copy of this vec post-decrement.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator--(const int /*unused*/)
        {
            const Vec<N> r_vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                --m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Create a vec with a copy of the data element values.
         *
         *  @return A copy of this vec with the same data element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator+() const
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec[i] = +m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Create a vec with a copy of the negated data element values.
         *
         *  @return A copy of this vec with the negated data element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator-() const
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec[i] = -m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by adding a given value to the data elements of a given vec.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator+(const Vec<N>& t_lhs, const double t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] + t_rhs;
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by adding the data elements of a given vec to another vec.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side vec operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator+(const Vec<N>& t_lhs, const Vec<N>& t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] + t_rhs.m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by subtracting a given value form the data elements of a given vec.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator-(const Vec<N>& t_lhs, const double t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] - t_rhs;
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by subtracting the data elements of a given vec from another vec.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side vec operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator-(const Vec<N>& t_lhs, const Vec<N>& t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] - t_rhs.m_data[i];
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by multiplying data elements of a given vec by a value.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator*(const Vec<N>& t_lhs, const double t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] * t_rhs;
            }

            return (r_vec);
        }

        /**
         *  Determine the dot-product of two vecs.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side vec operand.
         *
         *  @return The dot-product of the vecs.
         */
        template <size_t N>
        constexpr double operator*(const Vec<N>& t_lhs, const Vec<N>& t_rhs)
        {
            double r_prod = 0.0;

            for (size_t i = 0; i < N; ++i)
            {
                r_prod += t_lhs.m_data[i] * t_rhs.m_data[i];
            }

            return (r_prod);
        }

        /**
         *  Determine the matrix-vector vector product.
         *
         *  @param  t_lhs   Left hand side mat operand.
         *  @param  t_rhs   Right hand side vec operand.
         *
         *  @return The matrix-vector vector product.
         */
        template <size_t N, size_t M>
        constexpr Vec<N> operator*(const Mat<N, M>& t_lhs, const Vec<M>& t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    r_vec[i] += t_lhs.m_data[i][j] * t_rhs.m_data[j];
                }
            }

            return (r_vec);
        }

        /**
         *  Create a new vec by dividing data elements of a given vec by a value.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator/(const Vec<N>& t_lhs, const double t_rhs)
        {
            Vec<N> r_vec;

            for (size_t i = 0; i < N; ++i)
            {
                r_vec.m_data[i] = t_lhs.m_data[i] / t_rhs;
            }

            return (r_vec);
        }

        /**
         *  Determine the cross-product of two vecs.
         *
         *  @param  t_lhs   Left hand side vec operand.
         *  @param  t_rhs   Right hand side vec operand.
         *
         *  @return The cross-product of the vecs.
         */
        constexpr Vec<3> operator^(const Vec<3>& t_lhs, const Vec<3>& t_rhs)
        {
            Vec<3> r_prod;

            r_prod.m_data[X] = (t_lhs.m_data[Y] * t_rhs.m_data[Z]) - (t_lhs.m_data[Z] * t_rhs.m_data[Y]);
            r_prod.m_data[Y] = (t_lhs.m_data[Z] * t_rhs.m_data[X]) - (t_lhs.m_data[X] * t_rhs.m_data[Z]);
            r_prod.m_data[Z] = (t_lhs.m_data[X] * t_rhs.m_data[Y]) - (t_lhs.m_data[Y] * t_rhs.m_data[X]);

            return (r_prod);
        }


        //  -- Printing --
        /**
         *  Enable printing of a vec to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_vec       Vec to be written.
         *
         *  @return A reference to the stream post-write.
         */
        template <size_t N>
        std::ostream& operator<<(std::ostream& t_stream, const Vec<N>& t_vec)
        {
            if (N == 0)
            {
                t_stream << "⟨⟩";

                return (t_stream);
            }

            t_stream << "⟨" << t_vec.m_data[0];
            for (size_t i = 1; i < N; ++i)
            {
                t_stream << ", " << t_vec.m_data[i];
            }
            t_stream << "⟩";

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Mathematical --
        /**
        *  Find the index of the vec which holds the smallest data element.
        *  If multiple vec data elements are equally the smallest, the index of the first will be returned.
        *
        *  @pre    N must not be zero.
        *
        *  @return The index of the smallest data element within the vec.
        */
        template <size_t N>
        constexpr size_t Vec<N>::min_index() const
        {
            static_assert(N != 0);

            return (utl::min_index(m_data));
        }

        /**
         *  Find the index of the vec which holds the largest data element.
         *  If multiple vec data elements are equally the largest, the index of the first will be returned.
         *
         *  @pre    N must not be zero.
         *
         *  @return The index of the largest data element within the vec.
         */
        template <size_t N>
        constexpr size_t Vec<N>::max_index() const
        {
            static_assert(N != 0);

            return (utl::max_index(m_data));
        }

        /**
         *  Create a copy of the smallest data element within the vec.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the smallest value within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::min() const
        {
            static_assert(N != 0);

            return (utl::min(m_data));
        }

        /**
         *  Create a copy of the largest data element within the vec.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the largest value within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::max() const
        {
            static_assert(N != 0);

            return (utl::max(m_data));
        }

        /**
         *  Determine the total of all data elements stored within the vec.
         *  Empty vecs are considered to have a total of zero.
         *
         *  @return The total of all data elements stored within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::total() const
        {
            return (utl::total(m_data));
        }

        /**
         *  Determine the magnitude of the vec.
         *  Empty vecs are considered to have a magnitude of zero.
         *
         *  @return The magnitude of the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::magnitude() const
        {
            return (utl::magnitude(m_data));
        }

        /**
         *  Normalise the vec by dividing each data element by the magnitude of the total vec.
         */
        template <size_t N>
        constexpr void Vec<N>::normalise()
        {
            const double mag = utl::magnitude(m_data);

            for (size_t i = 0; i < N; ++i)
            {
                m_data[i] /= mag;
            }

            assert(is_normalised());
        }




        //  -- Properties --
        /**
         *  Determine if the vec is normalised to within a given tolerance.
         *
         *  @param  t_tol   Maximum deviation from unity where vec is considered uniform.
         *
         *  @return True if the vec's magnitude is equal to one within the given tolerance.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_normalised(const double t_tol) const
        {
            return (std::fabs(utl::magnitude(m_data) - 1.0) <= t_tol);
        }

        /**
         *  Determine if the vec's data elements are sorted in ascending order.
         *  Vec is not considered ascending if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's data elements are sorted in ascending order.
        */
        template <size_t N>
        constexpr bool Vec<N>::is_ascending() const
        {
            static_assert(N > 1);

            return (utl::is_ascending(m_data));
        }

        /**
         *  Determine if the vec's data elements are sorted in descending order.
         *  Vec is not considered descending if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's data elements are sorted in descending order.
        */
        template <size_t N>
        constexpr bool Vec<N>::is_descending() const
        {
            static_assert(N > 1);

            return (utl::is_descending(m_data));
        }

        /**
         *  Determine if the vec's data elements are sorted in monotonic order.
         *  Determine if the vec's data elements are sorted in ascending or descending order.
         *  Vec is not considered monotonic if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's data elements are sorted in monotonic order.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_monotonic() const
        {
            static_assert(N > 1);

            return (utl::is_monotonic(m_data));
        }

        /**
         *  Determine if the vec's data elements are uniformly separated to within a given tolerance.
         *  Vec must contain at more than one data element.
         *
         *  @param  t_tol   Maximum consecutive delta difference from the average delta where vec is considered uniform.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's data elements are uniformly spaced.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_uniform(const double t_tol) const
        {
            static_assert(N > 1);

            return (utl::is_uniform(m_data, t_tol));
        }

        /**
         *  Determine if a given vec's data elements are always less than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vec's data elements are all less than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than(const T t_limit) const
        {
            return (utl::is_always_less_than(m_data, t_limit));
        }

        /**
         *  Determine if a given vec's data elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vec's data elements are all less than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than_or_equal_to(const T t_limit) const
        {
            return (utl::is_always_less_than_or_equal_to(m_data, t_limit));
        }

        /**
         *  Determine if the vec's data elements are always greater than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vec's data elements are all greater than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than(const T t_limit) const
        {
            return (utl::is_always_greater_than(m_data, t_limit));
        }

        /**
         *  Determine if the vec's data elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  t_limit Limit to be tested.
         *
         *  @return True if the vec's data elements are all greater than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than_or_equal_to(const T t_limit) const
        {
            return (utl::is_always_greater_than_or_equal_to(m_data, t_limit));
        }


        //  -- Searching --
        /**
         *  Determine the lower index of the data element pair which encapsulates the given value.
         *  If the value is equal to an data element of the vec then the lower index is that index, unless it is the last data
         *  element.
         *
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  t_val           Value to locate within the vec.
         *  @param  t_init_guess    Initial guess for the upper index.
         *
         *  @pre    N must be greater than one.
         *  @pre    vec must be sorted in monotonic order.
         *  @pre    val must be within the array limits.
         *  @pre    init_guess must be a valid index of the vec.
         *
         *  @return The upper index of the data element pair which encapsulates the value.
         */
        template <size_t N>
        template <typename S>
        size_t Vec<N>::lower_index(const S t_val, const size_t t_init_guess) const
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(m_data));
            assert(((t_val >= m_data.front()) && (t_val <= m_data.back())) || ((t_val <= m_data.front()) && (t_val >= m_data
                .back())));
            assert(t_init_guess < N);

            return (utl::lower_index(m_data, t_val, t_init_guess));
        }

        /**
         *  Determine the upper index of the data element pair which encapsulates the given value.
         *  If the value is equal to an data element of the vec then the upper index is that index, unless it is the first data
         *  element.
         *
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  t_val           Value to locate within the vec.
         *  @param  t_init_guess    Initial guess for the upper index.
         *
         *  @pre    N must be greater than one.
         *  @pre    vec must be sorted in monotonic order.
         *  @pre    val must be within the array limits.
         *  @pre    init_guess must be a valid index of the vec.
         *
         *  @return The upper index of the data element pair which encapsulates the value.
         */
        template <size_t N>
        template <typename S>
        size_t Vec<N>::upper_index(const S t_val, const size_t t_init_guess) const
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(m_data));
            assert(((t_val >= m_data.front()) && (t_val <= m_data.back())) || ((t_val <= m_data.front()) && (t_val >= m_data
                .back())));
            assert(t_init_guess < N);

            return (utl::upper_index(m_data, t_val, t_init_guess));
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
