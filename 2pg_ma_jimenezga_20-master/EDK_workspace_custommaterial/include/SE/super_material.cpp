#include "super_material.h"

#include <cstdio>

#include "EDK3\dev\glew.h"
#include "EDK3\scoped_array.h"
#include "EDK3\dev\gpumanager.h"

SuperMaterial::SuperMaterial() {

	EDK3::dev::GPUManager::Instance()->newProgram(&program_);
}

EDK3::dev::Program* SuperMaterial::get_program()
{
	return program_.get();
}

const EDK3::dev::Program* SuperMaterial::get_program() const
{
	return program_.get();
}

void readFile(const char *file, EDK3::scoped_array<char> &output, unsigned int *size)
{
	FILE *file_;

	fopen_s(&file_, file, "rb");
	if (NULL == file_) { return; }

	fseek(file_, 0, SEEK_END);
	*size = ftell(file_);
	rewind(file_);

	output.alloc(*size + 1);
	output.memClear();

	fread_s(output.get(), *size, *size, 1, file_);
	fclose(file_);
}

bool SuperMaterial::load_shaders_from_filepaths(const char* vertex_shader_path, const char* fragment_shader_path) {
	
	unsigned int vertex_size = 0;
	unsigned int fragment_size = 0;
	
	EDK3::scoped_array<char> vertex_load;
	EDK3::scoped_array<char> fragment_load;

	EDK3::ref_ptr<EDK3::dev::Shader> vertex;
	EDK3::ref_ptr<EDK3::dev::Shader> fragment;

	readFile(vertex_shader_path, vertex_load, &vertex_size);
	readFile(fragment_shader_path, fragment_load, &fragment_size);

	EDK3::dev::GPUManager::Instance()->newShader(&vertex);
	EDK3::dev::GPUManager::Instance()->newShader(&fragment);

	vertex->loadSource(EDK3::dev::Shader::Type::kType_Vertex, vertex_load.get(), vertex_size);
	fragment->loadSource(EDK3::dev::Shader::Type::kType_Fragment, fragment_load.get(), fragment_size);

	load_shaders(vertex, fragment);

	return true;
}

bool SuperMaterial::load_shaders(EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader, EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader) {
	
	if (!vertex_shader->compile()) {
		return false;
	}

	if (!fragment_shader->compile()) {
		return false;
	}

	get_program()->attach(vertex_shader.get());
	get_program()->attach(fragment_shader.get());

	return get_program()->link();
}

bool SuperMaterial::enable(const EDK3::MaterialSettings *settings) const {

	get_program()->use();
	return true;
}

void SuperMaterial::setupModel(const float model[16]) const
{
	int position = get_program()->get_uniform_position("u_m_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, model);
}

unsigned int SuperMaterial::num_attributes_required() const{
	
	int count;
	glGetProgramiv(program_->internal_id(), GL_ACTIVE_ATTRIBUTES, &count);

	return count;
}

void SuperMaterial::setupCamera(const float projecton[16], const float view[16]) const
{
	int position = get_program()->get_uniform_position("u_p_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, projecton);

	position = get_program()->get_uniform_position("u_v_matrix");
	get_program()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, view);
}

EDK3::Attribute SuperMaterial::attribute_at_index(const unsigned int attrib_idx) const
{
	switch (attrib_idx)
	{
	case 0: return EDK3::Attribute::A_POSITION;
		break;
	case 1: return EDK3::Attribute::A_NORMAL;
		break;
	case 2: return EDK3::Attribute::A_COLOR;
	}
}

EDK3::Type SuperMaterial::attribute_type_at_index(const unsigned int attrib_index) const
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