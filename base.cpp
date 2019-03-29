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
#include "VectorOps.h"
#include <unordered_map>
#include <algorithm>
#define k0 5
using namespace std;

GeomOps geomAPI;
VectorOps vecAPI;

std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth);
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
	// cout<<"TUP\n";
	for(int i=0;i<num_points;i++)
	{
		if(points[i].getX()>pUMin.getX() && points[i].getX()<pUMax.getX())
		{
			TUp.push_back(points[i]);
			// TUp[i].printPoint();
		}
	}
	TLo.push_back(pLMin);
	TLo.push_back(pLMax);
	// cout<<"TLo\n";
	for(int i=0;i<num_points;i++)
	{
		if(points[i].getX()>pLMin.getX()&&points[i].getX()<pLMax.getX())
		{
			TLo.push_back(points[i]);
			// TLo[i].printPoint();
		}
	}

	upperHull(pUMin,pUMax,TUp,TUp.size(),0);
	// std::vector<Point> uHull=upperHull(pUMin,pUMax,TUp,TUp.size());
	// std::vector<Point> lHull=lowerHull(pLMin,pLMax,TLo,TLo.size());
}


pair<Point,Point> upperBridge(std::vector<Point> S,int num_points,Point L,int depth)
{
	vector<Point> candidates;
	cout<<"Depth = "<<depth<<endl;
	if(depth==20)
		return make_pair(Point(0,0),Point(0,0));
	Point med=vecAPI.medianOfMedians(S,0,S.size()-1,S.size()/2);
	vecAPI.medianPartition(S,0,S.size()-1,med);
	for(int i=0;i<S.size();i++)
	{
		S[i].printPoint();
	}
	if(S.size()==2)
		return make_pair(S[0],S[1]);
	vector<pair<Point,Point>> pairs;
	int i;
	for(i=0;i<num_points/2;i++)
	{
		pairs.push_back(make_pair(S[i],S[num_points-i-1]));
	}
	if(num_points%2==1)
	{
		candidates.push_back(S[i]);
	}
	vector<pair<double,pair<Point,Point>>> K;
	for(int i=0;i<pairs.size();i++)
	{
		if(pairs[i].first.getX()==pairs[i].second.getX())
		{
			if(pairs[i].first.getY()>pairs[i].second.getY())
				candidates.push_back(pairs[i].first);
			else
				candidates.push_back(pairs[i].second);
		}
		else
		{
			K.push_back(make_pair((pairs[i].first.getY()-pairs[i].second.getY())/(pairs[i].first.getX()-pairs[i].second.getX()),pairs[i]));
			// cout<<K[i].first<<endl;
		}
	}
	vector<double> KSlopesOnly;
	for(int i=0;i<K.size();i++)
	{
		KSlopesOnly.push_back(K[i].first);
	}
	double k=vecAPI.medianOfMedians(KSlopesOnly,0,KSlopesOnly.size()-1,KSlopesOnly.size()/2);
	// cout<<"Median Slope "<<k<<endl;
	vector<pair<Point,Point>> small,equal,large;
	for(int i=0;i<K.size();i++)
	{
		if(K[i].first<k)
		{
			small.push_back(K[i].second);
		}
		else if(K[i].first==k)
		{
			equal.push_back(K[i].second);
		}
		else
		{
			large.push_back(K[i].second);
		}
	}
	vector<Point> max=geomAPI.highestYIntersection(S,k);
	// for(int i=0;i<max.size();i++)
	// {
	// 	max[i].printPoint();
	// }
	Point pk=max[geomAPI.getLeftMost(max,max.size())];
	Point pm=max[geomAPI.getRightMost(max,max.size())];
	if(pk.getX()<=L.getX()&&pm.getY()>L.getX()&&max.size()!=1)
	{
		return make_pair(pk,pm);
	}
	if(pm.getX()<L.getX())
	{
		for(int i=0;i<large.size();i++)
		{
			candidates.push_back(large[i].second);
		}
		for(int i=0;i<equal.size();i++)
		{
			candidates.push_back(equal[i].second);
		}
		for(int i=0;i<small.size();i++)
		{
			candidates.push_back(small[i].first);
			candidates.push_back(small[i].second);
		}
	}
	else if(pk.getX()>L.getX())
	{
		for(int i=0;i<small.size();i++)
		{
			candidates.push_back(small[i].first);
		}
		for(int i=0;i<equal.size();i++)
		{
			candidates.push_back(equal[i].first);
		}
		for(int i=0;i<large.size();i++)
		{
			candidates.push_back(large[i].first);
			candidates.push_back(large[i].second);
		}
	}
	cout<<"Candidates for depth ="<<depth+1<<endl;
	for(int i=0;i<candidates.size();i++)
	{
		candidates[i].printPoint();
	}
	return upperBridge(candidates,candidates.size(),L,depth+1);
}
std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth)
{
	Point a=vecAPI.medianOfMedians(points,0,num_points-1,num_points/2);
	a.printPoint();
	pair<Point,Point> upBridge=upperBridge(points,num_points,a,0);
	cout<<"Depth="<<depth<<"UpperBridge\n";
	upBridge.first.printPoint();
	upBridge.second.printPoint();
}
std::vector<Point> lowerHull(Point pMin,Point pMax,std::vector<Point> points,int num_points)
{
}



int main(int argc, char** argv)
{
	std::ifstream input("./input/input3.txt");
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

	// // Testing medianOfMedians for POints
	// std::vector<Point> v;
	// for(int i=0;i<10;i++)
	// 	v.push_back(Point(10-i,10-i));
	// // for(int i=0;i<10;i++)
	// // 	v.push_back(Point(100-i,100-i));

	// printf("points:\n");
	// for(int i=0;i<v.size();i++)
	// 	v[i].printPoint();
	// vecAPI.medianOfMedians(v,0,v.size()-1,v.size()/2).printPoint();
	
	// //Testing medianOfMedians for Double
	// std::vector<double> v;
	// for(int i=0;i<10;i++)
	// 	v.push_back(10-i);
	// // for(int i=0;i<10;i++)
	// // 	v.push_back(Point(100-i,100-i));

	// printf("points:\n");
	// for(int i=0;i<v.size();i++)
	// 	cout<<v[i]<<endl;
	// cout<<vecAPI.medianOfMedians(v,0,v.size()-1,v.size()/2);
	

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
