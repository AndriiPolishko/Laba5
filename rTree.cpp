#include "rTree.h"

RTree::RTree()
{
	Node rootNode;

	rootNode.isLeaf = true;
	rootNode.MBR = { Vector2f(), Vector2f() };

	root = &rootNode;

	leafLevel = 1;
}

RTree::~RTree()
{
}

void RTree::InsertData(Spot* newData)
{
	Insert(newData);
}

void RTree::Insert(Spot* newData)
{
	Node* N;
	N = ChooseSubtree(newData);
}

Node* RTree::ChooseSubtree(Spot* newData)
{
	Node* N = root;

	while (!N->isLeaf)
	{
		// childpointers in N point to leaves
		if (N->childs[0]->data.size())
		{

		}
		// childpointers in N do not point to leaves
		else 
		{

		}
	}

	return N;
}

vector<Node*> RTree::MinOverlapEnlargeNodes(Node* N, Spot* data)
{
	vector<Node*> choosenNodes;
	Rectangle enlargedMBR;

	float minOverlapEnlargment = 100000000000;
	float curOverlapEnlargment;


	for (int i = 0; i < N->childs.size(); i++)
	{
		curOverlapEnlargment = 0;
		enlargedMBR = CalculateEnlargedMBR(N->childs[i]->MBR, data);

		for (int j = 0; j < N->childs.size(); j++)
		{
			if (j == i) continue;



		}
	}

	return choosenNodes;
}

float RTree::FindOverlapArea(Rectangle A, Rectangle B)
{
	int cordsFound = 0;
	float area = 0;

	Vector2f A0 = A.LB;
	Vector2f A1 = A.RT;

	Vector2f B0 = B.LB;
	Vector2f B1 = B.RT;

	Vector2f C0;
	Vector2f C1;

	// LB.x
	if (A0.x >= B0.x && A0.x <= B1.x) {
		C0.x = A0.x;
		cordsFound++;
	}
	else if (B0.x >= A0.x && B0.x <= A1.x) {
		C0.x = B0.x;
		cordsFound++;
	}

	// LB.y
	if (A0.y >= B0.y && A0.y <= B1.y) {
		C0.y = A0.y;
		cordsFound++;
	}
	else if (B0.y >= A0.y && B0.y <= A1.y) {
		C0.y = B0.y;
		cordsFound++;
	}

	// RT.x
	if (A1.x >= B0.x && A1.x <= B1.x) {
		C1.x = A1.x;
		cordsFound++;
	}
	else if (B1.x >= A0.x && B1.x <= A1.x) {
		C1.x = B1.x;
		cordsFound++;
	}

	// RT.y
	if (A1.y >= B0.y && A1.y <= B1.y) {
		C1.y = A1.y;
		cordsFound++;
	}
	else if (B1.y >= A0.y && B1.y <= A1.y) {
		C1.y = B1.y;
		cordsFound++;
	}

	// Calculating area
	if (cordsFound < 4)
	{
		area = 0;
	}
	else
	{
		area = (C1.x - C0.x) * (C1.y - C0.y);
	}

	return area;
}

Rectangle RTree::CalculateEnlargedMBR(Rectangle& oldMBR, Spot* data)
{
	Rectangle newMBR;
	Vector2f newSpot = {data->latitude, data->longitude};

	float maxX, maxY, minX, minY;

	maxX = max(oldMBR.RT.x, newSpot.x);
	maxY = max(oldMBR.RT.y, newSpot.y);
	
	minX = min(oldMBR.LB.x, newSpot.x);
	minY = min(oldMBR.LB.y, newSpot.y);
	
	newMBR = {
		Vector2f(minX, minY),
		Vector2f(maxX, maxY)
	};

	return newMBR;
}