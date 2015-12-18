#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include <ctime>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 13.0f, -10.0f));
	App->camera->LookAt(vec3(0, 5, 6));
	
	time = TIME;
	best_time = 0.0f;
	balls_left = NUM_BALLS;
	//Floor
	CreateCube(vec3(150.0f, 1.0f, 150.0f), vec3(0, 0, 0), vec3(0.0f, 5.0f, 1.0f));
	
	//Walls
	CreateCube(vec3(150.0f, 20.0f, 1.0f), vec3(0, 10.0f, 75.0f), vec3(0.0f,1.0f,5.0f));
	CreateCube(vec3(150.0f, 20.0f, 1.0f), vec3(0, 10.0f, -75.0f), vec3(0.0f, 1.0f, 5.0f));
	CreateCube(vec3(1.0f, 20.0f, 150.0f), vec3(75.0f, 10.0f, 0), vec3(0.0f, 1.0f, 5.0f));
	CreateCube(vec3(1.0f, 20.0f, 150.0f), vec3(-75.0f, 10.0f, 0), vec3(0.0f, 1.0f, 5.0f));

	CreateRandSpheres(NUM_BALLS);
	App->audio->PlayMusic("MasterOfPuppets.ogg");


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (p2List_item<Cube*>* tmp = cube_list.getFirst(); tmp != NULL; tmp = tmp->next){
		delete tmp->data;
	}
	cube_list.clear();
	for (p2List_item<Sphere*>* tmp = spheres.getFirst(); tmp != NULL; tmp = tmp->next){
		delete tmp->data;
	}
	spheres.clear();

	spheres_body.clear();
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	RenderStaticPieces();
	
	if (App->player->god_mode == false){
		if (App->player->start){
			time -= 0.02f;
		}
	}
	if (App->player->god_mode){
		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		{
			CreateRandSpheres(1);
		}
	}
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	p2List_item<Sphere*>* tmp1 = spheres.getFirst();
	p2List_item<PhysBody3D*>* tmp2 = spheres_body.getFirst();
	int i = 0;
	for (tmp2; tmp2 != NULL; tmp2 = tmp2->next){
		
		if (i == spheres_body.find(body1)){
			tmp2->data->SetPos(tmp2->data->GetPos().x, tmp2->data->GetPos().y - 6, tmp2->data->GetPos().z);
			balls_left--;
			break;
		}
		i++;
		tmp1=tmp1->next;
	}
}

Cube ModuleSceneIntro::CreateCube(const vec3 size, const vec3 position,  vec3 color, bool phys, float angle, const vec3 axis){
	Cube* new_cube = new Cube();
	new_cube->size.Set(size.x,size.y,size.z);
	if (angle != 0.0f)
		new_cube->SetRotation(angle, axis);

	new_cube->SetPos(position.x, position.y, position.z);
	if (color.x == 0.0f && color.y == 0.0f && color.z == 0.0f){
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
	}
	new_cube->color.Set(color.x, color.y, color.z);
	App->physics->AddBody(*new_cube, 0);
	cube_list.add(new_cube);

	return *new_cube;
}

//Iterate for objects statics and render them
void ModuleSceneIntro::RenderStaticPieces()
{

	for (p2List_item<Cube*>* tmp = cube_list.getFirst(); tmp != NULL; tmp = tmp->next){

		tmp->data->Render();
	}

	p2List_item<Sphere*>* tmp1 = spheres.getFirst();
	p2List_item<PhysBody3D*>* tmp2 = spheres_body.getFirst();
	for (tmp2; tmp2 != NULL; tmp2 = tmp2->next){
		tmp2->data->GetTransform(&tmp1->data->transform);
		tmp1->data->Render();
		tmp1 = tmp1->next;
	}
	
}

void ModuleSceneIntro::CreateSphere(const vec3& position, float radius)
{
	float r = rand() % 5;
	float g = rand() % 5;
	float b = rand() % 5;
	Sphere* new_sphere = new Sphere();
	new_sphere->radius = radius;
	new_sphere->SetPos(position.x, position.y, position.z);
	new_sphere->color.Set(r, g, b);
	spheres.add(new_sphere);

	PhysBody3D* new_sphere_body = new PhysBody3D();
	new_sphere_body = App->physics->AddBody(*new_sphere, 0);
	new_sphere_body->SetAsSensor(true);
	new_sphere_body->collision_listeners.add(this);
	spheres_body.add(new_sphere_body);

	
}

void ModuleSceneIntro::CreateRandSpheres(int num_spheres){

	for (int i = 0; i < num_spheres; i++){
		float x_rand = 72-rand() % 145;
		float z_rand = 72-rand() % 145;
		CreateSphere(vec3(x_rand, 3.0f, z_rand), 2);
	}

}












