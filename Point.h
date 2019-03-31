#ifndef POINT_H
#define POINT_H
#include <iostream>

/*! \class Point
    \brief This defines a 2-D point with common functionalities to set and retrieve coordinate values
*/
class Point
{
	public:
		Point();
		Point(double x,double y);
		double getX();
		double getY();
		void setX(double x);
		void setY(double y);
		void printPoint();
	private:
		double x; 
		double y;
};

#endif
