#version 330
 
in vec3 normal;
out vec4 fragColor;

void main() { 
  
  vec3 new_normal = 0.5 + normal;
  fragColor = vec4(new_normal, 1.0);
	
 }
