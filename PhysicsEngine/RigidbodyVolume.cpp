#include "RigidbodyVolume.h"
#include "EngineDefine.h"
#include "math3d.h"


void RigidbodyVolume::Render()
{
	SynchCollisionVolumes();
	if (type == SPHERE) {
		//::Render(sphere);
	}
	else if (type == BOX) {
		//::Render(box);
	}
}

void RigidbodyVolume::Update(float deltaTime)
{
	const float damping = 0.98f;

	Vec3 acceleration = forces * InvMass();
	velocity = velocity + acceleration * deltaTime;
	velocity = velocity * damping;

	if (fabsf(velocity.x) < 0.001f) {
		velocity.x = 0.0f;
	}
	if (fabsf(velocity.y) < 0.001f) {
		velocity.y = 0.0f;
	}
	if (fabsf(velocity.z) < 0.001f) {
		velocity.z = 0.0f;
	}

	if (type == BOX) {
		Vec3 angAccel = MultiplyVector(torques, InvTensor());
		angVelocity = angVelocity + angAccel * deltaTime;
		angVelocity = angVelocity * damping;

		if (fabsf(angVelocity.x) < 0.001f) {
			angVelocity.x = 0.0f;
		}
		if (fabsf(angVelocity.y) < 0.001f) {
			angVelocity.y = 0.0f;
		}
		if (fabsf(angVelocity.z) < 0.001f) {
			angVelocity.z = 0.0f;
		}
	}

	// Integrate position
	position = position + velocity * deltaTime;

	if (type == BOX) {
		orientation = orientation + angVelocity * deltaTime;
	}

	SynchCollisionVolumes();
}

float RigidbodyVolume::InvMass()
{
	if(mass == 0.0f) return 0.0f;
	return 1.0f / mass;
}

Matrix4 RigidbodyVolume::InvTensor()
{
	if (mass == 0) {
		return Matrix4(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		);
	}

	float ix = 0.0f;
	float iy = 0.0f;
	float iz = 0.0f;
	float iw = 0.0f;

	//分别计算球和盒体的扭力矩
	if (mass != 0 && type == SPHERE) {
		float r2 = sphere.radius * sphere.radius;
		float fraction = (2.0f / 5.0f);

		ix = r2 * mass * fraction;
		iy = r2 * mass * fraction;
		iz = r2 * mass * fraction;
		iw = 1.0f;
	}
	else if (mass != 0 && type == BOX) {
		Vec3 size = box.size * 2.0f;
		float fraction = (1.0f / 12.0f);

		float x2 = size.x * size.x;
		float y2 = size.y * size.y;
		float z2 = size.z * size.z;

		ix = (y2 + z2) * mass * fraction;
		iy = (x2 + z2) * mass * fraction;
		iz = (x2 + y2) * mass * fraction;
		iw = 1.0f;
	}

	return Matrix4(
		ix, 0, 0, 0,
		0, iy, 0, 0,
		0, 0, iz, 0,
		0, 0, 0, iw).Invert();
}

//添加力的作用
void RigidbodyVolume::ApplyForces()
{
	forces = GRAVITY * mass;
}

void RigidbodyVolume::SynchCollisionVolumes()
{
	sphere.center = position;
	box.origin = position;

	box.orientation = Rot3x3(
		RAD2DEG(orientation.x),
		RAD2DEG(orientation.y),
		RAD2DEG(orientation.z)
	);
}

//添加线性冲量
void RigidbodyVolume::AddLinearImpulse(const Vec3 & impulse)
{
	velocity = velocity + impulse;
}

//添加旋转冲量
void RigidbodyVolume::AddRotationalImpulse(const Vec3& point, const Vec3& impulse)
{
	Vec3 centerOfMass = position;
	Vec3 torque = (point - centerOfMass).Cross(impulse);
	Vec3 angleVelocity = torque * InvTensor();
	angVelocity = angVelocity + angleVelocity;


}










































