#ifndef VECTOROPS_H
#define VECTOROPS_H
#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
class VectorOps
{
    public:
    	void swap(double* x,double* y);
    	int medianPartition(std::vector<double> &points,int l,int r,double x);
        double medianOfMedians(std::vector<double> &points,int l,int r,int k);
        void swap(Point* x,Point* y);
        int medianPartition(std::vector<Point> &points,int l,int r,Point x);
        static bool sortByX(Point a,Point b);
        Point medianOfMedians(std::vector<Point> &points,int l,int r,int k);
        int findIndex(std::vector<Point> points,Point p);

};

#endif
