/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_PROP_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_PROP_HPP



//  == INCLUDES ==
//  -- System --
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

//  -- Classes --
#include "cls/graphical/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  A class containing all information required to draw a prop.
         */
        class Prop
        {
            //  == ENUMERATIONS ==
          public:
            /**
             *  Enumeration of the types of shapes the Prop class can construct a vertex list of.
             */
            enum class shape
            {
                CUBE,   //! Simple cube.
                SKYBOX  //! Skybox.
            };


            //  == FIELDS ==
          private:
            //  -- Properties --
            const GLsizei   m_num_vert; //! Total number of vertices.
            const glm::vec4 m_col;      //! Render colour of the object.

            //  -- Vertex Data --
            const GLuint m_vao; //! Vertex array object handle.
            const GLuint m_vbo; //! Vertex buffer object handle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Prop(const std::vector<Vertex>& t_vert, const glm::vec4& t_col);
            Prop(shape t_shape, const glm::vec4& t_col, float t_scale = 1.0);

          private:
            //  -- Initialisation --
            GLuint init_vao() const;
            GLuint init_vbo() const;
            std::vector<Vertex> init_vert(shape t_shape, float t_size) const;
            std::vector<Vertex> init_vert_cube(float t_scale) const;
            std::vector<Vertex> init_vert_skybox(float t_scale) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            GLsizei get_num_vert() const { return (m_num_vert); }
            const glm::vec4& get_col() const { return (m_col); }
            GLuint get_vao() const { return (m_vao); }
            GLuint get_vbo() const { return (m_vbo); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_HPP
