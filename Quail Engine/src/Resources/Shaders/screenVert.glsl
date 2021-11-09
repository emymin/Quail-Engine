R""(
#version 430 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 in_UV;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    in_UV = aUV;
}
)""