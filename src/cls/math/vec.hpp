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
            explicit constexpr Vec(double init_elements);
            explicit constexpr Vec(const std::initializer_list<double>& init_elements);


            //  == OPERATORS ==
          private:
            //  -- Access --
            constexpr double& operator[](size_t index);
            constexpr const double& operator[](size_t index) const;

            //  -- Printing --
            template <size_t M>
            friend std::ostream& operator<<(std::ostream& stream, const Vec<M>& vec);



            //  == METHODS ==
          private:
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
         *  Construct a vec and initialise all of its elements using the given initialiser list.
         *
         *  @tparam N   Size of the vec.
         *
         *  @param  init_element    List of values to initialise the vec elements to.
         *
         *  @post   All elements of the vec must vec must have been initialised.
         */
        template <size_t N>
        constexpr Vec<N>::Vec(const std::initializer_list<double>& init_element)
        {
            size_t            i = 0;
            for (const double val : init_element)
            {
                element[i] = val;
                ++i;
            }

            assert(i == N);
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


        //  -- Printing --
        /**
         *  Enable printing of a vec to a given ostream.
         *
         *  @tparam M   Size of the vec.
         *
         *  @param  stream  Stream to write to.
         *  @param  vec     Vec to be written.
         *
         *  @return A reference to the stream post-write.
         */
        template <size_t M>
        std::ostream& operator<<(std::ostream& stream, const Vec<M>& vec)
        {
            if (M == 0)
            {
                stream << "⟨⟩";

                return (stream);
            }

            stream << "⟨" << vec.element[0];
            for (size_t i = 1; i < M; ++i)
            {
                stream << ", " << vec.element[i];
            }
            stream << "⟩";

            return (stream);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
