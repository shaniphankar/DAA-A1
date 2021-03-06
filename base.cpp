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

//! Provides all the geometrical operations useful for various convex hull methods (imported file)
GeomOps geomAPI;
//! Provides all the median algorithms required for convex hull algorithms
VectorOps vecAPI;

Point refpt;

std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth);
std::vector<Point> lowerHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth);

std::ofstream outputKPS1("./outputKPS/output6KPSUpBridge.txt");
std::ofstream outputKPS2("./outputKPS/output6KPSUpLeft.txt");
std::ofstream outputKPS3("./outputKPS/output6KPSUpRight.txt");
std::ofstream outputKPS4("./outputKPS/output6KPSLowBridge.txt");
std::ofstream outputKPS5("./outputKPS/output6KPSLowLeft.txt");
std::ofstream outputKPS6("./outputKPS/output6KPSLowRight.txt");
	

/*! This function helps in comparing signed area of two points w.r.t reference base point
*/
bool comparator(Point p1,Point p2)
{
    int orient=geomAPI.getOrientation(refpt,p1,p2);
    if(orient==-1)
    {
        return true;
    }
    if(orient==0)
    {
        if(geomAPI.getDistance(refpt,p1)<geomAPI.getDistance(refpt,p2))
        {
            return true;
        }
    }
    return false;
}

/*! This function gives the points on convec hull for the input set using Graham Scan algorithm
\param points input set of points
\param num_points number of points in input
\return return points on the convex hull
*/
vector<Point> grahamScan(vector<Point> points,int num_points)
{
	vector<Point> bottomMostPoints=geomAPI.getBottomMostPoints(points,num_points);
	int leftMost=geomAPI.getLeftMost(bottomMostPoints,bottomMostPoints.size());
	int lefty=vecAPI.findIndex(points,bottomMostPoints[leftMost]);
	vecAPI.swap(&points[0],&points[lefty]);
	refpt=points[0];
	sort(points.begin()+1,points.end(),comparator);

	int m=1;
	for(int i=0;i<points.size();i++)
	{
		while(i<(points.size()-1)&&geomAPI.getOrientation(points[0],points[i],points[i+1])==0)
			i++;
		points[m]=points[i];
		m++;
	} 

	Stack<Point> s;
	s.push(points[0]);
	s.push(points[1]);
	s.push(points[2]);
	for(int i=3;i<m;i++)
	{
		while(geomAPI.getOrientation(s.peek2(),s.peek(),points[i])!=-1)
		{
			s.pop();
		}
		s.push(points[i]);
	}

	vector<Point> convexHull;
	while(!(s.isEmpty()))
	{
		convexHull.push_back(s.pop());
	}
	return convexHull;
}

/*! This function gives convex hull for a set of points using Jarvis March Algorithm
\param hull This is the hull vector to be filled using the algorithm
\param points This is the set of input points
\param num_points Number of points in input 
*/
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

/*! This function gives convex hull for a set of points using Kirkpatrick Siedel Algorithm
\param points Set of input points
\param number of points in input
\return set of points in hull
*/
vector<Point> kPS(vector<Point> points,int num_points)
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

	vector<Point> hullUp=upperHull(pUMin,pUMax,TUp,TUp.size(),0);
	// return hullUp;
	vector<Point> hullLo=lowerHull(pLMin,pLMax,TLo,TLo.size(),0);
	vector<Point> hull;
	for(int i=0;i<hullUp.size();i++)
		hull.push_back(hullUp[i]);
	for(int i=hullLo.size()-1;i>=0;i--)
		hull.push_back(hullLo[i]);
	hull.push_back(hullUp[0]);
	return hull;
	// std::vector<Point> uHull=upperHull(pUMin,pUMax,TUp,TUp.size());
	// std::vector<Point> lHull=lowerHull(pLMin,pLMax,TLo,TLo.size());
}

/*! This function finds of upper bridge line described by the two points
\param S input set of points
\param num_points number of points in input
\param L median line described by a point
\param depth number of times the function has recursed
\return returns a pair of points describing upper bridge
*/
pair<Point,Point> upperBridge(std::vector<Point> S,int num_points,Point L,int depth)
{
	vector<Point> candidates;
	// cout<<"Bridge depth = "<<depth<<endl;
	Point med=vecAPI.medianOfMedians(S,0,S.size()-1,S.size()/2);
	vecAPI.medianPartition(S,0,S.size()-1,med);
	// for(int i=0;i<S.size();i++)
	// {
	// 	S[i].printPoint();
	// }
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
	if(pk.getX()<=L.getX()&&pm.getX()>L.getX()&&max.size()!=1)
	{
		return make_pair(pk,pm);
	}
	if(pm.getX()<=L.getX())
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
	if(pk.getX()>L.getX())
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
	// cout<<"Candidates for Bridge depth ="<<depth+1<<endl;
	// for(int i=0;i<candidates.size();i++)
	// {
	// 	candidates[i].printPoint();
	// }
	return upperBridge(candidates,candidates.size(),L,depth+1);
}

