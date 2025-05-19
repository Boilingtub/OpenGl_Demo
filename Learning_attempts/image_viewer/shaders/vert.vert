R"(
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float scale_x;
uniform float scale_y;
uniform int flip;
uniform float displace_x;
uniform float displace_y;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(
        scale_x*(aPos.x + displace_x),
        scale_y*(aPos.y + displace_y),
        0.0 , 1.0
    );
    TexCoord = vec2(aTexCoord.x,flip*aTexCoord.y);
}
)"

