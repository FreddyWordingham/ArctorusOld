/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
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



            //  == CLASS ==
            /**
             *  Specialisation of the shader class for ambient lighting.
             */
            class Diffuse : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_mvp_uni;      //! Model-view-projection uniform handle.
                const GLint m_view_uni;     //! View matrix uniform handle.
                const GLint m_col_uni;      //! Colour uniform handle.
                const GLint m_sun_pos_uni;  //! Sun position uniform handle.
                const GLint m_amb_pow_uni;  //! Ambient lighting uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --

              private:
                //  -- Initialisation --


                //  == OPERATORS ==
              private:


                //  == METHODS ==
              private:
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP
