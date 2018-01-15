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



            //  == FUNCTION PROTOTYPES ==
            //  -- Mathematical --
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec and initialise all of its elements to zero.
         *
         *  @tparam N   Size of the vec.
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(element.begin(), element.end(), 0.0);
        }

        /**
         *  Construct a vec and initialise all of its elements to the given initial value.
         *
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  @tparam N   Size of the vec.
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
         *  Determine the dot-product of two vectors.
         *
         *  @tparam N   Size of the vec.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The dot-product of the vectors.
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
         *  @tparam N   Size of the vec.
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
         *  Determine the cross-product of two vectors.
         *
         *  @param  lhs Left hand side vec operand.
         *  @param  rhs Right hand side vec operand.
         *
         *  @return The cross-product of the vectors.
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
         *  @tparam N   Size of the vec.
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
        *  Find the index of the Vec which holds the smallest element.
        *  If multiple Vec elements are equally the smallest, the index of the first will be returned.
        *
        *  @tparam N   Size of the Vec.
        *
        *  @param  vec Vec to search.
        *
        *  @pre    N must not be zero.
        *
        *  @return The index of the smallest element within the Vec.
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
        *  Find the index of the Vec which holds the largest element.
        *  If multiple Vec elements are equally the largest, the index of the first will be returned.
        *
        *  @tparam N   Size of the Vec.
        *
        *  @param  vec Vec to search.
        *
        *  @pre    N must not be zero.
        *
        *  @return The index of the largest element within the Vec.
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
         *  Create a copy of the smallest element within a given Vec.
         *
         *  @tparam N   Size of the Vec.
         *
         *  @param  vec Vec to copy the minimum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the smallest value within the Vec.
         */
        template <size_t N>
        constexpr double Vec<N>::min(const Vec<N>& vec)
        {
            static_assert(N != 0);

            return (vec[min_index(vec)]);
        }

        /**
         *  Create a copy of the largest element within a given Vec.
         *
         *  @tparam N   Size of the Vec.
         *
         *  @param  vec Vec to copy the maximum value of.
         *
         *  @pre    N must not be zero.
         *
         * @return  A copy of the largest value within the Vec.
         */
        template <size_t N>
        constexpr double Vec<N>::max(const Vec<N>& vec)
        {
            static_assert(N != 0);

            return (vec[max_index(vec)]);
        }

        /**
         *  Determine the total of all elements stored within a given Vec.
         *  Empty Vecs are considered to have a total of zero.
         *
         *  @tparam N   Size of the Vec.
         *
         *  @param  vec Vec to find the total of.
         *
         *  @return The total of all elements stored within the Vec.
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
         *  Determine the magnitude of the given Vec.
         *  Empty Vecs are considered to have a magnitude of zero.
         *
         *  @tparam N   Size of the vec.
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



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
