#include "Particle.h"
#include "Line.h"
#include "RaycastResult.h"
#include "Raycast.h"
#include "math3d.h"

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
	int size = constraints.size();
	for (int i = 0; i < size; ++i) {
		Line traveled(prevPosition, position);
		OBB obb = constraints[i];
		if (Linetest(obb, traveled)) {
			Vec3 direction = velocity.GetNormalized();
			Ray ray(prevPosition, direction);
			RaycastResult result;
			if (Raycast(obb, ray, result)) {
				//解决方案是水平速度不变  垂直速度变为bounce的缩放速度
				position = result.point + result.normal * 0.002f;
				Vec3 vn = result.normal * result.normal.Dot(velocity);
				Vec3 vt = velocity - vn;
				prevPosition = position;
				velocity = vt - vn * bounce;
				break;
			}
		}
	}
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

void Particle::SetBounce(float _bounce)
{
	bounce = _bounce;
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
