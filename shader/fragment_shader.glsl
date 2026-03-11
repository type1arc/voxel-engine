#version 330 core

in vec3 FragPos;   // from vertex shader
in vec3 Normal;    // not used here

out vec4 FragColor;

void main() {
    // Normalize position to keep values in [0,1]
    vec3 color = normalize(FragPos);
    FragColor = vec4(abs(color), 1.0);
}

