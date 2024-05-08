#version 330
 
out vec4 fragColor;

void main()
{ 
  float st = gl_FragCoord.x/1280;
  fragColor = vec4(st, st, st, 1);
}
