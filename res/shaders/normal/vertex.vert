/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Layout --
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.



//  == IN/OUTPUT ==
//  -- Output --
out vec3 vert_pos;  //! Position of the vertex with.
out vec3 vert_norm; //! Normal of the vertex.



//  == MAIN ==
/**
*  Main function of the normal vertex sub-shader.
*/
void main()
{
    // Set vertex properties.
    vert_pos = pos;
    vert_norm = norm;
}
