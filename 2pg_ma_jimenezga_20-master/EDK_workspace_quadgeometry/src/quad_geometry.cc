#include "quad_geometry.h"
#include <EDK3\dev\gpumanager.h>

bool QuadGeometry::bindAttribute(const EDK3::Attribute attribute, unsigned int where_to_bind_attribute) const
{
	if (attribute == EDK3::Attribute::A_POSITION) {
		EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_buffer.get(), where_to_bind_attribute, EDK3::Type::T_FLOAT_3, false);
		return true;
	}
	if (attribute == EDK3::Attribute::A_NORMAL) {
		EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_buffer.get(), where_to_bind_attribute, EDK3::Type::T_FLOAT_3, false, size_position);
		return true;
	}

	return false;
}

void QuadGeometry::render() const
{
	bindAttribute(EDK3::Attribute::A_POSITION, 0);
	bindAttribute(EDK3::Attribute::A_NORMAL, 1);
	EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::kDrawMode_Triangles, indexs, index_buffer.get());
}

QuadGeometry::QuadGeometry()
{
	// Generate geometry
	float position[] = {
		 0.0f,-1.0f, 1.0f,
		-0.5f, 0.0f, 1.0f,
		 0.0f, 1.0f, 1.0f,
		 0.5f, 0.0f, 1.0f,

		 0.0f,-1.0f, 1.0f,
		-0.5f, 0.0f, 1.0f,
		 0.0f, 1.0f, 1.0f,
		 0.5f, 0.0f, 1.0f
	};
	unsigned short index[] = {
		3, 0, 1,
		1, 2, 3,

		7, 6, 5,
		5, 4, 7
	};
	float normal[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f
	};

	EDK3::dev::GPUManager::Instance()->newBuffer(&vertex_buffer);
	EDK3::dev::GPUManager::Instance()->newBuffer(&index_buffer);

	size_position = sizeof(position);
	size_index = sizeof(index);
	size_normal = sizeof(normal);

	indexs = 12;

	vertex_buffer.get()->init(size_position + size_normal);
	index_buffer.get()->init(size_index);

	vertex_buffer.get()->uploadData(position, size_position, 0);
	vertex_buffer.get()->uploadData(normal, size_normal, size_position);
	index_buffer.get()->uploadData(index, size_index);
}

QuadGeometry::~QuadGeometry()
{	
}
