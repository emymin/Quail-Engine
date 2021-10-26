#version 430 core
out vec4 FragColor;
in vec2 in_UV;


void main()
{

    FragColor = vec4(in_UV.x,in_UV.y,0,1);
};