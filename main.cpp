#include <fstream>
#include <vector>
#include <string>
#include "rTree.h"


//////////////////////////////////////////////////
// Functions for parsing data
//////////////////////////////////////////////////
vector<Spot> readSpotList(string);

//////////////////////////////////////////////////
// R*-tree functions
//////////////////////////////////////////////////




int main() {
    setlocale(LC_ALL, "ru");

    vector<Spot> geoSpots;
    RTree dataTree;

    geoSpots = readSpotList("c:/users/roman/source/repos/laba5/data/spots.csv");

  

    dataTree.InsertData(&geoSpots[0]);

    cout << dataTree.root->data[0]->latitude << endl;
    cout << dataTree.root->data[0]->longitude<< endl;
    cout << dataTree.root->data[0]->type << endl;

    return 0;
}


vector<Spot> readSpotList(string path){
    ifstream file(path);

    if (!file.is_open()){
        cout << "Failed to open spot list file!" << endl;
    }

    string buff;
    vector<Spot> geoSpots;

    while (!file.eof()){
        Spot newGeoSpot;

        getline(file, buff, ';');
        newGeoSpot.latitude = stof(buff);

        getline(file, buff, ';');
        newGeoSpot.longitude = stof(buff);

        getline(file, buff, ';');
        newGeoSpot.type = buff;

        getline(file, buff, ';');
        newGeoSpot.subtype = buff;

        getline(file, buff, ';');
        newGeoSpot.name = buff;

        getline(file, buff, ';');
        newGeoSpot.address = buff;

        getline(file, buff, '\n'); // Next spot

        geoSpots.push_back(newGeoSpot);
    }

    return geoSpots;
}

bool PointIntersect(Spot *point, Rectangle rec)
{
    double x1 = rec.LB.x,y1 = rec.LB.y;
    double x2 = rec.RT.x,y2 = rec.RT.y;
    if(point->longitude < x1 || point->longitude > x2 || point->latitude < y1 || point->latitude > y2)
        return false;
    return true;
}

bool RectIntersect(Rectangle rect1,Rectangle rect2)
{
    if ((rect1.LB.x <= rect2.RT.x || rect1.RT.x >= rect2.LB.x) && (rect1.LB.y <= rect2.RT.y || rect1.RT.y >= rect2.LB.y))
        return true;
    return false;
}

void findPointsInRect(Node* node, Rectangle rect, string type, string subtype, vector< Spot* >& result) {
    if (node->childs.size() > 0 || node->isLeaf== false) {
        if (RectIntersect(node->MBR, rect)) {
            for (int i = 0; i < node->childs.size(); i++) {
                findPointsInRect(node->childs[i], rect, type, subtype, result);
            }
        }
    }
    else
        for(auto i = 0 ;i<node->data.size();i++)
        {

                if (PointIntersect(node->data[i], rect) && node->data[i]->type == type && node->data[i]->subtype == subtype)
                {
                    result.push_back(node->data[i]);
                }

        }

}