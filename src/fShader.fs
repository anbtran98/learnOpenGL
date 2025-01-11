#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main() {
     vec2 xReversedTexCoord = TexCoord;
     xReversedTexCoord.x *= -1;
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, xReversedTexCoord), 0.2) * vec4(ourColor, 1.0);
}