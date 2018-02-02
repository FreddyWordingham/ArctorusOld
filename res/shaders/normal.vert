/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Arctorus --
in vec3 pos;    //! Vertex positions.
in vec3 norm;   //! Vertex normals.

//  -- Uniforms --
uniform vec4 prop_col;  //! Prop colour.
uniform mat4 model;     //! Model matrix.
uniform mat4 proj;      //! Projection matrix.



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
    vertex.col  = prop_col;
}
