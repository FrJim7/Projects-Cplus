#version 330

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;

vec4 normals;
out vec3 normal;

void main()
{
  gl_Position = u_vp_matrix * vec4(a_position, 1.0);
}
