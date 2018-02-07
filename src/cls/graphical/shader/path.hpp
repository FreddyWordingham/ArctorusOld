/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_PATH_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_PATH_HPP



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
            constexpr const char* PATH_SHADER_DIR = "path/";    //! Path to the path shader directory.



            //  == CLASS ==
            /**
             *  Path shader.
             */
            class Path : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_mvp_uni;  //! Model-view-projection uniform handle.
                const GLint m_col_uni;  //! Colour uniform handle.
                const GLint m_time_uni; //! Render distance uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Path();


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_mvp_uni() const { return (m_mvp_uni); }
                GLint get_col_uni() const { return (m_col_uni); }
                GLint get_time_uni() const { return (m_time_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_PATH_HPP
