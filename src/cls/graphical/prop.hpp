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
            //  == FIELDS ==
          private:
            //  -- Properties --
            const GLsizei   m_num_vert;   //! Total number of vertices.
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
