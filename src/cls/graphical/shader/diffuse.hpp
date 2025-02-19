/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP



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
            constexpr const char* DIFFUSE_SHADER_DIR = "diffuse/";  //! Path to the diffuse shader directory.



            //  == CLASS ==
            /**
             *  Specialisation of the shader class for ambient lighting.
             */
            class Diffuse : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_mvp_uni;      //! Model-view-projection uniform handle.
                const GLint m_view_uni;     //! View matrix uniform handle.
                const GLint m_col_uni;      //! Colour uniform handle.
                const GLint m_sun_pos_uni;  //! Sun position uniform handle.
                const GLint m_amb_pow_uni;  //! Ambient lighting uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Diffuse();


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_mvp_uni() const { return (m_mvp_uni); }
                GLint get_view_uni() const { return (m_view_uni); }
                GLint get_col_uni() const { return (m_col_uni); }
                GLint get_sun_pos_uni() const { return (m_sun_pos_uni); }
                GLint get_amb_pow_uni() const { return (m_amb_pow_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_DIFFUSE_HPP



//  == MODULE END ==
#endif
