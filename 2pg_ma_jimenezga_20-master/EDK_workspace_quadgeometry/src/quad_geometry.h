#ifndef QUAD_GEOMETRY
#define QUAD_GEOMETRY

#include <EDK3\geometry.h>

class QuadGeometry : public EDK3::Geometry
{
public:

	virtual bool bindAttribute(
		const EDK3::Attribute a,
		unsigned int where_to_bind_attribute) const;

	virtual void render() const;

	QuadGeometry();
	~QuadGeometry();

private:	

	EDK3::ref_ptr<EDK3::dev::Buffer> vertex_buffer;
	EDK3::ref_ptr<EDK3::dev::Buffer> index_buffer;
	unsigned int size_position;
	unsigned int size_normal;
	unsigned int size_index;
	unsigned int indexs;
};

#endif
