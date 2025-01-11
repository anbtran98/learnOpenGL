#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main() {
/*
     float scaler = 2;
     vec2 crateTexCoord = TexCoord;

     crateTexCoord.x /= scaler;
     crateTexCoord.x += 1/(scaler * 2);
     crateTexCoord.y /= scaler;
     crateTexCoord.y += 1/(scaler * 2);

     FragColor = mix(texture(texture1, crateTexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourColor, 1.0);
     */
     
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourColor, 1.0);
}
/*
    NOTE: scaling & shifting texture (opposite of conventional mathematic)
    -----------------------------------------------------------
    '*' will shrink,
    '/' will stretch,
    '+' will shift left,
    '-' will shift right.
*/