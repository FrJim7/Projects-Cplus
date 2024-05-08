#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/customgeometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/scoped_array.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/shader.h>

struct GameState {
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root;
};

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");

	// Create custom geometry
	EDK3::ref_ptr<EDK3::CustomGeometry> custom_geometry;
	custom_geometry.alloc();

	// generate vertices
	float positions[] = { 
						//Front
						  1.0f,  1.0f, 1.0f,
						 -1.0f,  1.0f, 1.0f,
						 -1.0f, -1.0f, 1.0f,
						  1.0f, -1.0f, 1.0f,

						//Right
						  1.0f,  1.0f, -1.0f,
						 -1.0f,  1.0f, -1.0f,
						 -1.0f, -1.0f, -1.0f,
						  1.0f, -1.0f, -1.0f,

						//Back
						  1.0f,  1.0f, -1.0f,
						  1.0f,  1.0f,  1.0f,
						  1.0f, -1.0f,  1.0f,
						  1.0f, -1.0f, -1.0f,

						//Left
						 -1.0f,  1.0f,  1.0f,
						 -1.0f,  1.0f, -1.0f,
						 -1.0f, -1.0f, -1.0f,
						 -1.0f, -1.0f,  1.0f,

						//Up
						  1.0f,  1.0f,  1.0f,
						  1.0f,  1.0f, -1.0f,
						 -1.0f,  1.0f, -1.0f,
						 -1.0f,  1.0f,  1.0f,

						//Down
						 -1.0f, -1.0f, -1.0f,
						  1.0f, -1.0f, -1.0f,
						  1.0f, -1.0f,  1.0f,
						 -1.0f, -1.0f,  1.0f,
	};

	float normals[] = { 0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f,

						1.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f,

						0.0f, 0.0f,-1.0f,
						0.0f, 0.0f,-1.0f,
						0.0f, 0.0f,-1.0f,
						0.0f, 0.0f,-1.0f,

						-1.0f, 0.0f, 0.0f,
						-1.0f, 0.0f, 0.0f,
						-1.0f, 0.0f, 0.0f,
						-1.0f, 0.0f, 0.0f,

						0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 0.0f,

						0.0f, -1.0f, 0.0f,
						0.0f, -1.0f, 0.0f,
						0.0f, -1.0f, 0.0f,
						0.0f, -1.0f, 0.0f,

	};


	int positions_size = sizeof(positions);
	int normals_size = sizeof(normals);
	int total_vertices_size = positions_size + normals_size;

	custom_geometry->createVertices(total_vertices_size);

	custom_geometry->uploadVertexPosition(positions, positions_size);
	custom_geometry->uploadVertexNormals(normals, normals_size, positions_size);

	// generate idices
	unsigned int indices[] = { 0, 1, 2,
							   2, 3, 0,

							   8, 9, 10,
							   10, 11, 8,

							   4, 7, 6,
							   6, 5, 4,

							   12, 13, 14,
							   14, 15, 12,

							   16, 17, 18,
							   18, 19, 16,

							   20, 21, 22,
							   22, 23, 20,
	};
	custom_geometry->createIndices(36);
	custom_geometry->uploadIndices(indices, sizeof(indices));

	// Material
	EDK3::ref_ptr<EDK3::MatDiffuse> diffuse_material;
	EDK3::ref_ptr<EDK3::MatDiffuse::Settings> cutom_material_settings;

	diffuse_material.alloc();
	cutom_material_settings.alloc();

	// Create a Drawable Node (Geometry+Material+Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable;

	// Graphic
	drawable.alloc();
	drawable->set_geometry(custom_geometry.get());
	drawable->set_material(diffuse_material.get());
	drawable->set_material_settings(cutom_material_settings.get());
	state->root = drawable.get();

	// Transform
	drawable->set_position(0.0f, 0.0f, 0.0f);

	// Color 
	float green_color[] = { 0 / 255.0f, 190 / 255.0f,  222 / 255.0f, 1.0f };
	cutom_material_settings->set_color(green_color);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, 4.0f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void render_function(GameState *state) {

	// For Every frame... determine what's visible:
	state->root->set_rotation_x(-5.0f * ESAT::Time() / 30.0f);
	state->root->set_rotation_y(5.0f * ESAT::Time() / 30.0f);

	state->camera->doCull(state->root.get());

	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {

	// State
	GameState state;
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);

	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

		render_function(&state);
		ESAT::DrawBegin();
		ESAT::DrawText(10, 20, "cube example");
		ESAT::DrawEnd();
		ESAT::WindowFrame();
	}

	return 0;
}
