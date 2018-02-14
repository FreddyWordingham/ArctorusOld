/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   05/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Uniforms --
uniform samplerCube skybox; //! Skybox textures.



//  == IN/OUTPUT ==
//  -- Input --
in vec3 texture_coor;   //! Texture coordinate.

//  -- Output --
out vec4 frag_colour;   //! Output fragment colour.



//  == MAIN ==
/**
 *  Main function of the skybox fragment sub-shader.
 */
void main()
{
    // Set the fragment colour using the texture coordinate.
    frag_colour = texture(skybox, texture_coor);
}
