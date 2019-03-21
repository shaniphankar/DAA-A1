#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Point.h"
#include "Stack.h"
#include "GeomOps.h"
#define k0 5
using namespace std;

GeomOps geomAPI;

void grahamScan()
{

}

void jarvisMarch(vector<int> &hull, vector<Point> points,int num_points)
{
	int leftMost=geomAPI.getLeftMost(points,num_points);
	//cout<<points[lMost].getX()<<" "<<points[lMost].getY()<<endl;
    hull.push_back(leftMost);
    int current=leftMost;
    while(true)
    {
        int next = (current+1)%num_points;
        for(int i=0;i<num_points;i++)
        {
            if(i==current)
                continue;
            int oriFlag=geomAPI.getOrientation(points[current],points[i],points[next]);
            if(oriFlag<0 || (oriFlag==0 && geomAPI.getDistance(points[i],points[current])>geomAPI.getDistance(points[next],points[current])))
            {
                next=i;
            }
        }
        current=next;
        if(current==leftMost)
            break;
        hull.push_back(next);
    }
}

void kPS(vector<int> &hull, vector<Point> points,int num_points)
{
	vector<Point> lMostVec=geomAPI.getLeftMostMultiple(points,num_points);
	int num_points_hull=lMostVec.size();
	for(int i=0;i<num_points_hull;i++)
	{
		cout<<lMostVec[i].getX()<<" "<<lMostVec[i].getY()<<endl;
	}
}

int main(int argc, char** argv)
{
	// std::ifstream input("./input/input1.txt");
	std::ifstream input("./input/input7.txt");//Degeneracy case with 2 leftmost points
	vector<Point> points;
	string line_data;
	int fLineFlag=0;
	int num_points;
	while(getline(input,line_data))
	{
		if(fLineFlag==0)
		{
			fLineFlag++;
			stringstream line_stream(line_data);
			line_stream>>num_points;
			continue;
		}
		istringstream line_stream(line_data);
		double x,y;
		line_stream>>x>>y;
		points.push_back(Point(x,y));
	}
	vector<int> hullGS;
	vector<int> hullJM;
	vector<int> hullKPS;
	kPS(hullKPS,points,num_points);
	// jarvisMarch(hullJM,points,num_points);
	// std::ofstream outputJM("./outputJM/output6JM.txt");
	// int num_points_hull=hullJM.size();
	// for(int i=0;i<num_points_hull;i++)
	// {
	//     output<<hullJM[i]<<" "<<hullJM[(i+1)%num_points_hull]<<"\n";
	//     //cout<<hullJM[i]<<" "<<hullJM[(i+1)%num_points_hull]<<endl;
	// }
}
