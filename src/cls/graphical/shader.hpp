/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Base shader class.
         *  Complex shaders should be derived from this base class.
         */
        class Shader
        {
            //  == FIELDS ==
          private:
            //  -- Program --
            const GLuint m_handle;  //! Handle to the compiled shader program.

            //  -- Uniforms --
            const GLint m_mvp;  //! Model-view-projection uniform handle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Shader(const std::string& t_vert_serial, const std::string& t_frag_serial);

          private:
            //  -- Initialisation --


            //  == METHODS ==
          private:
            //  -- Getters --
            GLuint get_handle() const { return (m_handle); }
            GLuint get_mvp() const { return (m_mvp); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP
