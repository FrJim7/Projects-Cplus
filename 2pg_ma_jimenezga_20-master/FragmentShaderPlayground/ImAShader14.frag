#version 330

out vec4 fragColor;

void main() {
  
  float color = float(abs(gl_FragCoord.x - 640) == abs(gl_FragCoord.y - 360));
  
  fragColor = vec4(color, color, 0, 1);
}