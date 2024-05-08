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

mat4 translate(float x, float y, float z) {
  mat4 translate_m = mat4(
                vec4(1.0, 0.0, 0.0, 0.0),
                vec4(0.0, 1.0, 0.0, 0.0),
                vec4(0.0, 0.0, 1.0, 0.0),
                vec4(x, y, z, 1.0)
              );
  return translate_m;
}

void main()
{
    
  vec4 position = vec4(a_position, 1.0);

  mat4 TMVP = (u_vp_matrix * u_m_matrix * translate(80.0, 0.0, 0.0));

  position = TMVP * position;

  gl_Position = position;
}
