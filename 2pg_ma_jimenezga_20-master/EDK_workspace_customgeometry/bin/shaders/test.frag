#version 330

 out vec4 fragColor;

 in vec3 normal;
void main()
{
	fragColor = vec4(normal, 1.0);
}
