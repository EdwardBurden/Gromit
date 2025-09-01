#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelViewProjection;

out vec4 vertexColor;
out vec2 textureCoord;

void main()
{
    gl_Position = modelViewProjection * vec4(aPos, 1.0);
   // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aCol, 1.0);
    textureCoord = aTexCoord;
}