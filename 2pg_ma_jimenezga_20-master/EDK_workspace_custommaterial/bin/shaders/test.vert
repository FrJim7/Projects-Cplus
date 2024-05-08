#version 330

uniform mat4 u_v_matrix;
uniform mat4 u_p_matrix;
uniform mat4 u_m_matrix;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;

out vec3 normal;

void main()
{
   normal = 0.5 + a_normal;
   gl_Position = ((u_p_matrix * u_v_matrix) * u_m_matrix) * vec4(a_position, 1);
}