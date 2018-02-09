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
             *  @param  t_power Power of the light.
             *  @param  t_col   Colour of the prop.
             *
             *  @post   t_power must be greater than zero.
             */
            Light::Light(const std::vector<Vertex>& t_vert, const float t_power, const glm::vec4& t_col) :
                Prop(t_vert, t_col),
                m_power(t_power)
            {
                assert(t_power > 0.0f);
            }



        } // namespace prop
    } // namespace graphical
} // namespace arc
