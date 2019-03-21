#include <iostream>
#include "Point.h"
Point::Point()
{
	x=0;
	y=0;
}
Point::Point(double x,double y)
{
	this->x=x;
	this->y=y;
}
double Point::getX()
{
	return x;
}
double Point::getY()
{
	return y;
}	

void Point::printPoint()
{
	std::cout<<this->x<<" "<<this->y<<"\n";
}




