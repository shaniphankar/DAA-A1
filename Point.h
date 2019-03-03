#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
	public:
		Point();
		Point(double x,double y);
		double getX();
		double getY();
	private:
		double x; 
		double y;
};

#endif
