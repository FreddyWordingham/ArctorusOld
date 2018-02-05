/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_NORMAL_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_NORMAL_HPP



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
             *  Specialised shader drawing prop normals.
             */
            class Normal : public Shader
            {
                //  == FIELDS ==
              private:
                //  -- Uniforms --
                const GLint m_mvp_uni;          //! Model-view-projection uniform handle.
                const GLint m_col_uni;          //! Colour uniform handle.
                const GLint m_light_power_uni;  //! Light power uniform handle.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                explicit Normal(const std::string& t_path);


                //  == METHODS ==
              public:
                //  -- Getters --
                GLint get_mvp_uni() const { return (m_mvp_uni); }
                GLint get_col_uni() const { return (m_col_uni); }
                GLint get_light_power_uni() const { return (m_light_power_uni); }
            };



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_NORMAL_HPP
