/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/ambient.hpp"



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
             *  Construct an ambient shader.
             *
             *  @param  t_path  Path to the directory containing the ambient sub-shader programs.
             */
            Ambient::Ambient(const std::string& t_path) :
                Shader(t_path, false),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
