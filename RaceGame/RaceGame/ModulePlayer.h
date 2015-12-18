#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void Restart();

public:

	bool god_mode;

	PhysVehicle3D* vehicle;
	float turn, turn_num;
	float acceleration;
	float brake;
	vec3 xpos;

	mat4x4 ini_trans;
	
	bool start;
	bool win;
	bool lose;

	//uint fx
	uint sound_motor;
	uint victorious;
	uint game_over;
	uint accelerate;
	uint car_break;
};