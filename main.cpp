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
