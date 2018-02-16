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
layout(location = 1) in float wavelength;   //! Photon packet wavelength.
layout(location = 2) in float weight;       //! Photon packet weight.
layout(location = 3) in float time;         //! Photon packet travelled time so far.

//  -- Uniforms --
uniform mat4 mvp;   //! Model-view-projection matrix.



//  == IN/OUTPUT ==
//  -- Output --
out float vert_time;    //! Time associated with the vertex.
out vec4 vert_col;      //! Colour to draw the vertex with.



//  == FUNCTIONS ==
float colormap_red(float x) {
    if (x < 0.7) {
        return 4.0 * x - 1.5;
    } else {
        return -4.0 * x + 4.5;
    }
}

float colormap_green(float x) {
    if (x < 0.5) {
        return 4.0 * x - 0.5;
    } else {
        return -4.0 * x + 3.5;
    }
}

float colormap_blue(float x) {
    if (x < 0.3) {
       return 4.0 * x + 0.5;
    } else {
       return -4.0 * x + 2.5;
    }
}

vec4 colormap(float x) {
    float r = clamp(colormap_red(x), 0.0, 1.0);
    float g = clamp(colormap_green(x), 0.0, 1.0);
    float b = clamp(colormap_blue(x), 0.0, 1.0);
    return vec4(r, g, b, 1.0);
}



//  == MAIN ==
/**
 *  Main function of the path vertex sub-shader.
 */
void main()
{
    // Set pixel position.
    gl_Position = mvp * vec4(pos, 1.0);

    // Set vertex properties.
    vert_time = time;

    // Colour the vertex according to wavelength.
    vert_col = colormap((wavelength - 400E-9) / 300E-9);
}