/*! This function calculates upper hull from given set of points
\param pMin Point with minimum x coordinate
\param pMax Point with maximum x coordinate
\param points set of input points
\param num_points number of points in input
\param depth number of times the function is recursed
\return Returns a set of points in upper hull
*/
std::vector<Point> upperHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth)
{
	vector<Point> hull;
	if(num_points==1)
	{
		vector<Point> hull;
		hull.push_back(pMin);
		return hull;
	}
	if(num_points==2)
	{
		vector<Point> hull;
		hull.push_back(pMin);
		hull.push_back(pMax);
		return hull;
	}
	Point a=vecAPI.medianOfMedians(points,0,num_points-1,num_points/2);
	// a.printPoint();
	pair<Point,Point> upBridge=upperBridge(points,num_points,a,0);
	// cout<<"Hull Depth="<<depth<<"\nUpperBridge\n";
	// upBridge.first.printPoint();
	// upBridge.second.printPoint();
	vector<Point> TLeft,TRight;
	TLeft.push_back(upBridge.first);
	TRight.push_back(upBridge.second);
	TLeft.push_back(pMin);
	TRight.push_back(pMax);
	double mL=(upBridge.first.getY()-pMin.getY())/(upBridge.first.getX()-pMin.getX());
	double mR=(upBridge.second.getY()-pMax.getY())/(upBridge.second.getX()-pMax.getX());
	for(int i=0;i<points.size();i++)
	{
		if((points[i].getX()<upBridge.first.getX())&&points[i].getY()>(mL*(points[i].getX()-pMin.getX())+pMin.getY()))
			TLeft.push_back(points[i]);
	}
	for(int i=0;i<points.size();i++)
	{
		if((points[i].getX()>upBridge.second.getX())&&points[i].getY()>(mR*(points[i].getX()-pMax.getX())+pMax.getY()))
			TRight.push_back(points[i]);
	}
	// cout<<"TLeft size"<<TLeft.size()<<endl;
	// for(int i=0;i<TLeft.size();i++)
	// 	TLeft[i].printPoint();
	// cout<<"TRight size "<<TRight.size()<<endl;
	// for(int i=0;i<TRight.size();i++)
	// 	TRight[i].printPoint();
	vector<Point> upHullL;
	vector<Point> upHullR;
	if(TLeft.size()>=2)
		upHullL=upperHull(pMin,upBridge.first,TLeft,TLeft.size(),depth+1);
	if(TRight.size()>=2)
		upHullR=upperHull(upBridge.second,pMax,TRight,TRight.size(),depth+1);
	for(int i=0;i<upHullL.size();i++)
	{
		hull.push_back(upHullL[i]);
	}
	hull.push_back(upBridge.first);
	hull.push_back(upBridge.second);
	for(int i=0;i<upHullR.size();i++)
	{
		hull.push_back(upHullR[i]);
	}
	if(depth==0)
	{
		for(int i=0;i<upHullL.size();i++)
		{
			outputKPS2<<upHullL[i].getX()<<" "<<upHullL[i].getY()<<"\n";
		}
		outputKPS1<<upBridge.first.getX()<<" "<<upBridge.first.getY()<<"\n";
		outputKPS1<<upBridge.second.getX()<<" "<<upBridge.second.getY()<<"\n";
		for(int i=0;i<upHullR.size();i++)
		{
			outputKPS3<<upHullR[i].getX()<<" "<<upHullR[i].getY()<<"\n";
		}
	}
	return hull;
}

/*! This function finds of lower bridge line described by the two points
\param S input set of points
\param num_points number of points in input
\param L median line described by a point
\param depth number of times the function has recursed
\return returns a pair of points describing lower bridge
*/
pair<Point,Point> lowerBridge(std::vector<Point> S,int num_points,Point L,int depth)
{
	vector<Point> candidates;
	cout<<"Bridge depth = "<<depth<<endl;
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
			if(pairs[i].first.getY()<pairs[i].second.getY())
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
	vector<Point> max=geomAPI.lowestYIntersection(S,k);
	// for(int i=0;i<max.size();i++)
	// {
	// 	max[i].printPoint();
	// }
	Point pk=max[geomAPI.getLeftMost(max,max.size())];
	Point pm=max[geomAPI.getRightMost(max,max.size())];
	if(pk.getX()<=L.getX()&&pm.getX()>L.getX()&&max.size()!=1)
	{
		return make_pair(pk,pm);
	}
	if(pm.getX()<=L.getX())
	{
		for(int i=0;i<small.size();i++)
		{
			candidates.push_back(small[i].second);
		}
		for(int i=0;i<equal.size();i++)
		{
			candidates.push_back(equal[i].second);
		}
		for(int i=0;i<large.size();i++)
		{
			candidates.push_back(large[i].first);
			candidates.push_back(large[i].second);
		}
	}
	if(pk.getX()>L.getX())
	{
		for(int i=0;i<large.size();i++)
		{
			candidates.push_back(large[i].first);
		}
		for(int i=0;i<equal.size();i++)
		{
			candidates.push_back(equal[i].first);
		}
		for(int i=0;i<small.size();i++)
		{
			candidates.push_back(small[i].first);
			candidates.push_back(small[i].second);
		}
	}
	cout<<"Candidates for Bridge depth ="<<depth+1<<endl;
	for(int i=0;i<candidates.size();i++)
	{
		candidates[i].printPoint();
	}
	return lowerBridge(candidates,candidates.size(),L,depth+1);
}

