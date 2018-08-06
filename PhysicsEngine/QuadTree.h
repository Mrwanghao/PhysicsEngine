#pragma once

#include "Rectangle2D.h"
#include <vector>

class QuadTreeData
{
public:
	void* objects;
	Rectangle2D bounds;
	bool flag;
	QuadTreeData(void* _objects, const Rectangle2D& _bounds);

};

class QuadTreeNode
{
protected:
	std::vector<QuadTreeNode> children;
	std::vector<QuadTreeData*> contents;
	int currentDepth;
	static int maxDepth;
	static int maxObjectsPerNode;
	Rectangle2D nodeBounds;

public:
	QuadTreeNode(const Rectangle2D& _bounds);

public:
	bool IsLeaf();
	int GetObjectsCount();
	void Insert(QuadTreeData& _data);
	void Remove(QuadTreeData& _data);
	void Update(QuadTreeData& _data);
	void Shake();
	void Split();
	void Reset();
	std::vector<QuadTreeData*> Query(const Rectangle2D& area);
};

typedef QuadTreeNode QuadTree;
