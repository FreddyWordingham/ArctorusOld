/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   05/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Layout --
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.

//  -- Uniforms --
uniform mat4 proj;  //! Propjection matrix.
uniform mat4 view;  //! View matrix.


//  == IN/OUTPUT ==
//  -- Output --
out vec3 texture_coor;  //! Texture coordintes.



//  == MAIN ==
/**
 *  Main function of the skybox vertex sub-shader.
 */
void main()
{
    // Set pixel position.
    gl_Position = (proj * view * vec4(pos, 1.0)).xyww;  // Not a typo. We always want to place the skybox behind everything.

    // Set texture position.
    texture_coor = pos;
}
