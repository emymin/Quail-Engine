R""(
#version 430 core
out vec4 FragColor;
in vec2 in_UV;
in vec3 in_worldPos;
in vec3 in_localPos;
in vec3 in_worldNormal;

uniform vec3 u_cameraPos;
uniform vec3 u_ambientColor;
uniform float u_ambientStrength;

struct Material {
    sampler2D u_mainTexture;
    vec4 u_mainColor;
};
uniform Material material;

void main()
{
    vec3 lightDir = vec3(1);
    
    float cosTheta = clamp(dot(in_worldNormal,lightDir),0,1);
    
    vec4 texColor = texture(material.u_mainTexture, in_UV);
    FragColor = texColor*material.u_mainColor;
    FragColor.rgb*=cosTheta;
    FragColor.rgb+=u_ambientColor*u_ambientStrength;
};

)""