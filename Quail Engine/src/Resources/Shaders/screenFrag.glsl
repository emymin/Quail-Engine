R""(
#version 430 core
out vec4 FragColor;
  
in vec2 in_UV;

uniform sampler2D screenTexture;

void main()
{ 
    FragColor = texture(screenTexture, in_UV);
}
)""