/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/03/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MATH_VEC3_HPP
#define ARCTORUS_SRC_CLS_MATH_VEC3_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == CLASS ==
        /**
         *  Three-dimensional mathematical vector class.
         *  Acts as a mathematical vector of double values.
         *  Should not be used for general purpose storage.
         */
        class vec3
        {
            //  == FIELDS ==
          public:
            //  -- Data --
            double x;   //! X-dimension value.
            double y;   //! Y-dimension value.
            double z;   //! Z-dimension value.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit constexpr vec3() noexcept;
            constexpr vec3(double t_x, double t_y, double t_z) noexcept;


            //  == OPERATORS ==
          public:
            //  -- Mathematical --
            constexpr vec3& operator+=(double t_rhs) noexcept;
            constexpr vec3& operator+=(const vec3& t_rhs) noexcept;
            constexpr vec3& operator-=(double t_rhs) noexcept;
            constexpr vec3& operator-=(const vec3& t_rhs) noexcept;
            constexpr vec3& operator*=(double t_rhs) noexcept;
            constexpr vec3& operator/=(double t_rhs) noexcept;
            constexpr vec3& operator^=(const vec3& t_rhs) noexcept;


            //  == METHODS ==
          private:
        };



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vec3 with values initialised to zero.
         */
        constexpr vec3::vec3() noexcept :
            x(0.0),
            y(0.0),
            z(0.0)
        {
        }

        /**
         *  Construct a vec3 with initialised values.
         *
         *  @param  t_x Value to initialise the x-dimension data element to.
         *  @param  t_y Value to initialise the y-dimension data element to.
         *  @param  t_z Value to initialise the z-dimension data element to.
         */
        constexpr vec3::vec3(const double t_x, const double t_y, const double t_z) noexcept :
            x(t_x),
            y(t_y),
            z(t_z)
        {
        }



        //  == OPERATORS ==
        //  -- Mathematical --
        /**
         *  Add a value to all data elements of the vec.
         *
         *  @param  t_rhs   Value to add to each vec data element.
         *
         *  @return A reference to this vec post-addition.
         */
        constexpr vec3& vec3::operator+=(const double t_rhs) noexcept
        {
            x += t_rhs;
            y += t_rhs;
            z += t_rhs;

            return (*this);
        }

        /**
         *  Add the data element values of another vec to this vec.
         *
         *  @param  t_rhs   Vec of data elements to add to this vec.
         *
         *  @return A reference to this vec post-addition.
         */
        constexpr vec3& vec3::operator+=(const vec3& t_rhs) noexcept
        {
            x += t_rhs.x;
            y += t_rhs.y;
            z += t_rhs.z;

            return (*this);
        }



    } // namespace math
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MATH_VEC3_HPP
