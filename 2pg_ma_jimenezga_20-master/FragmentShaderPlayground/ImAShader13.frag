#version 330

out vec4 fragColor;

void main() {

    vec3 seg_x = vec3(step(0.85, fract(cos(gl_FragCoord.x/10)/30)));
    vec3 seg_y = vec3(step(0.85, fract(sin(gl_FragCoord.y / 10) / 30)));

    float color = (seg_x.x * seg_y.y);

    fragColor = vec4(color,color,color, 1);
}