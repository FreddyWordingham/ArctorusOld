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



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == SETTINGS ==
            //  -- Directories --
            constexpr const char* SKYBOX_SHADER_DIR = "skybox/";    //! Path to the skybox shader directory.



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
                Skybox();


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_view_uni() const { return (m_view_uni); }
                GLint get_proj_uni() const { return (m_proj_uni); }
                GLint get_skybox_uni() const { return (m_skybox_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_SKYBOX_HPP
