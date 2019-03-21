#ifndef GEOMOPS_H
#define GEOMOPS_H
#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
class GeomOps
{
    public:
        double getDistance(Point p1,Point p2);
        double getAngle(Point p1,Point p2);
        int getLeftMost(std::vector<Point> points,int num_points);
        int getRightMost(std::vector<Point> points,int num_points);
        std::vector<Point> getLeftMostMultiple(std::vector<Point> points,int num_points);
        std::vector<Point> getRightMostMultiple(std::vector<Point> points,int num_points);
        int getOrientation(Point p1,Point p2, Point p3);
};

#endif
