#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <cfloat>
#include <cmath>
using namespace std;


struct Spot{
    float latitude;
    float longitude;
    string type;
    string subtype;
    string name;
    string address;
};
/*class Node
        {
            Node Child1,Child2;
            int maxSize = 10;
            list<Spot> Points;
        public:
            bool IsParent = false;
            int Size = 0;
            double xMax, xMin, yMax, yMin;

        };

*/


struct Point {
        double x;
        double y;
        Point()
        {
            x = DBL_MAX;
            y = DBL_MAX;
        }
        Point(double vx, double vy){
            x = vx;
            y = vy;
        }
};
/*struct boundingBox
        {
    point  left,right;
    double perimetr,ploshya;
        };

struct obj
        {

    boundingBox mbr;
    Spot * i;
        };

class node
        {
    boundingBox nmbr;
    node* parent;
    vector<node*> children;
    vector<obj*> objects;
    bool isLeaf;
    int level;
    bool getIsLeaf();
    node * getChild(node*);
    obj
        };
*/
/*bool isLeaf,isNonLeaf;
vector<Spot*> tochki;
vector<node*> children;
node* parent;
boundingBox MBR;
vector<boundingBox> I;*/
class rTree
        {
            bool isParent = false;
            int maxLong,minLong,maxLatt,minLatt;
            int size = 0,maxSize = 10;
            list<Spot> points;
        public:
            void add(Spot p)
            {
                if(!isParent)
                {
                    points.push_back(p);
                    size++;
                    if (size == 1)
                    {
                        minLatt = maxLatt = p.latitude;
                        minLong = maxLong = p.longitude;
                    }
                    else
                    {
                        maxLong = maxLong > p.longitude ? maxLong : p.longitude;
                        minLong = minLong < p.longitude ? minLong : p.longitude;
                        maxLatt = maxLatt > p.latitude ? maxLatt : p.latitude;
                        minLatt = minLatt < p.latitude ? minLatt : p.latitude;
                        //if(size>maxSize) divivide;
                    }
                }

            }


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
