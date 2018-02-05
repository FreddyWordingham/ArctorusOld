/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/photon.hpp"



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
             *  Construct a photon shader.
             *
             *  @param  t_path  Path to the directory containing the diffuse sub-shader programs.
             */
            Photon::Photon(const std::string& t_path) :
                Shader(t_path, false),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col")),
                m_render_dist_uni(init_uniform("render_dist"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
