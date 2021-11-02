R""(

#version 430 core
layout (location=0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 in_UV;
out vec3 in_worldPos;
out vec3 in_localPos;
out vec3 in_worldNormal;

uniform mat4 u_M;
uniform mat4 u_MVP;

void main()
{
    gl_Position = vec4(aPos,1.0);
    gl_Position = u_MVP * gl_Position;
    in_worldPos = (u_M * vec4(aPos,1.0)).xyz;
    in_localPos = aPos;
    in_worldNormal = (u_M*vec4(aNormal,0.0)).xyz;
    in_UV = aUV;
};

)""