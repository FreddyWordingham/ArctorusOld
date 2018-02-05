/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/diffuse.hpp"



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
             *  Construct a diffuse shader.
             *
             *  @param  t_path  Path to the directory containing the diffuse sub-shader programs.
             */
            Diffuse::Diffuse(const std::string& t_path) :
                Shader(t_path, false),
                m_mvp_uni(init_uniform("mvp")),
                m_view_uni(init_uniform("view")),
                m_col_uni(init_uniform("col")),
                m_sun_pos_uni(init_uniform("sun_pos")),
                m_amb_pow_uni(init_uniform("amb_pow"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
