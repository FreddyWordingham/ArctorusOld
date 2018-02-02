/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/prop/light.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace prop
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a light prop to be rendered.
             *
             *  @param  t_vert  Vector of vertices forming the prop.
             *  @param  t_col   Colour of the prop.
             *  @param  t_power Power of the light.
             */
            Light::Light(const std::vector<Vertex>& t_vert, const glm::vec4& t_col, const float t_power) :
                Prop(t_vert, t_col),
                m_power(t_power)
            {
            }



        } // namespace prop
    } // namespace graphical
} // namespace arc
