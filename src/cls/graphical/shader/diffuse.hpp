/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP



//  == BASE CLASS ==
#include "cls/graphical/shader.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == SETTINGS ==
            //  -- Uniforms --
            constexpr const char* VIEW_MAT_UNIFORM_NAME  = "view";       //! Name of the view matrix uniform.
            constexpr const char* PROP_COL_UNIFORM_NAME  = "prop_col";   //! Name of the prop colour uniform.
            constexpr const char* LIGHT_POS_UNIFORM_NAME = "light_pos";  //! Name of the light position uniform.



            //  == CLASS ==
            /**
             *  Specialisation of the shader class for diffuse spotlight lighting.
             */
            class Diffuse : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_prop_col; //! Prop colour uniform handle.
                const GLint m_prop_col; //! Prop colour uniform handle.
                const GLint m_prop_col; //! Prop colour uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Diffuse(const std::string& t_vert_serial, const std::string& t_frag_serial);


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_prop_col() const { return (m_prop_col); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP
