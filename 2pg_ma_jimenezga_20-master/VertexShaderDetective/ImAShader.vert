#version 330

layout (location=0) in vec3 a_position;

mat4 scale(float scx, float scy, float scz) {
  mat4 temp = mat4(
                vec4(scx, 0.0, 0.0, 0.0),
                vec4(0.0, scy, 0.0, 0.0),
                vec4(0.0, 0.0, scz, 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return temp;
}

mat4 rotateX(float angle) {
  mat4 temp = mat4(
                vec4(1.0, 0.0, 0.0, 0.0),
                vec4(0.0, cos(angle), -sin(angle), 0.0),
                vec4(0.0, sin(angle), cos(angle), 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return temp;
}

mat4 rotateY(float angle) {
  mat4 temp = mat4(
                vec4(cos(angle), 0.0, sin(angle), 0.0),
                vec4(0.0, 1.0, 0.0, 0.0),
                vec4(-sin(angle), 0.0, cos(angle), 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return temp;
}

mat4 rotateZ(float angle) {
  mat4 temp = mat4(
                vec4(cos(angle), -sin(angle), 0.0, 0.0),
                vec4(sin(angle), cos(angle), 0.0, 0.0),
                vec4(0.0, 0.0, 1.0, 0.0),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return temp;
}

mat4 translate(float x, float y, float z) {
  mat4 temp = mat4(
                vec4(1.0, 0.0, 0.0, x),
                vec4(0.0, 1.0, 0.0, y),
                vec4(0.0, 0.0, 1.0, z),
                vec4(0.0, 0.0, 0.0, 1.0)
              );
  return temp;
}

void main()
{
  vec4 vertex = vec4(a_position, 1);

  gl_Position = translate(1.0, 0.0, 0.0) * rotateX(0) * scale(0.005, 0.005, 0.005) * vertex ;

}