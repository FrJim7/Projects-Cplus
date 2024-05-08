#version 330

uniform mat4 u_m_matrix; 
uniform mat4 u_v_matrix; 
uniform mat4 u_p_matrix; 

layout (location = 0) in vec3 a_position; 
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;


out vec3 normal;

void main() {

	vec3 ligth_dir = vec3(-1.0 , 0.0, 0.0); 
	vec3 model_normal = vec4(u_m_matrix * vec4(a_normal, 0.0)).xyz;
	vec3 normalized = normalize(model_normal);
	float diffuse = max(dot(normalized, -ligth_dir), 0.0);
	gl_Position = u_p_matrix * u_v_matrix * u_m_matrix * vec4(a_position, 1.0);
	normal = vec3(diffuse) * (a_normal * 0.5 + 0.5);
}