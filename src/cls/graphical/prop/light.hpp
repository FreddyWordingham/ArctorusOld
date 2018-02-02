/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
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
             *  Light prop.
             */
            class Light : public Prop
            {
                //  == FIELDS ==
              private:
                //  -- Properties --
                const float m_power;    //! Power of the light source.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Light(const std::vector<Vertex>& t_vert, const glm::vec4& t_col, const float t_power);


                //  == METHODS ==
              public:
                //  -- Getters --
                float get_power() const { return (m_power); }
            };



        } // namespace prop
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_LIGHT_HPP
