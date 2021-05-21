#pragma once
#include <iostream>
#include "structures.h"

using namespace std;

class RTree
{
public:
	RTree();
	~RTree();

	Node* root; // Pointer to tree root
	
	void InsertData(Spot*);

private:
	void Insert(Spot*);
	Node* ChooseSubtree(Spot*);

	

	vector<Node*> MinOverlapEnlargeNodes(Node*, Spot*);
	float FindOverlapArea(Rectangle , Rectangle );
	Rectangle CalculateEnlargedMBR(Rectangle&, Spot*);

	int leafLevel; // Tree level, where the leaves are
};