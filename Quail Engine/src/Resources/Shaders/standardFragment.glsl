R""(
#version 430 core
out vec4 FragColor;
in vec2 in_UV;
in vec3 in_worldPos;
in vec3 in_localPos;
in vec3 in_worldNormal;

uniform vec3 u_cameraPos;

struct Material {
    sampler2D u_mainTexture;
    vec4 u_mainColor;
};
uniform Material material;

void main()
{
    vec4 texColor = texture(material.u_mainTexture, in_UV);
    FragColor = texColor*material.u_mainColor;
    FragColor.rgb*=clamp(dot(in_worldNormal,vec3(0,1,0)),0,1);
};

)""