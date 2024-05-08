#version 330
 
out vec4 fragColor;

void main()
{ 
  float segment = gl_FragCoord.x - 640;
  fragColor = vec4(segment, 0, 0, 1);
}