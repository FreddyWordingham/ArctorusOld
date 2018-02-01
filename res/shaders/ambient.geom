/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Layout --
layout(triangles) in;



//  == OUTPUT ==
//  -- Layout --
layout(triangle_strip, max_vertices = 1) out;



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}
