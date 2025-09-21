#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 textureCoord;

uniform sampler2D ourTexture;

void main()
{
  FragColor = texture(ourTexture, textureCoord);
// FragColor = vec4(textureCoord.x, textureCoord.y, 0.0, 1.0);
//FragColor= vertexColor;
} 