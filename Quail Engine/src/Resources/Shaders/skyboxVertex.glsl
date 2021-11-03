R""(

#version 430 core
layout (location=0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec3 in_worldPos;

uniform mat4 u_MVP;

void main()
{
    gl_Position = vec4(aPos,1.0);
    gl_Position = u_MVP * gl_Position;
    in_worldPos = aPos;

};

)""