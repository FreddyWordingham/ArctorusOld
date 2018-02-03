/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/skybox.hpp"



//  == INCLUDES ==
//  -- System --



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
             *
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_geom_serial   Serialised source code of the geometry shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Skybox::Skybox(const std::string& t_vert_serial, const std::string& t_geom_serial,
                           const std::string& t_frag_serial) :
                Shader(t_vert_serial, t_geom_serial, t_frag_serial),
                m_view_uni(init_uniform("view")),
                m_proj_uni(init_uniform("proj")),
                m_skybox_uni(init_uniform("skybox"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
