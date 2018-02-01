/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



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
                Ambient(const std::string& t_geom_serial, const std::string& t_vert_serial, const std::string& t_frag_serial);


                //  == METHODS ==
              private:
                //  -- Getters --
                GLint get_mvp_uni() const { return (m_mvp_uni); }
                GLint gem_col_uni() const { return (m_col_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
