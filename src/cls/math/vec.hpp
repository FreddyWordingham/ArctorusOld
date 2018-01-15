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
            std::array<double, N> element;  //! Array of element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();
            explicit constexpr Vec(double init_element);
            explicit constexpr Vec(const std::array<double, N>& init_element);


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
            template <size_t V>
            friend constexpr Vec<V> operator+(const Vec<V>& lhs, double rhs);
            template <size_t V>
            friend constexpr Vec<V> operator+(const Vec<V>& lhs, const Vec<V>& rhs);
            template <size_t V>
            friend constexpr Vec<V> operator-(const Vec<V>& lhs, double rhs);
            template <size_t V>
            friend constexpr Vec<V> operator-(const Vec<V>& lhs, const Vec<V>& rhs);
            template <size_t V>
            friend constexpr Vec<V> operator*(const Vec<V>& lhs, double rhs);
            template <size_t V>
            friend constexpr double operator*(const Vec<V>& lhs, const Vec<V>& rhs);
            template <size_t V>
            friend constexpr Vec<V> operator/(const Vec<V>& lhs, double rhs);
            friend constexpr Vec<3> operator^(const Vec<3>& lhs, const Vec<3>& rhs);

            //  -- Printing --
            template <size_t V>
            friend std::ostream& operator<<(std::ostream& stream, const Vec<V>& vec);



            //  == METHODS ==
          private:
            //  -- Mathematical --
            constexpr size_t min_index(const Vec<N>& vec);
            constexpr size_t max_index(const Vec<N>& vec);
            constexpr double min(const Vec<N>& vec);
            constexpr double max(const Vec<N>& vec);
            constexpr double total(const Vec<N>& vec);
            constexpr double magnitude(const Vec<N>& vec);

            //  -- Properties --
            constexpr bool is_ascending();
            constexpr bool is_descending();
            constexpr bool is_monotonic();
            constexpr bool is_uniform(double tol = std::numeric_limits<double>::epsilon());
            template <typename T>
            constexpr bool is_always_less_than(T limit);
            template <typename T>
            constexpr bool is_always_less_than_or_equal_to(T limit);
            template <typename T>
            constexpr bool is_always_greater_than(T limit);
            template <typename T>
            constexpr bool is_always_greater_than_or_equal_to(T limit);

            //  -- Searching --
            template <typename S>
            size_t lower_index(S val, size_t init_guess = 0);
            template <typename S>
            size_t upper_index(S val, size_t init_guess = 1);
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec and initialise all of its elements to zero.
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(element.begin(), element.end(), 0.0);
        }

        /**
         *  Construct a vec and initialise all of its elements to the given initial value.
         *
         *  @param  init_element    Value to initialise all elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const double init_element)
        {
            std::fill(element.begin(), element.end(), init_element);
        }

        /**
         *  Construct a vec and initialise all of its elements using the given array.
         *
         *  @param  init_element    Array of values to initialise the vec elements to.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const std::array<double, N>& init_element) :
            element(init_element)
        {
        }



        //  == OPERATORS ==
        //  -- Access --
        /**
         *  Retrieve a reference to an element of the vec.
         *
         *  @param  index   Index of the element to access.
         *
         *  @return A reference to the vec element.
         */
        template <size_t N>
        constexpr double& Vec<N>::operator[](const size_t index)
        {
            return (element[index]);
        }

        /**
         *  Retrieve a reference to a const element of the vec.
         *
         *  @param  index   Index of the element to access.
         *
         *  @return A reference to the const vec element.
         */
        template <size_t N>
        constexpr const double& Vec<N>::operator[](const size_t index) const
        {
            return (element[index]);
        }


        //  -- Mathematical --
        /**
         *  Add a value to all elements of a vec.
         *
         *  @param  rhs Value to add to each vec element.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] += rhs;
            }

            return (*this);
        }

        /**
         *  Add the element values of another vec to this vec.
         *
         *  @param  rhs Vec of elements to add to this vec.
         *
         *  @return A reference to this vec post-addition.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator+=(const Vec<N>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] += rhs.element[i];
            }

            return (*this);
        }

        /**
         *  Subtract a value from all elements of a vec.
         *
         *  @param  rhs Value to subtract from each vec element.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] -= rhs;
            }

            return (*this);
        }

        /**
         *  Subtract the element values of another vec from this vec.
         *
         *  @param  rhs Vec of elements to subtract from this vec.
         *
         *  @return A reference to this vec post-subtraction.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator-=(const Vec<N>& rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] -= rhs.element[i];
            }

            return (*this);
        }

        /**
         *  Multiply all elements of a vec by a value.
         *
         *  @param  rhs Value to multiply each vec element by.
         *
         *  @return A reference to this vec post-multiplication.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator*=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] *= rhs;
            }

            return (*this);
        }

        /**
         *  Divide all elements of a vec by a value.
         *
         *  @param  rhs Value to divide each vec element by.
         *
         *  @return A reference to this vec post-division.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator/=(const double rhs)
        {
            for (size_t i = 0; i < N; ++i)
            {
                element[i] /= rhs;
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

            const std::array<double, 3> lhs = element;

            element[X] = (lhs[Y] * rhs[Z]) - (lhs[Z] * rhs[Y]);
            element[Y] = (lhs[Z] * rhs[X]) - (lhs[X] * rhs[Z]);
            element[Z] = (lhs[X] * rhs[Y]) - (lhs[Y] * rhs[X]);

            return (*this);
        }

        /**
         *  Increment each element stored by the vec.
         *
         *  @return A reference to this vec post-increment.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator++()
        {
            for (size_t i = 0; i < N; ++i)
            {
                ++element[i];
            }

            return (*this);
        }

        /**
         *  Increment each element stored by the vec.
         *
         *  @return A copy of this vec post-increment.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator++(const int /*unused*/)
        {
            const Vec<N> vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                ++element[i];
            }

            return (vec);
        }

        /**
         *  Decrement each element stored by the vec.
         *
         *  @return A reference to this vec post-decrement.
         */
        template <size_t N>
        constexpr Vec<N>& Vec<N>::operator--()
        {
            for (size_t i = 0; i < N; ++i)
            {
                --element[i];
            }

            return (*this);
        }

        /**
         *  Decrement each element stored by the vec.
         *
         *  @return A copy of this vec post-decrement.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator--(const int /*unused*/)
        {
            const Vec<N> vec = *this;

            for (size_t i = 0; i < N; ++i)
            {
                --element[i];
            }

            return (vec);
        }

        /**
         *  Create a vec with a copy of the element values.
         *
         *  @return A copy of this vec with the same element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator+() const
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec[i] = +element[i];
            }

            return (vec);
        }

        /**
         *  Create a vec with a copy of the negated element values.
         *
         *  @return A copy of this vec with the negated element values.
         */
        template <size_t N>
        constexpr Vec<N> Vec<N>::operator-() const
        {
            Vec<N> vec;

            for (size_t i = 0; i < N; ++i)
            {
                vec[i] = -element[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by adding a given value to the elements of a given vec.
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
                vec.element[i] = lhs.element[i] + rhs;
            }

            return (vec);
        }

        /**
         *  Create a new vec by adding the elements of a given vec to another vec.
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
                vec.element[i] = lhs.element[i] + rhs.element[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by subtracting a given value form the elements of a given vec.
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
                vec.element[i] = lhs.element[i] - rhs;
            }

            return (vec);
        }

        /**
         *  Create a new vec by subtracting the elements of a given vec from another vec.
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
                vec.element[i] = lhs.element[i] - rhs.element[i];
            }

            return (vec);
        }

        /**
         *  Create a new vec by multiplying elements of a given vec by a value.
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
                vec.element[i] = lhs.element[i] * rhs;
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
                prod += lhs.element[i] * rhs.element[i];
            }

            return (prod);
        }

        /**
         *  Create a new vec by dividing elements of a given vec by a value.
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
                vec.element[i] = lhs.element[i] / rhs;
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

            prod.element[X] = (lhs.element[Y] * rhs.element[Z]) - (lhs.element[Z] * rhs.element[Y]);
            prod.element[Y] = (lhs.element[Z] * rhs.element[X]) - (lhs.element[X] * rhs.element[Z]);
            prod.element[Z] = (lhs.element[X] * rhs.element[Y]) - (lhs.element[Y] * rhs.element[X]);

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

            stream << "⟨" << vec.element[0];
            for (size_t i = 1; i < N; ++i)
            {
                stream << ", " << vec.element[i];
            }
            stream << "⟩";

            return (stream);
        }



        //  == METHODS ==
        //  -- Mathematical --
        /**
        *  Find the index of the vec which holds the smallest element.
        *  If multiple vec elements are equally the smallest, the index of the first will be returned.
        *
        *  @param  vec vec to search.
        *
        *  @pre    N must not be zero.
        *
        *  @return The index of the smallest element within the vec.
        */
        template <size_t N>
        constexpr size_t Vec<N>::min_index(const Vec<N>& vec)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (vec[i] < vec[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
        *  Find the index of the vec which holds the largest element.
        *  If multiple vec elements are equally the largest, the index of the first will be returned.
        *
        *  @param  vec Vec to search.
        *
        *  @pre    N must not be zero.
        *
        *  @return The index of the largest element within the vec.
        */
        template <size_t N>
        constexpr size_t Vec<N>::max_index(const Vec<N>& vec)
        {
            static_assert(N != 0);

            size_t index = 0;

            for (size_t i = 1; i < N; ++i)
            {
                if (vec[i] > vec[index])
                {
                    index = i;
                }
            }

            return (index);
        }

        /**
         *  Create a copy of the smallest element within a given vec.
         *
         *  @param  vec Vec to copy the minimum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the smallest value within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::min(const Vec<N>& vec)
        {
            static_assert(N != 0);

            return (vec[min_index(vec)]);
        }

        /**
         *  Create a copy of the largest element within a given vec.
         *
         *  @param  vec Vec to copy the maximum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the largest value within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::max(const Vec<N>& vec)
        {
            static_assert(N != 0);

            return (vec[max_index(vec)]);
        }

        /**
         *  Determine the total of all elements stored within a given vec.
         *  Empty vecs are considered to have a total of zero.
         *
         *  @param  vec Vec to find the total of.
         *
         *  @return The total of all elements stored within the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::total(const Vec<N>& vec)
        {
            double total = 0.0;

            for (size_t i = 0; i < N; ++i)
            {
                total += vec[i];
            }

            return (total);
        }

        /**
         *  Determine the magnitude of the given vec.
         *  Empty vecs are considered to have a magnitude of zero.
         *
         *  @param  vec Vec to find the magnitude of.
         *
         *  @return The magnitude of the vec.
         */
        template <size_t N>
        constexpr double Vec<N>::magnitude(const Vec<N>& vec)
        {
            double squared_total = 0.0;

            for (size_t i = 0; i < N; ++i)
            {
                squared_total += vec[i] * vec[i];
            }

            return (std::sqrt(squared_total));
        }


        //  -- Properties --
        /**
         *  Determine if the vec's elements are sorted in ascending order.
         *  Vec is not considered ascending if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's elements are sorted in ascending order.
        */
        template <size_t N>
        constexpr bool Vec<N>::is_ascending()
        {
            static_assert(N > 1);

            return (utl::is_ascending(element));
        }

        /**
         *  Determine if the vec's elements are sorted in descending order.
         *  Vec is not considered descending if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's elements are sorted in descending order.
        */
        template <size_t N>
        constexpr bool Vec<N>::is_descending()
        {
            static_assert(N > 1);

            return (utl::is_descending(element));
        }

        /**
         *  Determine if the vec's elements are sorted in monotonic order.
         *  Determine if the vec's elements are sorted in ascending or descending order.
         *  Vec is not considered monotonic if two consecutive values are equal.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's elements are sorted in monotonic order.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_monotonic()
        {
            static_assert(N > 1);

            return (utl::is_monotonic(element));
        }

        /**
         *  Determine if the vec's elements are uniformly separated to within a given tolerance.
         *  Vec must contain at more than one element.
         *
         *  @param  tol Maximum consecutive delta difference from the average delta where vec is considered uniform.
         *
         *  @pre    N must be greater than one.
         *
         *  @return True if the vec's elements are uniformly spaced.
         */
        template <size_t N>
        constexpr bool Vec<N>::is_uniform(const double tol)
        {
            static_assert(N > 1);

            return (utl::is_uniform(element, tol));
        }

        /**
         *  Determine if a given vec's elements are always less than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's elements are all less than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than(const T limit)
        {
            return (utl::is_always_less_than(element, limit));
        }

        /**
         *  Determine if a given vec's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's elements are all less than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_less_than_or_equal_to(const T limit)
        {
            return (utl::is_always_less_than_or_equal_to(element, limit));
        }

        /**
         *  Determine if the vec's elements are always greater than a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's elements are all greater than the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than(const T limit)
        {
            return (utl::is_always_greater_than(element, limit));
        }

        /**
         *  Determine if the vec's elements are always less than, or equal to, a given limit.
         *
         *  @tparam T   Type of the limit.
         *
         *  @param  limit   Limit to be tested.
         *
         *  @return True if the vec's elements are all greater than, or equal to, the given limit.
         */
        template <size_t N>
        template <typename T>
        constexpr bool Vec<N>::is_always_greater_than_or_equal_to(const T limit)
        {
            return (utl::is_always_greater_than_or_equal_to(element, limit));
        }


        //  -- Searching --
        /**
         *  Determine the lower index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the vec then the lower index is that index, unless it is the last element.
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
         *  @return The upper index of the element pair which encapsulates the value.
         */
        template <size_t N>
        template <typename S>
        size_t Vec<N>::lower_index(const S val, const size_t init_guess)
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(element));
            assert(
                ((val >= element.front()) && (val <= element.back())) || ((val <= element.front()) && (val >= element.back())));
            assert(init_guess < N);

            return (utl::lower_index(element, val, init_guess));
        }

        /**
         *  Determine the upper index of the element pair which encapsulates the given value.
         *  If the value is equal to an element of the vec then the upper index is that index, unless it is the first element.
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
         *  @return The upper index of the element pair which encapsulates the value.
         */
        template <size_t N>
        template <typename S>
        size_t Vec<N>::upper_index(const S val, const size_t init_guess)
        {
            static_assert(N > 1);
            assert(utl::is_monotonic(element));
            assert(
                ((val >= element.front()) && (val <= element.back())) || ((val <= element.front()) && (val >= element.back())));
            assert(init_guess < N);

            return (utl::upper_index(element, val, init_guess));
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
