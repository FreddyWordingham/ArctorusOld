/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_PROP_LIGHT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_PROP_LIGHT_HPP



//  == BASE CLASS ==
#include "cls/graphical/prop.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace prop
        {



            //  == CLASS ==
            /**
             *  Light prop specialisation.
             *  Holds additional information such as direction and power.
             */
            class Light : public Prop
            {
                //  == FIELDS ==
              private:
                //  -- Properties --
                const glm::vec3 m_pos;      //! Position of the light.
                const glm::vec3 m_dir;      //! Direction of the light.
                const float     m_radius;   //! Radius of the light.
                const float     m_aperture; //! Numerical aperture of the light.
                const float     m_power;    //! Power of the light.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Light(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, float t_rad, float t_aperture, float t_power,
                      const glm::vec3& t_col);
            };



        } // namespace prop
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_LIGHT_HPP
