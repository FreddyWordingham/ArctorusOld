/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == CONSTANTS --
//  -- Uniforms --
const float amb_pow     = 0.1f; //! Ambient lighting power.
const float light_pow   = 5.0f; //! Power of the light source (arbitrary).



//  == INPUT ==
//  -- Passed --
in vec3 vert_col;               //! Colour to draw the vertex with.
in vec3 cam_space_norm;         //! Camera-space light normal.
in vec3 cam_space_light_norm;   //! Camera-space light direction.
in float dist;                  //! Distance between the light and the vertex.



//  == OUTPUT ==
//  -- Passed --
out vec3 col;   //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    col = vert_col;
}
