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
            std::array<double, N> elements; //! Array of element values.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            constexpr Vec();


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
         * @tparam N
         */
        template <size_t N>
        constexpr Vec<N>::Vec()
        {
            std::fill(elements.begin(), elements.end(), 0.0);
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
            return (elements[index]);
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
            return (elements[index]);
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

            stream << "⟨" << vec[0];
            for (size_t i = 1; i < M; ++i)
            {
                stream << ", " << vec[i];
            }
            stream << "⟩";

            return (stream);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC_HPP
