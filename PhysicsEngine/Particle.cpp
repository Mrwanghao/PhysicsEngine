#include "Particle.h"


Particle::Particle()
{
	type = PARTICLE;
	friction = 0.95f;
	bounce = 0.7f;
	gravity = Vec3(0.0f, -10.0f, 0.0f);
	mass = 1.0f;
}

void Particle::Update(float deltaTime)
{
	//对于一个球来说 没有方向
	prevPosition = position;
	Vec3 acceleration = forces * InvMass();
	velocity = velocity * friction + acceleration * deltaTime;
	position = position + velocity * deltaTime;
	
}

void Particle::Render()
{
	//渲染一个球
}

void Particle::ApplyForces()
{
	forces = gravity * mass;
}

void Particle::SolveConstraints(const std::vector<OBB>& constraints)
{
}

void Particle::SetPosition(const Vec3 & pos)
{
	position = pos;
	prevPosition = pos;
}

Vec3 Particle::GetPosition()
{
	return position;
}

void Particle::SetBounce(float bounce)
{
	this->bounce = bounce;
}

float Particle::GetBounce()
{
	return bounce;
}

void Particle::AddImpulse(const Vec3 & impulse)
{
	velocity = velocity + impulse;
}

float Particle::InvMass()
{
	if (mass == 0.0f) return 0.0f;
	return 1.0f / mass;
}

void Particle::SetMass(float mass)
{
	this->mass = mass;
}

Vec3 Particle::GetVelocity()
{
	return velocity;
}

void Particle::SetFriction(float friction)
{
	this->friction = friction;
}
