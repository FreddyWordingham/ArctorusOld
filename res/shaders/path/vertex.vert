/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Layout --
layout(location = 0) in vec3 pos;           //! Photon packet position.
layout(location = 1) in float wavlength;    //! Photon packet wavelength.
layout(location = 2) in float weight;       //! Photon packet weight.
layout(location = 3) in float time;         //! Photon packet travelled time so far.

//  -- Uniforms --
uniform mat4 mvp;       //! Model-view-projection matrix.
uniform vec4 prop_col;  //! Prop colour.



//  == OUTPUT ==
//  -- Passed --
out vec4 vert_col;  //! Colour to draw the vertex with.
out float vert_time;


//  == MAIN ==
/**
 *  Photon packet path rendering shader.
 */
void main()
{
    // Set position.
    gl_Position = mvp * vec4(pos, 1.0);

    // Set vertex colour.
    vert_col = prop_col;

    vert_time = time;
}
