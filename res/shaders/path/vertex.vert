/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Layout --
layout(location = 0) in vec3 pos;           //! Photon packet position.
layout(location = 1) in float wavlength;    //! Photon packet wavelength.
layout(location = 2) in float weight;       //! Photon packet weight.
layout(location = 3) in float time;         //! Photon packet travelled time so far.

//  -- Uniforms --
uniform mat4 mvp;   //! Model-view-projection matrix.
uniform vec4 col;   //! Path colour.



//  == IN/OUTPUT ==
//  -- Output --
out vec4 vert_col;      //! Colour to draw the vertex with.
out float vert_time;    //! Time associated with the vertex.



//  == MAIN ==
/**
 *  Main function of the path vertex sub-shader.
 */
void main()
{
    // Set pixel position.
    gl_Position = mvp * vec4(pos, 1.0);

    // Set vertex properties.
    vert_col = col;
    vert_time = time;
}
