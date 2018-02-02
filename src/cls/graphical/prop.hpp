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

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_PROP_HPP
