#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "VectorOps.h"

/*! This funtion simply swaps two double values
*/
void VectorOps::swap(double* x,double* y){
	double temp;

	temp = *x;
	*x=*y;
	*y=temp;
}

/*! This function separates the input set across the median point along x axis
\param points input set
\param l left index
\param r right index
\param x x coordinate of median point
\return gives the position of median point after final partitioning
*/
int VectorOps::medianPartition(std::vector<double> &points,int l,int r,double x){
	/*printf("medianPartition start:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	int z;
	for(z=l;z<r;z++)
		if(points[z]==x)
			break;

	swap(&points[z],&points[r]);

	int i=l;

	for(int z=l;z<r;z++){
		if(points[z]<=x){
			swap(&points[z],&points[i]);
			i++;
		}
	}

	swap(&points[i],&points[r]);

/*	printf("printing vec:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
		cout<<"\t";
	}
	cout<<"\n";*/

	/*printf("medianPartition end here:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	return i;
}

/*! This functions finds the median of a set of points using medians of median method
\param points input set of points- only single coordinate
\param l left index
\param r right index
\param k kth smallest element to find
\return returns median point
*/
double VectorOps::medianOfMedians(std::vector<double> &points,int l,int r,int k)
{	//dividing into buckets
	//printf("arguments: l:%d r:%d k:%d\n",l,r,k );

	int nofOfPts= (r-l+1);

	std::vector<double> medianVec;

	for(int i=l;i<=r;i=i+5){
		int start=i;
		int end= (i+5<=r?i+5:r+1);
		sort(points.begin()+start,points.begin()+end);
		medianVec.push_back(points[(start+end)/2]);
	}
/*
	cout<<"c:"<<c<<"\n";
	for(int l=0;l<medianVec.size();l++){
		medianVec[l].printPoint();
		cout<<"\n";
	}*/

	double medOfMed = (medianVec.size()==1? medianVec[0]: medianOfMedians(medianVec,0,medianVec.size()-1,medianVec.size()/2) );

	/*printf("medOfMed:\n");
	medOfMed.printPoint();*/
	int medianPosition = medianPartition(points,l,r, medOfMed);
	//printf("medianPosition: %d\n",medianPosition );

	//cout<<"ans:\n";
	if(medianPosition - l == k) return medOfMed;
	else if(k>medianPosition - l) return medianOfMedians(points,medianPosition + 1, r, k - medianPosition - 1 +  l );
	else return medianOfMedians(points,l,medianPosition - 1, k);
}

/*! This funtion simply swaps two point object values
*/
void VectorOps::swap(Point* x,Point* y){
	Point temp;

	temp = *x;
	*x=*y;
	*y=temp;
}

/*! This function separates the input set across the median point along x axis
\param points input set as Point object
\param l left index
\param r right index
\param x x coordinate of median point
\return gives the position of median point after final partitioning
*/
int VectorOps::medianPartition(std::vector<Point> &points,int l,int r,Point x){
	/*printf("medianPartition start:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	int z;
	for(z=l;z<r;z++)
		if(points[z].getX()==x.getX() && points[z].getY()==x.getY())
			break;

	swap(&points[z],&points[r]);

	int i=l;

	for(int z=l;z<r;z++){
		if(points[z].getX()<=x.getX()){
			swap(&points[z],&points[i]);
			i++;
		}
	}

	swap(&points[i],&points[r]);

/*	printf("printing vec:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
		cout<<"\t";
	}
	cout<<"\n";*/

	/*printf("medianPartition end here:\n");
	for(int z=l;z<=r;z++){
		points[z].printPoint();
	}*/

	return i;
}

/*! This function is used to sort Point objects by x-coordinate
*/
bool VectorOps::sortByX(Point a,Point b){
	return (a.getX() < b.getX());
}

/*! This functions finds the median of a set of points using medians of median method
\param points input set of points as Point object
\param l left index
\param r right index
\param k kth smallest element to find
\return returns median point as Point object
*/
Point VectorOps::medianOfMedians(std::vector<Point> &points,int l,int r,int k)
{	//dividing into buckets
	//printf("arguments: l:%d r:%d k:%d\n",l,r,k );

	int nofOfPts= (r-l+1);

	std::vector<Point> medianVec;

	for(int i=l;i<=r;i=i+5){
		int start=i;
		int end= (i+5<=r?i+5:r+1);
		sort(points.begin()+start,points.begin()+end,this->sortByX);
		medianVec.push_back(points[(start+end)/2]);

	}
/*
	cout<<"c:"<<c<<"\n";
	for(int l=0;l<medianVec.size();l++){
		medianVec[l].printPoint();
		cout<<"\n";
	}*/

	Point medOfMed = (medianVec.size()==1? medianVec[0]: medianOfMedians(medianVec,0,medianVec.size()-1,medianVec.size()/2) );

	/*printf("medOfMed:\n");
	medOfMed.printPoint();*/
	int medianPosition = medianPartition(points,l,r, medOfMed);
	//printf("medianPosition: %d\n",medianPosition );

	//cout<<"ans:\n";
	if(medianPosition - l == k) return medOfMed;
	else if(k>medianPosition - l) return medianOfMedians(points,medianPosition + 1, r, k - medianPosition - 1 +  l );
	else return medianOfMedians(points,l,medianPosition - 1, k);
}

/*! This function gets the index of a point from the set of points
*/

int VectorOps::findIndex(std::vector<Point> points,Point p)
{
	int i;
	for(i=0;i<points.size();i++)
	{
		if(std::abs(points[i].getY()-p.getY())<0.000001)
		{
			if(std::abs(points[i].getX()-p.getX())<0.000001)
			{
				return i;
			}
		}
	}
	return -1;
}