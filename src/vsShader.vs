#version 330 core
layout (location = 0) in vec3 aPos;

uniform float horizontalOffset;

out vec4 vertPosition;

void main () {
     vec3 temp;
     temp = aPos * 1; // learnopengl.com - shader, exercise 1: flip triangle
     temp.x += horizontalOffset; // learnopengl.com - shader, exercise 2: triangle horizontal offset
     temp.y += horizontalOffset;
     gl_Position = vec4( temp, 1.0 );
     vertPosition = vec4( temp, 1.0 ); // learnopengl.com shader, exercise 3: set vertex position to fragment color
}
