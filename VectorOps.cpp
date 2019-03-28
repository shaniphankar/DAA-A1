#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "VectorOps.h"
void VectorOps::swap(Point* x,Point* y){
	Point temp;

	temp = *x;
	*x=*y;
	*y=temp;
}

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

bool VectorOps::sortByX(Point a,Point b){
	return (a.getX() < b.getX());
}

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