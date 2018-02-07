/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == SETTINGS ==
//  -- Normal Rendering --
const vec4 normal_end_col = vec4(0.0, 0.0, 0.0, 1.0);   //! Colour of the end of the normal.



//  == LINKING ==
//  -- Layout --
layout(points) in;                          //! Start with points.
layout(line_strip, max_vertices = 2) out;   //! End with a line strip.

//  -- Uniforms --
uniform mat4 mvp;           //! Model-view-projection matrix.
uniform vec4 col;           //! Normal colour.
uniform float light_power;  //! Length to draw normal lines.



//  == IN/OUTPUT ==
//  -- Input --
in vec3 vert_pos[];     //! Array of vertex positions.
in vec3 vert_norm[];    //! Array of vertex normals.

//  -- Output --
out vec4 geom_col;  //! Geometry colour.



//  == MAIN ==
/**
 *  Main function of the normal geometry sub-shader.
 */
void main()
{
    // Create the start vertex.
    vec4 v0     = vec4(vert_pos[0], 1.0);
    gl_Position = mvp * v0;
    geom_col = col;
    EmitVertex();

    // Create the end vertex.
    vec4 v1     = v0 + vec4(vert_norm[0] * light_power, 0.0);
    gl_Position = mvp * v1;
    geom_col = normal_end_col;
    EmitVertex();

    // Send the completed line.
    EndPrimitive();
}
