/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_SKYBOX_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_SKYBOX_HPP



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
             *  Shader used to display skyboxes.
             */
            class Skybox : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_view_uni;     //! View matrix uniform handle.
                const GLint m_proj_uni;     //! Projetion matrix uniform handle.
                const GLint m_skybox_uni;   //! Skybox uniform handle.



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
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_SKYBOX_HPP
