/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a shader object from
         *
         *  @param  t_vert_serial   Source code of the vertex shader.
         *  @param  t_frag_serial   Source code of the fragment shader.
         */
        Shader::Shader(const std::string& t_vert_serial, const std::string& t_frag_serial) :
            m_handle(init_handle(t_vert_serial, t_frag_serial)),
            m_mvp(init_uniform())
        {
        }


        //  -- Initialisation --



    } // namespace graphical
} // namespace arc
