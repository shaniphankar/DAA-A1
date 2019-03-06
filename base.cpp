#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Point.h"
#include "Stack.h"
#define k0 5
using namespace std;


void grahamScan()
{

}

void jarvisMarch(vector<Point> hull, vector<Point> points,int num_points)
{
	
}

void kPS(vector<Point> hull, vector<Point> points,int num_points)
{
	
}

int main(int argc, char** argv)
{
	std::ifstream input("./input/input1.txt");
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
	vector<Point> hullGS;
	vector<Point> hullJM;
	vector<Point> hullKPS;
	jarvisMarch(hull,points,num_points);
	
}