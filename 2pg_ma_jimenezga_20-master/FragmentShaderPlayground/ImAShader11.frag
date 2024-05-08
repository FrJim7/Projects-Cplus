#version 330
 
out vec4 fragColor;
float segment_x;
float segment_y;

void main()
{ 

  segment_x = cos(gl_FragCoord.x/15);
  segment_y = sin(gl_FragCoord.y/15);

  fragColor = vec4(segment_x, segment_y, 0, 1);
}