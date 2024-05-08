#version 330
 
out vec4 fragColor;

vec3 colorA = vec3(0, 0, 0);
vec3 colorB = vec3(1, 0, 0);

void main()
{ 
  if(gl_FragCoord.x < (1280/2)) {
    fragColor = vec4(colorA, 1);
  } else {
    fragColor = vec4(colorB, 1);
  }
}
