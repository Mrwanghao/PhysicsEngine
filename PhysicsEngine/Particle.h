#pragma once
#include "Rigidbody.h"




class Particle : public Rigidbody
{
	Vec3 position;
	Vec3 prevPosition;
	Vec3 forces;
	Vec3 gravity;
	Vec3 velocity;
	float friction;
	float bounce;
	float mass;


	Particle();

	void Update(float deltaTime);
	void Render();
	void ApplyForces();
	void SolveConstraints(const std::vector<OBB>& constraints);

	void SetPosition(const Vec3& pos);
	Vec3 GetPosition();

	//·´µ¯
	void SetBounce(float bounce);
	float GetBounce();

	void AddImpulse(const Vec3& impulse);
	float InvMass();
	void SetMass(float mass);
	Vec3 GetVelocity();
	void SetFriction(float friction);
};