/*! This function calculates lower hull from given set of points
\param pMin Point with minimum x coordinate
\param pMax Point with maximum x coordinate
\param points set of input points
\param num_points number of points in input
\param depth number of times the function is recursed
\return Returns a set of points in lower hull
*/
std::vector<Point> lowerHull(Point pMin,Point pMax,std::vector<Point> points,int num_points,int depth)
{	
	vector<Point> hull;
	if(num_points==1)
	{
		vector<Point> hull;
		hull.push_back(pMin);
		return hull;
	}
	if(num_points==2)
	{
		vector<Point> hull;
		hull.push_back(pMin);
		hull.push_back(pMax);
		return hull;
	}
	Point a=vecAPI.medianOfMedians(points,0,num_points-1,num_points/2);
	// a.printPoint();
	pair<Point,Point> lowBridge=lowerBridge(points,num_points,a,0);
	cout<<"Hull Depth="<<depth<<"\nLowerBridge\n";
	lowBridge.first.printPoint();
	lowBridge.second.printPoint();
	vector<Point> TLeft,TRight;
	TLeft.push_back(lowBridge.first);
	TRight.push_back(lowBridge.second);
	TLeft.push_back(pMin);
	TRight.push_back(pMax);
	double mL=(lowBridge.first.getY()-pMin.getY())/(lowBridge.first.getX()-pMin.getX());
	double mR=(lowBridge.second.getY()-pMax.getY())/(lowBridge.second.getX()-pMax.getX());
	for(int i=0;i<points.size();i++)
	{
		if((points[i].getX()<lowBridge.first.getX())&&points[i].getY()<(mL*(points[i].getX()-pMin.getX())+pMin.getY()))
			TLeft.push_back(points[i]);
	}
	for(int i=0;i<points.size();i++)
	{
		if((points[i].getX()>lowBridge.second.getX())&&points[i].getY()<(mR*(points[i].getX()-pMax.getX())+pMax.getY()))
			TRight.push_back(points[i]);
	}
	cout<<"TLeft size "<<TLeft.size()<<endl;
	cout<<"TRight size "<<TRight.size()<<endl;
	vector<Point> lowHullL;
	vector<Point> lowHullR;
	if(TLeft.size()>=2)
		lowHullL=lowerHull(pMin,lowBridge.first,TLeft,TLeft.size(),depth+1);
	if(TRight.size()>=2)
		lowHullR=lowerHull(lowBridge.second,pMax,TRight,TRight.size(),depth+1);
	for(int i=0;i<lowHullL.size();i++)
	{
		hull.push_back(lowHullL[i]);
	}
	hull.push_back(lowBridge.first);
	hull.push_back(lowBridge.second);
	for(int i=0;i<lowHullR.size();i++)
	{
		hull.push_back(lowHullR[i]);
	}
	if(depth==0)
	{
		for(int i=0;i<lowHullL.size();i++)
		{
			outputKPS5<<lowHullL[i].getX()<<" "<<lowHullL[i].getY()<<"\n";
		}
		outputKPS4<<lowBridge.first.getX()<<" "<<lowBridge.first.getY()<<"\n";
		outputKPS4<<lowBridge.second.getX()<<" "<<lowBridge.second.getY()<<"\n";
		for(int i=0;i<lowHullR.size();i++)
		{
			outputKPS6<<lowHullR[i].getX()<<" "<<lowHullR[i].getY()<<"\n";
		}
	}
	return hull;
}




int main(int argc, char** argv)
{
	std::ifstream input("./input/input6.txt");
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
	//vector<int> hullGS;
	vector<int> hullJM;
	vector<Point> hullKPS;
	hullKPS=kPS(points,num_points);
	for(int i=0;i<hullKPS.size();i++)
		hullKPS[i].printPoint();
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

	// std::ofstream outputKPS("./outputKPS/output2KPS.txt");
	// int num_points_hull=hullKPS.size();
	// for(int i=0;i<num_points_hull;i++)
	// {
	// 	outputKPS<<hullKPS[i].getX()<<" "<<hullKPS[i].getY()<<"\n";
	// }
	
// 	vector<Point> gsHull=grahamScan(points,num_points);
// 	std::ofstream outputGS("./outputGS/output1GS.txt");
// 	int num_points_hull=gsHull.size();
// 	for(int i=0;i<num_points_hull;i++)
// 	{
// 		outputGS<<gsHull[i].getX()<<" "<<gsHull[i].getY()<<"\n";
// 	}

	std::ofstream outputKPS("./outputKPS/output6KPS.txt");
	int num_points_hull=hullKPS.size();
	for(int i=0;i<num_points_hull;i++)
	{
		outputKPS<<hullKPS[i].getX()<<" "<<hullKPS[i].getY()<<"\n";
	}
}
