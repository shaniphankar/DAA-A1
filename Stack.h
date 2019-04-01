#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
#define MAX 10000
template<class T>
/*! \class Stack
    \brief Simple Stack implementation

This class defines a stack and its important functions for respective objects using template.
*/
class Stack
{
	public:
		Stack()
		{
			arr = new T[MAX];
			top=-1;
		}
		int size()
		{
			return top+1;
		}
		bool isEmpty()
		{
		if(top==-1)
			return true;
		else
			return false;
		}
		void push(T elem)
		{
			arr[++top]=elem;
		}
		T pop()
		{
			if(top==-1)
			{
				std::cout<<"Underflow. Terminating program"<<std::endl;
				exit(EXIT_FAILURE);
			}
			return arr[top--];
		}
		T peek()
		{
			if(top!=-1)
			{
				return arr[top];
			}
		}
		T peek2()
		{
			if(top-1!=-1)
			{
				return arr[top-1];
			}
		}
	private:
		T *arr;
		int top;
};

#endif
