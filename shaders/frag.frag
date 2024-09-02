#version 460 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    FragColor = mix(texture(texture0, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0),
                    texture(texture1, TexCoord) * vec4(0.0, 1.0, 1.0, 1.0),
                    0.9);
}
