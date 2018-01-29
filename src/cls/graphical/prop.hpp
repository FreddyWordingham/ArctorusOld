/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
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
         *  A class containing all information required to draw an object.
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
                CUBE    //! Simple cube.
            };


            //  == FIELDS ==
          private:
            //  -- Properties --
            const GLsizei   m_num_vert; //! Total number of vertices.
            const glm::vec3 m_col;      //! Render colour of the object.

            //  -- Vertex Data --
            const GLuint m_vao; //! Vertex array object handle.
            const GLuint m_vbo; //! Vertex buffer object handle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Prop(const std::vector<Vertex>& t_vert, const glm::vec3& t_col);
//            Prop(const shape t_shape, const glm::vec3& t_col, const float t_scale = 1.0);

          private:
            //  -- Initialisation --
            GLuint init_vao() const;
            GLuint init_vbo() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            GLsizei get_num_vert() const { return (m_num_vert); }
            const glm::vec3& get_col() const { return (m_col); }
            GLuint get_vao() const { return (m_vao); }
            GLuint get_vbo() const { return (m_vbo); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_HPP
