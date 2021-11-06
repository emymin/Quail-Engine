R""(
#version 430 core
out vec4 FragColor;
in vec2 in_UV;
in vec3 in_worldPos;
in vec3 in_localPos;
in vec3 in_worldNormal;

#define POINTLIGHTSNUMBER 10

struct PointLight{
    vec3 pos;
    vec3 col;
    float range;
};

struct Renderer{
    vec3 u_cameraPos;
    
    PointLight[POINTLIGHTSNUMBER] pointLights;

    vec3 u_ambientColor;
    float u_ambientStrength;
    sampler2D u_environmentMap;
};
uniform Renderer rend;

vec4 sampleSkybox(vec3 ray){
    vec2 uv = vec2(atan(ray.x,ray.z),acos(ray.y))/3.141592;
    uv.x=uv.x*0.5 + 0.5;
    uv.y = 1 - uv.y;
    return texture(rend.u_environmentMap,uv);
}

vec3 bounceRay(vec3 ray,vec3 normal){
    return ray - 2*dot(ray,normal)*normal;
}

//SURF
struct Material {
    sampler2D u_mainTexture;
    vec4 u_mainColor;
};
uniform Material material;
vec4 surf(){
    vec4 texColor = texture(material.u_mainTexture, in_UV);
    return texColor*material.u_mainColor;
}
//



void main()
{    
    
    vec4 col = surf();
    vec3 ray = rend.u_cameraPos-in_worldPos;
    vec3 bounce = bounceRay(ray,in_worldNormal);
    vec3 ambient = rend.u_ambientColor*rend.u_ambientStrength;

    FragColor.a = col.a;

    for(int i=0;i<POINTLIGHTSNUMBER;i++){
        PointLight light = rend.pointLights[i];
        vec3 lightDir = normalize(light.pos - in_worldPos);
        float cosTheta = clamp(dot(in_worldNormal,lightDir),0,1);
        FragColor.rgb += (col.rgb+ambient)*cosTheta*light.col;

    }
};

)""