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
            std::array<double, N> data; //! Array of data element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();
            explicit constexpr Vec(double init_data);
            explicit constexpr Vec(const std::array<double, N>& init_data);


            //  == OPERATORS ==
          public:
            //  -- Access --
            constexpr double& operator[](size_t index);
            constexpr const double& operator[](size_t index) const;

            //  -- Mathematical --
            constexpr Vec<N>& operator+=(double rhs);
            constexpr Vec<N>& operator+=(const Vec<N>& rhs);
            constexpr Vec<N>& operator-=(double rhs);
            constexpr Vec<N>& operator-=(const Vec<N>& rhs);
            constexpr Vec<N>& operator*=(double rhs);
            constexpr Vec<N>& operator/=(double rhs);
            constexpr Vec<N>& operator^=(const Vec<3>& rhs);
            constexpr Vec<N>& operator++();
            constexpr Vec<N> operator++(int /*unused*/);
            constexpr Vec<N>& operator--();
            constexpr Vec<N> operator--(int /*unused*/);
            constexpr Vec<N> operator+() const;
            constexpr Vec<N> operator-() const;
            template <size_t U>
            friend constexpr Vec<U> operator+(const Vec<U>& lhs, double rhs);
            template <size_t U>
            friend constexpr Vec<U> operator+(const Vec<U>& lhs, const Vec<U>& rhs);
            template <size_t U>
            friend constexpr Vec<U> operator-(const Vec<U>& lhs, double rhs);
            template <size_t U>
            friend constexpr Vec<U> operator-(const Vec<U>& lhs, const Vec<U>& rhs);
            template <size_t U>
            friend constexpr Vec<U> operator*(const Vec<U>& lhs, double rhs);
            template <size_t U>
            friend constexpr double operator*(const Vec<U>& lhs, const Vec<U>& rhs);
            template <size_t U, size_t V>
            friend constexpr Vec<U> operator*(const Mat<U, V>& lhs, const Vec<V>& rhs);
            template <size_t U>
            friend constexpr Vec<U> operator/(const Vec<U>& lhs, double rhs);
            friend constexpr Vec<3> operator^(const Vec<3>& lhs, const Vec<3>& rhs);

            //  -- Printing --
            template <size_t U>
            friend std::ostream& operator<<(std::ostream& stream, const Vec<U>& vec);



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

            //  -- Properties --
            constexpr bool is_normalised(double tol = std::numeric_limits<double>::epsilon()) const;
            constexpr bool is_ascending() const;
            constexpr bool is_descending() const;
            constexpr bool is_monotonic() const;
            constexpr bool is_uniform(double tol = std::numeric_limits<double>::epsilon()) const;
            template <typename T>
            constexpr bool is_always_less_than(T limit) const;
            template <typename T>
            constexpr bool is_always_less_than_or_equal_to(T limit) const;
            template <typename T>
            constexpr bool is_always_greater_than(T limit) const;
            template <typename T>
            constexpr bool is_always_greater_than_or_equal_to(T limit) const;

            //  -- Searching --
            template <typename S>
            size_t lower_index(S val, size_t init_guess = 0) const;
            template <typename S>
            size_t upper_index(S val, size_t init_guess = 1) const;
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec and initialise all of its data elements to zero.
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(data.begin(), data.end(), 0.0);
        }

        /**
         *  Construct a vec and initialise all of its data elements to the given initial value.
         *
         *  @param  init_data    Value to initialise all data elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const double init_data)
        {
            std::fill(data.begin(), data.end(), init_data);
        }

        /**
         *  Construct a vec and initialise all of its data elements using the given array.
         *
         *  @param  init_data    Array of values to initialise the vec data elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const std::array<double, N>& init_data) :
            data(init_data)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to an data element of the vec.
         *
         *  @param  index   Index of the data element to access.
         *
         *  @return A reference to the vec data element.
         */
        template <size_t N>
        constexpr double& Vec<N>::operator[](const size_t index)
        {
            return (data[index]);
        }

        /**
         *  Retrieve a reference to a const data element of the vec.
         *
         *  @param  index   Index of the data element to access.
         *
         *  @return A reference to the const vec data element.
         */
        template <size_t N>
        constexpr const double& Vec<N>::operator[](const size_t index) const
        {
            return (data[index]);
        }


        //  -- Mathematical --
        /**
         *  Add a value to all data elements of a vec.
         *
         *  @param  rhs Value to add to each vec data element.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] += rhs;
            }

            return (*this);
        }

        /**
         *  Add the data element values of another vec to this vec.
         *
         *  @param  rhs Vec of data elements to add to this vec.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const Vec<N>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] += rhs.data[i];
            }

            return (*this);
        }

        /**
         *  Subtract a value from all data elements of a vec.
         *
         *  @param  rhs Value to subtract from each vec data element.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] -= rhs;
            }

            return (*this);
        }

        /**
         *  Subtract the data element values of another vec from this vec.
         *
         *  @param  rhs Vec of data elements to subtract from this vec.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const Vec<N>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] -= rhs.data[i];
            }

            return (*this);
        }

        /**
         *  Multiply all data elements of a vec by a value.
         *
         *  @param  rhs Value to multiply each vec data element by.
         *
         *  @return A reference to this vec post-multiplication.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator*=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] *= rhs;
            }

            return (*this);
        }

        /**
         *  Divide all data elements of a vec by a value.
         *
         *  @param  rhs Value to divide each vec data element by.
         *
         *  @return A reference to this vec post-division.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator/=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] /= rhs;
            }

            return (*this);
        }


        /**
         *  Determine the cross-product of this vec and another given vec.
         *  This vec acts as the left hand side operand.
         *
         *  @param  rhs Vec to perform cross product with.
         *
         *  @pre    N must equal three.
         *
         *  @return A reference to this vec post-operation.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator^=(const Vec<3>& rhs)
        {
            static_assert(N == 3);

            const std::array<double, 3> lhs = data;

            data[X] = (lhs[Y] * rhs[Z]) - (lhs[Z] * rhs[Y]);
            data[Y] = (lhs[Z] * rhs[X]) - (lhs[X] * rhs[Z]);
            data[Z] = (lhs[X] * rhs[Y]) - (lhs[Y] * rhs[X]);

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
                ++data[i];
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
            const Vec<N> vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                ++data[i];
            }

            return (vec);
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
                --data[i];
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
            const Vec<N> vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                --data[i];
            }

            return (vec);
        }

        /**
         *  Create a vec with a copy of the data element values.
         *
         *  @return A copy of this vec with the same data element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator+() const
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec[i] = +data[i];
            }

            return (vec);
        }

        /**
         *  Create a vec with a copy of the negated data element values.
         *
         *  @return A copy of this vec with the negated data element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator-() const
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec[i] = -data[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by adding a given value to the data elements of a given vec.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator+(const Vec<N>& lhs, const double rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] + rhs;
            }

            return (vec);
        }

        /**
         *  Create a new vec by adding the data elements of a given vec to another vec.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator+(const Vec<N>& lhs, const Vec<N>& rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] + rhs.data[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by subtracting a given value form the data elements of a given vec.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator-(const Vec<N>& lhs, const double rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] - rhs;
            }

            return (vec);
        }

        /**
         *  Create a new vec by subtracting the data elements of a given vec from another vec.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator-(const Vec<N>& lhs, const Vec<N>& rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] - rhs.data[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by multiplying data elements of a given vec by a value.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator*(const Vec<N>& lhs, const double rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] * rhs;
            }

            return (vec);
        }

        /**
         *  Determine the dot-product of two vecs.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The dot-product of the vecs.
         */
        template <size_t N>
        constexpr double operator*(const Vec<N>& lhs, const Vec<N>& rhs)
        {
            double prod = 0.0;

            for (size_t i = 0; i < N; ++i)
            {
                prod += lhs.data[i] * rhs.data[i];
            }

            return (prod);
        }

        /**
         *  Create a new vec by dividing data elements of a given vec by a value.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side value operand.
         *
         *  @return The created vec.
         */
        template <size_t N>
        constexpr Vec<N> operator/(const Vec<N>& lhs, const double rhs)
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec.data[i] = lhs.data[i] / rhs;
            }

            return (vec);
        }

        /**
         *  Determine the cross-product of two vecs.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The cross-product of the vecs.
         */
        constexpr Vec<3> operator^(const Vec<3>& lhs, const Vec<3>& rhs)
        {
            Vec<3> prod;

            prod.data[X] = (lhs.data[Y] * rhs.data[Z]) - (lhs.data[Z] * rhs.data[Y]);
            prod.data[Y] = (lhs.data[Z] * rhs.data[X]) - (lhs.data[X] * rhs.data[Z]);
            prod.data[Z] = (lhs.data[X] * rhs.data[Y]) - (lhs.data[Y] * rhs.data[X]);

            return (prod);
        }


        //  -- Printing --
        /**
         *  Enable printing of a vec to a given ostream.
         *
         *  @param  stream  Stream to write to.
         *  @param  vec     Vec to be written.
         *
         *  @return A reference to the stream post-write.
         */
        template <size_t N>
        std::ostream& operator<<(std::ostream& stream, const Vec<N>& vec)
        {
            if (N == 0)
            {
                stream << "⟨⟩";

                return (stream);
            }

            stream << "⟨" << vec.data[0];
            for (size_t i = 1; i < N; ++i)
            {
                stream << ", " << vec.data[i];
            }
            stream << "⟩";

            return (stream);
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

            return (utl::min_index(data));
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

            return (utl::max_index(data));
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

            return (utl::min(data));
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

            return (utl::max(data));
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
            return (utl::total(data));
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
            return (utl::magnitude(data));
        }

        /**
         *  Normalise the vec by deviding each data element by the magnitude of the total vec.
         */
        template <size_t N>
        constexpr void Vec<N>::normalise()
        {
            const double mag = utl::magnitude(data);

            for (size_t i = 0; i < N; ++i)
            {
                data[i] /= mag;
            }

            assert(is_normalised());
        }


        //  -- Properties --
        /**
         *  Determine if the vec is normalised to within a given tolerance.
         *
         *  @param  tol Maximum deviation from unity where vec is considered uniform.
         *
         *  @return True if the vec's magnitude is equal to one within the given tolerance.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_normalised(const double tol) const
        {
            return (std::fabs(utl::magnitude(data) - 1.0) <= tol);
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

            return (utl::is_ascending(data));
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

            return (utl::is_descending(data));
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

            return (utl::is_monotonic(data));
        }

        /**
         *  Determine if the vec's data elements are uniformly separated to within a given tolerance.
         *  Vec must contain at more than one data element.
         *
         *  @param  tol Maximum consecutive delta difference from the average delta where vec is considered uniform.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's data elements are uniformly spaced.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_uniform(const double tol) const
        {
            static_assert(N > 1);

            return (utl::is_uniform(data, tol));
        }

        /**
         *  Determine if a given vec's data elements are always less than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's data elements are all less than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than(const T limit) const
        {
            return (utl::is_always_less_than(data, limit));
        }

        /**
         *  Determine if a given vec's data elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's data elements are all less than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than_or_equal_to(const T limit) const
        {
            return (utl::is_always_less_than_or_equal_to(data, limit));
        }

        /**
         *  Determine if the vec's data elements are always greater than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's data elements are all greater than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than(const T limit) const
        {
            return (utl::is_always_greater_than(data, limit));
        }

        /**
         *  Determine if the vec's data elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's data elements are all greater than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than_or_equal_to(const T limit) const
        {
            return (utl::is_always_greater_than_or_equal_to(data, limit));
        }


        //  -- Searching --
        /**
         *  Determine the lower index of the data element pair which encapsulates the given value.
         *  If the value is equal to an data element of the vec then the lower index is that index, unless it is the last data element.
         *
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  val         Value to locate within the vec.
         *  @param  init_guess  Initial guess for the upper index.
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
        size_t Vec<N>::lower_index(const S val, const size_t init_guess) const
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(data));
            assert(((val >= data.front()) && (val <= data.back())) || ((val <= data.front()) && (val >= data.back())));
            assert(init_guess < N);

            return (utl::lower_index(data, val, init_guess));
        }

        /**
         *  Determine the upper index of the data element pair which encapsulates the given value.
         *  If the value is equal to an data element of the vec then the upper index is that index, unless it is the first data element.
         *
         *  @tparam S   Type of the value to be found within the array.
         *
         *  @param  val         Value to locate within the vec.
         *  @param  init_guess  Initial guess for the upper index.
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
        size_t Vec<N>::upper_index(const S val, const size_t init_guess) const
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(data));
            assert(((val >= data.front()) && (val <= data.back())) || ((val <= data.front()) && (val >= data.back())));
            assert(init_guess < N);

            return (utl::upper_index(data, val, init_guess));
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
