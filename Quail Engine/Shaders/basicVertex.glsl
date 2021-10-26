#version 430 core
layout (location=0) in vec3 aPos;
layout(location = 1) in vec2 aUV;

out vec2 in_UV;

void main()
{
    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
    in_UV = aUV;
};
