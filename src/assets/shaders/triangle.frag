#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D imgTexture1;
// uniform sampler2D imgTexture2; If you want more than one texture

void main(){
   // FragColor = mix(texture(imgTexture1, texCoord), texture(imgTexture2, texCoord)) * vec4(vertexColor, 1.0); If you want more than 1 texture
   FragColor = texture(imgTexture1, texCoord);
}