/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP



//  == BASE CLASS ==
#include "cls/graphical/shader.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == SETTINGS ==
            //  -- Uniforms --
            constexpr const char* PROP_COL_UNIFORM_NAME = "prop_col";   //! Name of the prop colour uniform within the shader.



            //  == CLASS ==
            /**
             *  Specialisation of the shader class for ambient lighting.
             */
            class Ambient : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_prop_col; //! Prop colour uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Ambient(const std::string& t_vert_serial, const std::string& t_frag_serial);


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_prop_col() const { return (m_prop_col); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
