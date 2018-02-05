/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



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
             *
             *  @param  t_path  Path to the directory containing the diffuse sub-shader programs.
             */
            Skybox::Skybox(const std::string& t_path) :
                Shader(t_path, false),
                m_view_uni(init_uniform("view")),
                m_proj_uni(init_uniform("proj")),
                m_skybox_uni(init_uniform("skybox"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
