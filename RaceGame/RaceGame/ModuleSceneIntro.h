#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	Cube CreateCube(const vec3 size, const vec3 position, vec3 color = vec3(1.0f,1.0f,1.0f), bool phys = true, float angle = 0.0f, const vec3 axis = vec3(0, 0, 0));
	void CreateSphere(const vec3& position, float radius);
	void CreateRandSpheres(int num_spheres);

	void RenderStaticPieces();

	
	

public:
	//<--List Primitives Objects statics
	p2List<Cube*> cube_list;

	p2List<Sphere*> spheres;
	p2List<PhysBody3D*> spheres_body;

	
	//<----CAR------------>
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;


	//Floor
	Cube floor;

	Timer crono;
	float time;
	float best_time;

	int balls_left;
};









