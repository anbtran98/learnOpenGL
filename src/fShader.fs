#version 330 core

/*
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float transInterpolation;

*/

out vec4 FragColor;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
     /*FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), transInterpolation) * vec4(ourColor, 1.0);*/
     FragColor = vec4(lightColor * objectColor, 1.0);
}
