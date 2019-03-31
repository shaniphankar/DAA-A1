#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
#include "GeomOps.h"

/*! This function gives the set of points from the input having the highest y coordinate for a line of mentioned slope
\param points input set of points
\param k required slope of line
\return set of points with highest y coordinate
*/
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

/*! This function gives the set of points from the input having the lowest y coordinate for a line of mentioned slope
\param points input set of points
\param k required slope of line
\return set of points with lowest y coordinate
*/
std::vector<Point> GeomOps::lowestYIntersection(std::vector<Point> points, double k)
{
    int minP=0;
    for(int i=1;i<points.size();i++)
    {
        if((points[i].getY()-k*points[i].getX())<(points[minP].getY()-k*points[minP].getX()))
            minP=i;
    }
    std::vector<Point> min;
    for(int i=0;i<points.size();i++)
    {
        if((points[i].getY()-k*points[i].getX())==(points[minP].getY()-k*points[minP].getX()))
            min.push_back(points[i]);
    }
    return min;
}

/*! This funcion return distance between two points
*/
double GeomOps::getDistance(Point p1, Point p2)
{
    return sqrt(pow(p1.getY()-p2.getY(),2)+pow(p1.getX()-p2.getX(),2));
}

/*! This funcion returns angle between two points
*/
double GeomOps::getAngle(Point p1, Point p2)
{
    return atan2(p1.getY()-p2.getY(),p1.getX()-p2.getX());
}

/*! This funcion returns index of left most point
*/
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

/*! This funcion returns index of right most point
*/
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

/*! This funcion returns index of bottom most point
*/
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

/*! This funcion returns index of top most point
*/
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

/*! This funcion returns all the left most points meaning all those having least x coordinate
*/
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

/*! This funcion returns all the right most points meaning all those having highest x coordinate
*/
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

/*! This funcion returns signed area for three points
*/
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

/*! This funcion returns all the bottom points meaning all those having lowest y coordinate
*/
std::vector<Point> GeomOps::getBottomMostPoints(std::vector<Point> points,int num_points)
{
    int i,bottomMostIndx=0;
    for(i=0;i<num_points;i++)
    {
        if(points[i].getY()<points[bottomMostIndx].getY())
        {

            bottomMostIndx=i;
        }
    }

    std::vector<Point> BottomMostpoints;

    for(i=0;i<num_points;i++)
    {
        if(std::abs(points[i].getY()-points[bottomMostIndx].getY())<0.000001)
        {
            BottomMostpoints.push_back(points[i]);
        }
    }

    return BottomMostpoints;
}

