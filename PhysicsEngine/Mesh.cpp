#include "Mesh.h"
#include <memory>

Mesh::~Mesh()
{
	if (values)
	{
		free(values);
		values = nullptr;
	}
}
