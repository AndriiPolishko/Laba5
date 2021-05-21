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
	vector<Node*> ;

	while (!N->isLeaf)
	{
		// childpointers in N point to leaves
		if (N->childs[0]->data.size())
		{
			N = MinOverlapEnlargeNode(N, newData);
		}
		// childpointers in N do not point to leaves
		else 
		{
			N = MinAreaEnlargementNode(N, newData);
		}
	}

	return N;
}

Node* RTree::MinOverlapEnlargeNode(Node* N, Spot* data)
{
	Node* choosenNode;
	Rectangle enlargedMBR;

	float minOverlapEnlargment = 10000000000000;
	float curOverlapEnlargment;

	float curOverlap;
	float oldOverlap;


	for (int i = 0; i < N->childs.size(); i++)
	{
		curOverlapEnlargment = 0;
		enlargedMBR = CalculateEnlargedMBR(N->childs[i]->MBR, data);

		for (int j = 0; j < N->childs.size(); j++)
		{
			if (j == i) continue;

			oldOverlap = FindOverlapArea(
				N->childs[i]->MBR,
				N->childs[j]->MBR
			);

			curOverlap = FindOverlapArea(
				enlargedMBR, 
				N->childs[j]->MBR
			);

			curOverlapEnlargment = curOverlap - oldOverlap;
		}

		// Compare MBR overlap enlargement
		if (curOverlapEnlargment < minOverlapEnlargment)
		{

			choosenNode = N->childs[i];
			minOverlapEnlargment = curOverlapEnlargment;
		}
		else if (curOverlapEnlargment == minOverlapEnlargment)
		{
			// Compare MBR area enlargement
			float oldArea;
			float newArea;
			float oldAreaEnl;
			float newAreaEnl;
			float oldDelta;
			float newDelta;

			oldAreaEnl = FindRectangleArea(CalculateEnlargedMBR(choosenNode->MBR, data));
			newAreaEnl = FindRectangleArea(CalculateEnlargedMBR(N->childs[i]->MBR, data));

			oldArea = FindRectangleArea(choosenNode->MBR);
			newArea = FindRectangleArea(N->childs[i]->MBR);

			oldDelta = oldAreaEnl - oldArea;
			newDelta = newAreaEnl - newArea;

			if (oldDelta > newDelta)
				choosenNode = N->childs[i];
			else if (oldDelta == newDelta) {
				// Compare new MBR areas
				if (oldAreaEnl > newAreaEnl)
					choosenNode = N->childs[i];
			}
		}
	}

	return choosenNode;
}

Node* RTree::MinAreaEnlargementNode(Node* N, Spot* data)
{

	Node* choosenNode;
	Rectangle enlargedMBR;

	float minAreaEnlargment = 10000000000000;
	float curAreaEnlargment;

	float oldArea;
	float enlArea;
	
	for (int i = 0; i < N->childs.size(); i++)
	{
		enlargedMBR = CalculateEnlargedMBR(N->childs[i]->MBR, data);

		oldArea = FindRectangleArea(N->childs[i]->MBR);
		enlArea = FindRectangleArea(enlargedMBR);

		curAreaEnlargment = enlArea - oldArea;

		if (minAreaEnlargment > curAreaEnlargment)
		{
			choosenNode = N->childs[i];
			minAreaEnlargment = curAreaEnlargment;
		}
		else if (minAreaEnlargment == curAreaEnlargment) {
			float prevEnlArea;

			prevEnlArea = FindRectangleArea(
				CalculateEnlargedMBR(choosenNode->MBR, data)
			);

			if (prevEnlArea > enlArea)
			{
				choosenNode = N->childs[i];
			}

		}
	}

	return choosenNode;
}

float RTree::FindOverlapArea(Rectangle& A, Rectangle& B)
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

float RTree::FindRectangleArea(Rectangle& a)
{
	return (a.RT.x - a.LB.x) * (a.RT.y - a.LB.y);
}

Rectangle& RTree::CalculateEnlargedMBR(Rectangle& oldMBR, Spot* data)
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