/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Arctorus --
in vec3 pos;    //! Vertex positions.
in vec3 norm;   //! Vertex normals.

//  -- Uniforms --
uniform vec4 col;   //! Prop colour.



//  == OUTPUT ==
//  -- Passed --
out Vertex
{
    vec3 norm;
    vec4 col;
}   vertex;



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    gl_Position = vec4(pos, 1.0);

    vertex.norm = norm;
    vertex.col  = col;
}
