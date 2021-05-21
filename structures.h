#pragma once
#include <vector>

using namespace std;

//////////////////////////////////////////////////
// Main strutures
//////////////////////////////////////////////////
struct Spot {
    float latitude;
    float longitude;
    string type;
    string subtype;
    string name;
    string address;
};

struct Vector2f { // f - for float, V - for Vandeta
    float x;
    float y;
};

struct Rectangle {
    Vector2f LB; // Left bottom corner
    Vector2f RT; // Top right corner
};

struct Node {
    vector<Node*> childs;
    vector<Spot*> data;
    Node* parent;
    Rectangle MBR;
    bool isLeaf;
};
