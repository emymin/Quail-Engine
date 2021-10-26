#version 430 core
out vec4 FragColor;
in vec2 in_UV;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, in_UV);
    FragColor = texColor;
};