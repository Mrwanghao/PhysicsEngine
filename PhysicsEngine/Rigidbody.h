#pragma once
#include <vector>
#include "OBB.h"

#define BASE 0
#define PARTICLE 1
#define SPHERE 2
#define BOX 3

class Rigidbody
{
public:
	int type;
public:
	inline Rigidbody() { type = BASE; }
	virtual ~Rigidbody() {}

	virtual inline void Update(float deltaTime) {}
	virtual inline void Render() {}
	virtual inline void ApplyForces() {}
	virtual inline void SolveConstraints(const std::vector<OBB>& constraints) {}

	inline bool HasVolume() { return type == SPHERE || type == BOX; }

};