#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Spot{
    float latitude;
    float longitude;
    string type;
    string subtype;
    string name;
    string address;
};

vector<Spot> readSpotList(string);
float stringToFloat(string);

int main() {
    vector<Spot> geoSpotsList;

    geoSpotsList = readSpotList("spots.csv");


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
