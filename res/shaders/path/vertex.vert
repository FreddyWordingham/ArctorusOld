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



//  == FUNCTION PROTOTYPES ==
vec4 colourmap(const float t_x);
float colourmap_red(const float t_x);
float colourmap_green(const float t_x);
float colourmap_blue(const float t_x);



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
    vert_col = colourmap((wavelength - 400E-9) / 300E-9);
}



//  == FUNCTIONS ==
vec4 colourmap(const float t_x)
{
    // Check if t_x is outside limits.
    if ((t_x < 0.0) || (t_x > 1.0))
    {
        return (vec4(1.0, 0.0, 1.0, 1.0));
    }

    // Determine red, green blue values.
    float red = clamp(colourmap_red(t_x), 0.0, 1.0);
    float green = clamp(colourmap_green(t_x), 0.0, 1.0);
    float blue = clamp(colourmap_blue(t_x), 0.0, 1.0);

    return vec4(red, green, blue, 1.0);
}

float colourmap_red(const float t_x)
{
    if (t_x < 0.7)
    {
        return ((4.0 * t_x) - 1.5);
    }

    return ((-4.0 * t_x) + 4.5);
}

float colourmap_green(const float t_x)
{
    if (t_x < 0.5)
    {
        return ((4.0 * t_x) - 0.5);
    }

    return ((-4.0 * t_x) + 3.5);
}

float colourmap_blue(const float t_x)
{
    if (t_x < 0.3)
    {
       return ((4.0 * t_x) + 0.5);
    }

   return ((-4.0 * t_x) + 2.5);
}
