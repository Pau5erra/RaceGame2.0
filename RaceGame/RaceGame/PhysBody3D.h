#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	bool IsSensor() const;
	void ResetVelocity();

	vec3 GetPos();
	btRigidBody* body = nullptr;

private:
	
	bool is_sensor = false;

public:
	p2List<Module*> collision_listeners;
	float velocity, motion_position;
};

#endif // __PhysBody3D_H__