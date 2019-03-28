#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
#include "GeomOps.h"

std::vector<Point> GeomOps::highestYIntersection(std::vector<Point> points, double k)
{
    int maxP=0;
    for(int i=1;i<points.size();i++)
    {
        if((points[i].getY()-k*points[i].getX())>(points[maxP].getY()-k*points[maxP].getX()))
            maxP=i;
    }
    std::vector<Point> max;
    for(int i=0;i<points.size();i++)
    {
        if((points[i].getY()-k*points[i].getX())==(points[maxP].getY()-k*points[maxP].getX()))
            max.push_back(points[i]);
    }
    return max;
}

double GeomOps::getDistance(Point p1, Point p2)
{
    return sqrt(pow(p1.getY()-p2.getY(),2)+pow(p1.getX()-p2.getX(),2));
}

double GeomOps::getAngle(Point p1, Point p2)
{
    return atan2(p1.getY()-p2.getY(),p1.getX()-p2.getX());
}

int GeomOps::getLeftMost(std::vector<Point> points,int num_points)
{
    int lMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getX()<points[lMost].getX())
        {
            lMost=i;
        }
    }
    return lMost;
}

int GeomOps::getRightMost(std::vector<Point> points,int num_points)
{
    int rMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getX()>points[rMost].getX())
        {
            rMost=i;
        }
    }
    return rMost;
}

int GeomOps::getBottomMost(std::vector<Point> points,int num_points)
{
    int bMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getY()<points[bMost].getY())
        {
            bMost=i;
        }
    }
    return bMost;
}

int GeomOps::getTopMost(std::vector<Point> points,int num_points)
{
    int tMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getY()>points[tMost].getY())
        {
            tMost=i;
        }
    }
    return tMost;
}

std::vector<Point> GeomOps::getLeftMostMultiple(std::vector<Point> points,int num_points)
{
    int lMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getX()<points[lMost].getX())
        {
            lMost=i;
        }
    }
    std::vector<Point> lMostVec;
    for(int i=0;i<num_points;i++)
    {
        if(points[i].getX()==points[lMost].getX())
        {
            lMostVec.push_back(points[i]);
        }   
    }
    return lMostVec;
}
std::vector<Point> GeomOps::getRightMostMultiple(std::vector<Point> points,int num_points)
{
    int rMost=0;
    for(int i=1;i<num_points;i++)
    {
        if(points[i].getX()>points[rMost].getX())
        {
            rMost=i;
        }
    }
    std::vector<Point> rMostVec;
    for(int i=0;i<num_points;i++)
    {
        if(points[i].getX()==points[rMost].getX())
        {
            rMostVec.push_back(points[i]);
        }   
    }
    return rMostVec;
}
int GeomOps::getOrientation(Point p1,Point p2, Point p3)
{
    double crossProduct=(p2.getY()-p1.getY())*(p3.getX()-p2.getX())-(p2.getX()-p1.getX())*(p3.getY()-p2.getY());
    if(crossProduct==0) 
        return 0;
    else if(crossProduct>0)
        return 1;
    else
        return -1;
    
}
