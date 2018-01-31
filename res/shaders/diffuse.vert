/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Layout --
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.

//  -- Uniforms --
uniform mat4 mvp;       //! Model-view-projection matrix.
uniform mat4 view;      //! View matrix.
uniform vec3 prop_col;  //! Prop colour.
uniform vec3 light_pos; //! Light position.



//  == OUTPUT ==
//  -- Passed --
in vec3 vert_col;               //! Colour to draw the vertex with.
in vec3 cam_space_norm;         //! Camera-space light normal.
in vec3 cam_space_light_norm;   //! Camera-space light direction.
in float dist;                  //! Distance between the light and the vertex.



//  == MAIN ==
/**
 *  Illuminate objects with diffuse, directed lighting.
 */
void main()
{
    gl_Position = mvp * vec4(pos, 1.0);

    cam_space_light_dir = normalize((view * vec4(sun_pos, 1.0)).xyz - (view * vec4(pos, 1.0)).xyz);
    cam_space_norm      = normalize((view * vec4(norm, 0.0)).xyz);

    vert_col = obj_col;

    dist = length(sun_pos - pos);
}
