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
layout(location = 3) in float dist;         //! Photon packet travelled dist.

//  -- Uniforms --
uniform mat4 mvp;           //! Model-view-projection matrix.
uniform vec4 col;           //! Prop colour.

//  -- Constants --
const float render_dist;    //! Distance to render photons at.



//  == OUTPUT ==
//  -- Passed --



//  == MAIN ==
/**
 *  Photon packet path rendering shader.
 */
void main()
{
}
