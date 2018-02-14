/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == IN/OUTPUT ==
//  -- Input --
in vec4 vert_col;   //! Colour of the vertex.

//  -- Output --
out vec4 frag_col;  //! Output fragment colour.



//  == MAIN ==
/**
 *  Main function of the ambient fragment sub-shader.
 */
void main()
{
    // Set the fragment colour.
    frag_col = vert_col;
}
