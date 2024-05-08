#include "Eluminado.h"

#include "EDK3/dev/shader.h"
#include "EDK3/dev/glew.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/scoped_array.h"

Eluminado::Eluminado() {
	
	/*char vertex_c[] = "\
	#version 330\n \
	uniform mat4 u_m_matrix; \n \
	uniform mat4 u_vp_matrix; \n\n \
	layout(location = 0) in vec3 a_position; \n \
	layout(location = 1) in vec3 a_normal;\n \
	out vec3 normal;\n \
	void main() {\n \
		vec3 ligth_dir = vec3(1.0 , 0.0, 0.0); \n\
		vec3 model_normal = vec4(u_m_matrix * vec4(a_normal, 0.0)).xyz;\n \
		vec3 normalized = normalize(model_normal);\n \
		float diffuse = max(dot(normalized, -ligth_dir), 0.0);\n \
		gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);\n \
		normal = vec3(diffuse) * (a_normal * 0.5 + 0.5);\n \
	}";

	char fragment_c[] = "\
	#version 330\n \
	out vec4 fragColor;\n \
	in vec3 normal;\n \
	void main() {\n \
		fragColor = vec4(normal, 1.0); \n \
	}";*/

	EDK3::ref_ptr<EDK3::dev::Shader> vertex;
	EDK3::ref_ptr<EDK3::dev::Shader> fragment;

	EDK3::dev::GPUManager::Instance()->newShader(&vertex);
	EDK3::dev::GPUManager::Instance()->newShader(&fragment);

	EDK3::dev::GPUManager::Instance()->newProgram(&program_);

	loadVertexShaderFile(&vertex, "./shader.vert");
	loadFragmentShaderFile(&fragment, "./shader.frag");

	if (vertex->compile()) {
		printf("+vertex\n");
	}
	if (fragment->compile()) {
		printf("+fragment\n");
	}

	program_->attach(vertex.get());
	program_->attach(fragment.get());

	EDK3::scoped_array<char> info_link;

	if (program_->link(&info_link)) {
		printf("+link\n");
	}

	printf("%s", info_link.get());

}

EDK3::dev::Program* Eluminado::get_program() {
	return program_.get();
}

const EDK3::dev::Program* Eluminado::get_program() const{
	return program_.get();
}

bool Eluminado::enable(const EDK3::MaterialSettings *settings) const {

	program_->use();
	return true;
}

void Eluminado::setupModel(const float model[16]) const
{
	int position = get_program()->get_uniform_position("u_m_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, model);
}

void Eluminado::setupLight(const float ligth[3]) const{
	int position = get_program()->get_uniform_position("ligth_dir");
	get_program()->set_uniform_value(position, EDK3::Type::T_FLOAT_3, ligth);
}

unsigned int Eluminado::num_attributes_required() const {

	return 2;
}

void Eluminado::setupCamera(const float projecton[16], const float view[16]) const
{
	int position = get_program()->get_uniform_position("u_p_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, projecton);

	position = get_program()->get_uniform_position("u_v_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, view);
}

EDK3::Attribute Eluminado::attribute_at_index(const unsigned int attrib_idx) const
{
	switch (attrib_idx)
	{
	case 0: return EDK3::Attribute::A_POSITION;
		break;
	case 1: return EDK3::Attribute::A_NORMAL;
		break;
	case 2: return EDK3::Attribute::A_UV;
	}
}

EDK3::Type Eluminado::attribute_type_at_index(const unsigned int attrib_index) const
{
	switch (attrib_index)
	{
	case 0: return EDK3::Type::T_FLOAT_3;
		break;
	case 1: return EDK3::Type::T_FLOAT_3;
		break;
	case 2: return EDK3::Type::T_FLOAT_3;
	}
}