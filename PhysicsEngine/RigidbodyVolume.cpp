#include "RigidbodyVolume.h"
#include "EngineDefine.h"
#include "math3d.h"
#include "OBB.h"
#include "draw.h"

void RigidbodyVolume::Render()
{
	SynchCollisionVolumes();
	if (type == SPHERE) {
		//::Render(sphere);
	}
	else if (type == BOX) {
		RenderOBB(box);
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

CollisionManifold FindCollisionFeatures(RigidbodyVolume & ra, RigidbodyVolume & rb)
{
	CollisionManifold result;
	result.Reset();
	if (ra.type == SPHERE) {
		if (rb.type == SPHERE) {
			result = FindCollisionFeatures(ra.sphere, rb.sphere);
		}
		else if (rb.type == BOX) {
			result = FindCollisionFeatures(rb.box, ra.sphere);
			result.normal = result.normal * -1.0f;
		}
	}
	else if (ra.type == BOX) {
		if (rb.type == BOX) {
			result = FindCollisionFeatures(ra.box, rb.box);
		}
		else if (rb.type == SPHERE) {
			result = FindCollisionFeatures(ra.box, rb.sphere);
		}
	}
	return result;
}

void ApplyImpulse(RigidbodyVolume & A, RigidbodyVolume & B, const CollisionManifold & M, int c)
{
	float invMass1 = A.InvMass();
	float invMass2 = B.InvMass();
	float invMassSum = invMass1 + invMass2;

	if (invMassSum == 0.0f) {
		return; 
	}

	Vec3 r1 = M.contacts[c] - A.position;
	Vec3 r2 = M.contacts[c] - B.position;
	Matrix4 i1 = A.InvTensor();
	Matrix4 i2 = B.InvTensor();

	Vec3 relativeVel = (B.velocity + B.angVelocity.Cross(r2)) - (A.velocity + A.angVelocity.Cross(r1));
	Vec3 relativeNorm = M.normal;
	relativeNorm.Normalize();
	if (relativeVel.Dot(relativeNorm) > 0.0f) {
		return;
	}

	float e = fminf(A.cor, B.cor);

	float numerator = (-(1.0f + e) * relativeVel.Dot(relativeNorm));
	float d1 = invMassSum;
	Vec3 d2 = MultiplyVector(r1.Cross(relativeNorm), i1).Cross(r1);
	Vec3 d3 = MultiplyVector(r2.Cross(relativeNorm), i2).Cross(r2);
	float denominator = d1 + relativeNorm.Dot(d2 + d3);
	float j = (denominator == 0.0f) ? 0.0f : numerator / denominator;
	if (M.contacts.size() > 0.0f && j != 0.0f) {
		j /= (float)M.contacts.size();
	}

	Vec3 impulse = relativeNorm * j;
	A.velocity = A.velocity - impulse * invMass1;
	B.velocity = B.velocity + impulse * invMass2;

	A.angVelocity = A.angVelocity - MultiplyVector(r1.Cross(impulse), i1);
	B.angVelocity = B.angVelocity + MultiplyVector(r2.Cross(impulse), i2);

	Vec3 t = relativeVel - (relativeNorm * relativeVel.Dot(relativeNorm));
	if (compare(t.MagnitudeSq(), 0.0f)) {
		return;
	}
	t.Normalize();

	numerator = -relativeVel.Dot(t);
	d1 = invMassSum;
	d2 = MultiplyVector(r1.Cross(t), i1).Cross(r1);
	d3 = MultiplyVector(r2.Cross(t), i2).Cross(r2);
	denominator = d1 + t.Dot(d2 + d3);

	float jt = (denominator == 0.0f) ? 0.0f : numerator / denominator;
	if (M.contacts.size() > 0.0f && jt != 0.0f) {
		jt /= (float)M.contacts.size();
	}

	if (compare(jt, 0.0f)) {
		return;
	}

	Vec3 tangentImpuse;
	float friction = sqrtf(A.friction * B.friction);
	if (jt > j * friction) {
		jt = j * friction;
	}
	else if (jt < -j * friction) {
		jt = -j * friction;
	}
	tangentImpuse = t * jt;

	A.velocity = A.velocity - tangentImpuse * invMass1;
	B.velocity = B.velocity + tangentImpuse * invMass2;

	A.angVelocity = A.angVelocity - MultiplyVector(r1.Cross(tangentImpuse), i1);
	B.angVelocity = B.angVelocity + MultiplyVector(r2.Cross(tangentImpuse), i2);
}
