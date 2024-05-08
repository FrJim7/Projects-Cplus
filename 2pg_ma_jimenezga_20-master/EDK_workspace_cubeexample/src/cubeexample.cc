#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>

#include <MATH/vector_3.h>
#include <cstdlib>

double pi = 3.14159;
double previus_time;

struct CameraData {
	bool first = false;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 0.0f;
	float lastY = 0.0f;
	float speed = 0.05f;
	Vector3 pos = Vector3(0.0f, 0.0f, 20.5f);
	Vector3 front = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
};

struct GameState {
	int n_row = 10;
	int n_colum = 10;
	int n_depth = 10;
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root;
};

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");
	
	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);

	//Create texutre

	EDK3::ref_ptr<EDK3::Texture> texture;
	// Material
	EDK3::ref_ptr<EDK3::MatDiffuseTexture> diffuse_material;
	EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> diffuse_material_settings;

	diffuse_material.alloc();
	diffuse_material_settings.alloc();

	// Nodes
	EDK3::Node *root = state->root.alloc();
	EDK3::ref_ptr<EDK3::Drawable> drawable;

	// Graphic
	drawable.alloc();
	drawable->set_geometry(cube_geometry.get());
	drawable->set_material(diffuse_material.get());
	drawable->set_material_settings(diffuse_material_settings.get());

	// Transform
	drawable->set_position(0.0f, 0.0f, 0.0f);
	drawable->set_scale(0.5f, 0.5f, 0.5f);
	root->addChild(drawable.get());

	// Color
	diffuse_material_settings.alloc();
	float green_color[] = { rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f, 1.0f };
	diffuse_material_settings->set_color(green_color);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, 2 };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(90, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void input(GameState *state, CameraData *data) {

	if (!data->first && ESAT::MousePositionX() > 0.0f && ESAT::MousePositionY() > 0.0f) {
		data->lastX = ESAT::MousePositionX();
		data->lastY = ESAT::MousePositionY();
		data->first = true;
	}

	float xpos = ESAT::MousePositionX();
	float ypos = ESAT::MousePositionY();

	if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Shift)) {
		data->speed = 0.2f;
	}
	else {
		data->speed = 0.05f;
	}
	if (ESAT::IsKeyPressed('W')) data->pos += (data->front * data->speed);
	if (ESAT::IsKeyPressed('S')) data->pos -= (data->front * data->speed);
	if (ESAT::IsKeyPressed('E')) data->pos += (data->up * data->speed);
	if (ESAT::IsKeyPressed('Q')) data->pos -= (data->up * data->speed);
	if (ESAT::IsKeyPressed('D')) {
		Vector3 right = data->up.CrossProduct(data->up, data->front);
		data->pos -= (right.Normalized() * data->speed);
	}

	if (ESAT::IsKeyPressed('A')) {
		Vector3 right = data->up.CrossProduct(data->up, data->front);
		data->pos += (right.Normalized() * data->speed);
	}

	float xoffset = xpos - data->lastX;
	float yoffset = data->lastY - ypos;
	data->lastX = xpos;
	data->lastY = ypos;

	data->yaw += xoffset * 0.5;
	data->pitch += yoffset * 0.5;

	if (data->pitch > 89.0f) data->pitch = 89.0f;
	if (data->pitch < -89.0f) data->pitch = -89.0f;

	Vector3 direction;
	direction.x = cos((data->yaw * pi) / 180.0f) * cos((data->pitch * pi) / 180.0f);
	direction.y = sin((data->pitch * pi) / 180.0f);
	direction.z = sin((data->yaw * pi) / 180.0f) * cos((data->pitch * pi) / 180.0f);;
	data->front = direction.Normalized();

	float pos[] = { data->pos.x, data->pos.y, data->pos.z };
	float view[] = { data->front.x, data->front.y, data->front.z };

	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
}



void render_function(GameState *state) {
	
	// Update
	state->root->set_rotation_y(-5.0f * ESAT::Time() / 300.0f);


	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	
	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {
	
	// State
	GameState state;
	CameraData data;
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);
	
	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
		
		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;
		
		input(&state, &data);
		render_function(&state);	
		ESAT::WindowFrame();
	}

	return 0;
}
