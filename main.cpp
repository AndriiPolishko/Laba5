#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cfloat>
#include <cmath>
using namespace std;

struct Spot
        {
    float latitude;
    float longitude;
    string type;
    string subtype;
    string name;
    string address;
};

struct Mbr
        {
    Spot leftDown,rightUp;
        };

vector<Spot> readSpotList(string);
float stringToFloat(string);

int main() {
    vector<Spot> geoSpotsList;

    geoSpotsList = readSpotList("spots.csv");
for(int i = 0 ;i<geoSpotsList.size();i++)
    cout<<geoSpotsList[i].latitude<<endl;

    return 0;
}

vector<Spot> readSpotList(string path){
    ifstream file(path);

    cout << "Here" << endl;

    if (!file.is_open()){
        cout << "Failed to open spot list file!" << endl;
    }

    string buff;
    vector<Spot> geoSpots;

    while (!file.eof()){
        Spot newGeoSpot;

        getline(file, buff, ';');
        newGeoSpot.latitude = stringToFloat(buff);

        getline(file, buff, ';');
        newGeoSpot.longitude = stringToFloat(buff);

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

float stringToFloat(string strNum){

    for (int i = 0; i < strNum.size(); ++i) {
        if (strNum[i] == ',')
            strNum[i]='.';
    }

    return stof(strNum);
}

bool intersectPointRectangle(Spot point, Mbr rect) {
    double x1 = rect.leftDown.longitude, y1 = rect.leftDown.latitude,
            x2 = rect.rightUp.longitude, y2 = rect.rightUp.latitude;
    if (point.longitude < x1 || point.longitude > x2 || point.latitude < y1 || point.latitude > y2)
        return false;
    return true;
}

bool intersectRectangles(Mbr rect1, Mbr rect2){
    if ((rect1.leftDown.longitude <= rect2.rightUp.longitude || rect1.rightUp.longitude >= rect2.leftDown.longitude) &&
        (rect1.leftDown.latitude <= rect2.rightUp.latitude || rect1.rightUp.latitude >= rect2.leftDown.latitude))
        return true;
    return false;
}

bool intersectCircleRectangle(Spot point, double R, Mbr rect)
{
    double centerX = (rect.leftDown.longitude + rect.rightUp.longitude) / 2,
            centerY = (rect.leftDown.latitude + rect.rightUp.latitude) / 2,
            width = -rect.leftDown.longitude + rect.rightUp.longitude,
            height = -rect.leftDown.latitude + rect.rightUp.latitude;
    double dx = abs(point.longitude - centerX);
    double dy = abs(point.latitude - centerY);

    if (dx > width / 2 + R) { return false; }
    if (dy > height / 2 + R) { return false; }

    if (dx <= width / 2) { return true; }
    if (dy <= height / 2) { return true; }

    double cornerDistance = pow(dx - width / 2,  2) + pow(dy - height / 2, 2);

    return cornerDistance <= pow(R, 2);
}

bool intersectCirclePoint(Spot center, double R, Spot point) {
    return pow(center.longitude - point.longitude, 2) + pow(center.latitude - point.latitude, 2) <= pow(R, 2);
}