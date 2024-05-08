#version 330

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;

vec4 normals;
out vec3 normal;

mat4 scale(float scx, float scy, float scz) {
  mat4 scale_m = mat4(
                vec4(scx, 0.0, 0.0, 0.0),
                vec4(0.0, scy, 0.0, 0.0),
                vec4(0.0, 0.0, scz, 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return scale_m;
}

void main()
{

  mat4 MVP = u_vp_matrix * u_m_matrix;

  gl_Position = MVP * scale(1.5, 2.0, -0.5) * vec4(a_position, 1.0);
}
