#ifndef __ELUMINADO_H__
#define __ELUMINADO_H__ 1

#include "EDK3/material.h"
#include "EDK3/dev/program.h"
#include "EDK3/materialsettings.h"

class Eluminado : public EDK3::Material {
public:
	Eluminado();

	 bool enable(const EDK3::MaterialSettings *) const override;

	 void setupCamera(const float projecton[16], const float view[16]) const override;

	 void setupModel(const float model[16]) const override;

	 void setupLight(const float light[3]) const;

	 unsigned int num_attributes_required() const override;

	 EDK3::Attribute attribute_at_index(
		const unsigned int attrib_idx) const override;

	 EDK3::Type attribute_type_at_index(
		const unsigned int attrib_index) const override;

	 class Settings : public EDK3::MaterialSettings {
	 public:
		 Settings()
		 {
			 for (int i = 0; i < 4; ++i) {
				 color_data[i] = 1.0f;
				 custom_data_[i] = 1.0f;
			 }
		 }
		 void set_color(const float v[4]) { memcpy(color_data, v, sizeof(color_data)); }
		 void set_color(float r, float g, float b, float a = 1.0f) {
			 color_data[0] = r; color_data[1] = g; color_data[2] = b; color_data[3] = a;
		 }
		 const float *color() const { return color_data; }

		 void set_custom_data(const float data[4]) { memcpy(custom_data_, data, sizeof(custom_data_)); }
		 const float *custom_data() const { return custom_data_; }

	 protected:
		 virtual ~Settings() {}

	 private:
		 Settings(const Settings&);
		 Settings& operator=(const Settings&);
		 float color_data[4];
		 float custom_data_[4];
	 };

protected:
	EDK3::dev::Program* get_program();
	const EDK3::dev::Program* get_program() const;

	
	virtual ~Eluminado() {};
private:
	EDK3::ref_ptr<EDK3::dev::Program> program_;

	Eluminado(const Eluminado&);
	Eluminado& operator=(const Eluminado &);
};

#endif