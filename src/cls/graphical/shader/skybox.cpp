/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == HEADER ==
#include "cls/graphical/shader/skybox.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a skybox shader.
             */
            Skybox::Skybox() :
                Shader(SKYBOX_SHADER_DIR, false),
                m_view_uni(init_uniform("view")),
                m_proj_uni(init_uniform("proj")),
                m_skybox_uni(init_uniform("skybox"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == MODULE END ==
#endif
