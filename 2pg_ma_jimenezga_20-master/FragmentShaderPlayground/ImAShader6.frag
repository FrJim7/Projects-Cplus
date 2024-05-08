#version 330
 
out vec4 fragColor;

vec3 colorA = vec3(0, 0, 1);
vec3 colorB = vec3(1, 0.2, 0.9);

void main()
{ 
  float fade_x = gl_FragCoord.x/1280;
  float fade_y = gl_FragCoord.y/720;

  colorA = vec3(0, fade_y, 1);
  colorB = vec3(1, fade_y, 1);

  vec3 color = vec3(0.0);

  color = mix(colorA, colorB, fade_x);

  fragColor = vec4(color, 1);
}
