R""(
#version 430 core
out vec4 FragColor;
in vec3 in_worldPos;

struct Material {
    sampler2D u_mainTexture;
    vec4 u_mainColor;
};
uniform Material material;
uniform vec3 cameraPos;

void main()
{

    
    vec3 ray = normalize(cameraPos-in_worldPos);
    vec2 in_UV = vec2(atan(ray.x,ray.z),acos(-ray.y))/3.141592;
    in_UV.x=in_UV.x*0.5 + 0.5;
    in_UV.y = 1 - in_UV.y;

    vec4 texColor = texture(material.u_mainTexture, in_UV);
    FragColor = texColor*material.u_mainColor;
};

)""