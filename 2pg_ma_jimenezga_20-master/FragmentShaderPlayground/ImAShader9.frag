#version 330
 
out vec4 fragColor;

void main()
{ 
  float segment_x = gl_FragCoord.x - 640;
  float segment_y = gl_FragCoord.y - 360;
  segment_x = segment_x/20;
  segment_y = segment_y/20;
  fragColor = vec4(segment_x, segment_y, 0, 1);
}