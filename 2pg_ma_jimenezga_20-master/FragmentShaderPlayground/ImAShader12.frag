#version 330
 
out vec4 fragColor;
float segment_x;
float segment_y;
float real_segment;

void main()
{ 
  segment_x = tan((gl_FragCoord.x + gl_FragCoord.y)/30);

  fragColor = vec4(segment_x, segment_x, 0, 1);
}