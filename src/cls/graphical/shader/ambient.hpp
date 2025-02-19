/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP



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
            constexpr const char* AMBIENT_SHADER_DIR = "ambient/";  //! Path to the ambient shader directory.



            //  == CLASS ==
            /**
             *  Ambient lighting shader.
             *  Props are uniformly luminescent.
             */
            class Ambient : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_mvp_uni;  //! Model-view-projection uniform handle.
                const GLint m_col_uni;  //! Colour uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Ambient();


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_mvp_uni() const { return (m_mvp_uni); }
                GLint get_col_uni() const { return (m_col_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP



//  == MODULE END ==
#endif
