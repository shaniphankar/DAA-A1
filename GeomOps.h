#ifndef GEOMOPS_H
#define GEOMOPS_H
#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
class GeomOps
{
    public:
        std::vector<Point> highestYIntersection(std::vector<Point> points, double k);
        double getDistance(Point p1,Point p2);
        double getAngle(Point p1,Point p2);
        int getLeftMost(std::vector<Point> points,int num_points);
        int getRightMost(std::vector<Point> points,int num_points);
        int getTopMost(std::vector<Point> points,int num_points);
        int getBottomMost(std::vector<Point> points,int num_points);
        std::vector<Point> getLeftMostMultiple(std::vector<Point> points,int num_points);
        std::vector<Point> getRightMostMultiple(std::vector<Point> points,int num_points);
        int getOrientation(Point p1,Point p2, Point p3);
};

#endif
