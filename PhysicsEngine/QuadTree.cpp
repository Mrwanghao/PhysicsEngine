#include "QuadTree.h"
#include <queue>
#include "math2d.h"

QuadTreeData::QuadTreeData(void * _objects, const Rectangle2D & _bounds)
	:
	objects(_objects),
	bounds(_bounds),
	flag(false)
{
}

int QuadTree::maxDepth = 5;
int QuadTree::maxObjectsPerNode = 15;

QuadTreeNode::QuadTreeNode(const Rectangle2D & _bounds)
	:
	nodeBounds(_bounds),
	currentDepth(0)
{
}

bool QuadTreeNode::IsLeaf()
{
	return children.size() == 0;
}

int QuadTreeNode::GetObjectsCount()
{
	Reset();
	int objectCount = contents.size();
	for (int i = 0, size = contents.size(); i < size; i++)
	{
		contents[i]->flag = true;
	}

	std::queue<QuadTreeNode*> process;
	process.push(this);

	while (process.size() > 0)
	{
		QuadTreeNode* processing = process.back();
		if (!processing->IsLeaf())
		{
			for (int i = 0, size = processing->children.size(); i < size; i++)
			{
				process.push(&processing->children[i]);
			}
		}
		else
		{
			for (int i = 0, size = processing->contents.size(); i < size; i++)
			{
				if (!processing->contents[i]->flag)
				{
					objectCount += 1;
					processing->contents[i]->flag = true;
				}
			}
		}
		process.pop();
	}

	Reset();
	return objectCount;

	return 0;
}

void QuadTreeNode::Insert(QuadTreeData & _data)
{
	if (!RectangleRectangle(_data.bounds, nodeBounds))
	{
		return;
	}

	if (IsLeaf() && contents.size() + 1 > maxObjectsPerNode)
	{
		Split();
	}

	if (IsLeaf())
	{
		contents.push_back(&_data);
	}
	else
	{
		for (int i = 0, size = children.size(); i < size; i++)
		{
			children[i].Insert(_data);
		}
	}

}

void QuadTreeNode::Remove(QuadTreeData & _data)
{
	if (IsLeaf()) {
		int removeIndex = -1;
		for (int i = 0, size = contents.size(); i<size; ++i) {
			if (contents[i]->objects == _data.objects) {
				removeIndex = i;
				break;
			}
		}

		if (removeIndex != -1) {
			contents.erase(contents.begin() + removeIndex);
		}

	}
	else {
		for (int i = 0, size = children.size(); i<size; ++i) {
			children[i].Remove(_data);
		}
	}
	Shake();
}

void QuadTreeNode::Update(QuadTreeData & _data)
{
	Remove(_data);
	Insert(_data);
}

//把他的子节点的data全部放进自己的口袋
void QuadTreeNode::Shake()
{
	//必须保证不是叶节点
	if (!IsLeaf()) {
		//获取这个节点及其子节点中的data数量
		int numObjects = GetObjectsCount();
		if (numObjects == 0) {
			children.clear();
		}
		else if (numObjects < maxObjectsPerNode) {
			std::queue<QuadTreeNode*> process;
			process.push(this);
			while (process.size() > 0) {
				QuadTreeNode* processing = process.back();
				if (!processing->IsLeaf()) {
					for (int i = 0, size =
						processing->children.size();
						i < size; ++i) {
						process.push(&processing->children[i]);
					}
				}
				else {
					contents.insert(contents.end(),
						processing->contents.begin(),
						processing->contents.end());
				}
				process.pop();
			}
			children.clear();
		}
	}
}

//根据四个分区来构造树
void QuadTreeNode::Split()
{
	if (currentDepth + 1 >= maxDepth)
	{
		return;
	}

	Vec2 min = nodeBounds.GetMin();
	Vec2 max = nodeBounds.GetMax();
	Vec2 center = min + (max - min) * 0.5f;

	Rectangle2D childAreas[] =
	{
		Rectangle2D::FromMinToMax(Vec2(min.x, min.y), Vec2(center.x, center.y)),
		Rectangle2D::FromMinToMax(Vec2(center.x, min.y), Vec2(max.x, center.y)),
		Rectangle2D::FromMinToMax(Vec2(center.x, center.y), Vec2(max.x, max.y)),
		Rectangle2D::FromMinToMax(Vec2(min.x, center.y), Vec2(center.x, max.y)),
	};

	for (int i = 0; i < 4; i++)
	{
		children.push_back(QuadTreeNode(childAreas[i]));
		children[i].currentDepth = currentDepth + 1;
	}

	for (int i = 0, size = contents.size(); i < size; i++)
	{
		children[i].Insert(*contents[i]);
	}
	contents.clear();
}

void QuadTreeNode::Reset()
{
	if (IsLeaf()) 
	{
		for (int i = 0, size = contents.size(); i<size; ++i) 
		{
			contents[i]->flag = false;
		}
	}
	else 
	{
		for (int i = 0, size = children.size(); i<size; ++i) 
		{
			children[i].Reset();
		}
	}
}

std::vector<QuadTreeData*> QuadTreeNode::Query(const Rectangle2D & area)
{
	std::vector<QuadTreeData*> result;
	if (!RectangleRectangle(area, nodeBounds)) 
	{
		return result;
	}

	if (IsLeaf()) {
		for (int i = 0, size = contents.size(); i<size; ++i) {
			if (RectangleRectangle(contents[i]->bounds, area)) {
					result.push_back(contents[i]);
			}
		}
	}
	else {
		for (int i = 0, size = children.size(); i<size; ++i) {
			std::vector<QuadTreeData*> recurse =
				children[i].Query(area);
			if (recurse.size() > 0) {
				result.insert(result.end(),
					recurse.begin(),
					recurse.end());
			}
		}
	}
	return result;
}
