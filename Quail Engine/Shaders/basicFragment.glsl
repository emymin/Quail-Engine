#version 430 core
out vec4 FragColor;
in vec2 in_UV;

struct Material {
    sampler2D u_mainTexture;
    vec4 u_mainColor;
};
uniform Material material;

void main()
{
    vec4 texColor = texture(material.u_mainTexture, in_UV);
    FragColor = texColor*material.u_mainColor;
};