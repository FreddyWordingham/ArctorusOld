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



//  == INCLUDES ==
//  -- System --



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
                const float m_pow;  //! Power of the light source.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Prop(const std::vector<Vertex>& t_vert, const glm::vec4& t_col, const float t_power);


                //  == METHODS ==
              public:
                //  -- Getters --
                float get_float() const { return (m_pow); }
            };



        } // namespace prop
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_LIGHT_HPP
