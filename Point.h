#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
	public:
		Point();
		Point(int x,int y);
		int getX();
		int getY();
	private:
		int x; 
		int y;
};

#endif
