#version 330
 
out vec4 fragColor;
float segment_x;

void main()
{ 
  segment_x = cos(gl_FragCoord.x/15);

  fragColor = vec4(segment_x, 0, 0, 1);
}