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
#include <algorithm>
#define k0 5
using namespace std;

GeomOps geomAPI;

std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points);
std::vector<Point> lowerHull(Point pMin,Point pMax,std::vector<Point> points,int num_points);

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
	Point pUMin,pUMax,pLMin,pLMax;
	vector<Point> lMostVec=geomAPI.getLeftMostMultiple(points,num_points);
	int numPointsLeft=lMostVec.size();
	if(numPointsLeft==1)
	{
		pUMin=lMostVec[0];
		pLMin=lMostVec[0];
	}
	else
	{
		pUMin=lMostVec[geomAPI.getTopMost(lMostVec,numPointsLeft)];
		pLMin=lMostVec[geomAPI.getBottomMost(lMostVec,numPointsLeft)];
	}
	vector<Point> rMostVec=geomAPI.getRightMostMultiple(points,num_points);
	int numPointsRight=rMostVec.size();
	if(numPointsRight==1)
	{
		pUMax=rMostVec[0];
		pLMax=rMostVec[0];
	}
	else
	{
		pUMax=rMostVec[geomAPI.getTopMost(rMostVec,numPointsRight)];
		pLMax=rMostVec[geomAPI.getBottomMost(rMostVec,numPointsRight)];
	}
	// pLMin.printPoint();
	// pLMax.printPoint();
	// pUMin.printPoint();
	// pUMax.printPoint();
	vector<Point> TUp;
	vector<Point> TLo;
	TUp.push_back(pUMin);
	TUp.push_back(pUMax);
	for(int i=0;i<num_points;i++)
	{
		if(points[i].getX()>pUMin.getX())
		{
			TUp.push_back(points[i]);
		}
	}
	TLo.push_back(pLMin);
	TLo.push_back(pLMax);
	for(int i=0;i<num_points;i++)
	{
		if(points[i].getX()>pLMin.getX())
		{
			TLo.push_back(points[i]);
		}
	}
	// std::vector<Point> uHull=upperHull(pUMin,pUMax,TUp,TUp.size());
	// std::vector<Point> lHull=lowerHull(pLMin,pLMax,TLo,TLo.size());
}

void swap(Point* x,Point* y){
	Point temp;
	
	temp = *x;
	*x=*y;
	*y=temp;
}

int medianPartition(std::vector<Point> &points,int l,int r,Point x){
	/*printf("medianPartition start:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	int z;
	for(z=l;z<r;z++)
		if(points[z].getX()==x.getX() && points[z].getY()==x.getY())
			break;

	swap(&points[z],&points[r]);

	int i=l;

	for(int z=l;z<r;z++){
		if(points[z].getX()<=x.getX()){
			swap(&points[z],&points[i]);
			i++;
		}
	}

	swap(&points[i],&points[r]);

/*	printf("printing vec:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
		cout<<"\t";
	}
	cout<<"\n";*/

	/*printf("medianPartition end here:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	return i;
}

bool sortByX(Point a,Point b){
	return (a.getX() < b.getX());
}

int c=10;
Point medianOfMedians(std::vector<Point> &points,int l,int r,int k)
{	//dividing into buckets
	//printf("arguments: l:%d r:%d k:%d\n",l,r,k );
	
	c--;
	if(c<0)
		exit(0);

	int nofOfPts= (r-l+1);

	std::vector<Point> medianVec;

	for(int i=l;i<=r;i=i+5){
		int start=i;
		int end= (i+5<=r?i+5:r+1);
		sort(points.begin()+start,points.begin()+end,sortByX);
		medianVec.push_back(points[(start+end)/2]);

	}
/*
	cout<<"c:"<<c<<"\n";
	for(int l=0;l<medianVec.size();l++){
		medianVec[l].printPoint();
		cout<<"\n";
	}*/

	Point medOfMed = (medianVec.size()==1? medianVec[0]: medianOfMedians(medianVec,0,medianVec.size()-1,medianVec.size()/2) );

	/*printf("medOfMed:\n");
	medOfMed.printPoint();*/
	int medianPosition = medianPartition(points,l,r, medOfMed);
	//printf("medianPosition: %d\n",medianPosition );

	//cout<<"ans:\n";
	if(medianPosition - l == k) return medOfMed;
	else if(k>medianPosition - l) return medianOfMedians(points,medianPosition + 1, r, k - medianPosition - 1 +  l );
	else return medianOfMedians(points,l,medianPosition - 1, k);
}

std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points)
{
}
std::vector<Point> lowerHull(Point pMin,Point pMax,std::vector<Point> points,int num_points)
{
}

int main(int argc, char** argv)
{
	std::ifstream input("./input/input1.txt");
	//std::ifstream input("./input/input7.txt");//Degeneracy case with 2 leftmost points
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

	std::vector<Point> v;
	for(int i=0;i<10;i++)
		v.push_back(Point(10-i,10-i));
	for(int i=0;i<10;i++)
		v.push_back(Point(100-i,100-i));

	printf("points:\n");
	for(int i=0;i<v.size();i++)
		v[i].printPoint();

	medianOfMedians(v,0,v.size()-1,v.size()/2).printPoint();
	// jarvisMarch(hullJM,points,num_points);
	// std::ofstream outputJM("./outputJM/output7JM.txt");
	// int num_points_hull=hullJM.size();
	// for(int i=0;i<num_points_hull;i++)
	// {
	// 	outputJM<<hullJM[i]<<" "<<hullJM[(i+1)%num_points_hull]<<"\n";
	//     output<<hullJM[i]<<" "<<hullJM[(i+1)%num_points_hull]<<"\n";
	//     cout<<hullJM[i]<<" "<<hullJM[(i+1)%num_points_hull]<<endl;
	// }
}
