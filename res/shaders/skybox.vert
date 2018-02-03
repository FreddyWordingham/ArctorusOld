#version 330 core
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.

out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main()
{
    TexCoords = pos;
    vec4 apos = proj * view * vec4(pos, 1.0);
    gl_Position = apos.xyww;
}
