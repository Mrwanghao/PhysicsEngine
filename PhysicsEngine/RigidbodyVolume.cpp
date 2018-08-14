#include "RigidbodyVolume.h"
#include "EngineDefine.h"



float RigidbodyVolume::InvMass()
{
	if(mass == 0.0f) return 0.0f;
	return 1.0f / mass;
}

void RigidbodyVolume::ApplyForces()
{
	forces = GRAVITY * mass;
}

void RigidbodyVolume::SynchCollisionVolumes()
{
	sphere.center = position;
	box.origin = position;

#pragma error 123
}

void RigidbodyVolume::AddLinearImpulse(const Vec3 & impulse)
{
	velocity = velocity + impulse;
}

void RigidbodyVolume::AddRotationalImpulse(const Vec3& point, const Vec3& impulse)
{
	Vec3 centerOfMass = position;
	Vec3 torque = (point - centerOfMass).Cross(impulse);
	Vec3 angleVelocity = torque * InvTensor();
	angVelocity = angVelocity + angleVelocity;


}










































