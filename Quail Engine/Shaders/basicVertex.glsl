#version 430 core
layout (location=0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 in_UV;

uniform mat4 u_MVP;

void main()
{
    gl_Position = vec4(aPos,1.0);
    gl_Position = u_MVP * gl_Position;
    in_UV = aUV;
};
