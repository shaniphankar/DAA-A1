#ifndef LINE_H
#define LINE_H
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
