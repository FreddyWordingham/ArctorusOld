#version 330 core
out vec4 FragColor;

in vec3 texture_coor;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, texture_coor);
}
