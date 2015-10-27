//Given an array, find an element before which all elements are smaller than it, 
//and after which all are greater than it. 
//Return index of the element if there is such an element, otherwise return -1.
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<ctime>
using namespace std;

void findLeftMax(int* a,int* LeftMax, int length);
void findRightMin(int* a,int* RightMin,int length);
void printArray(int *a,int length);
void printValidIndicies(int* a,int* LeftMax,int* RightMin, int length);
int main(){
	int length = 10,k=5;
	int a[length];
	int LeftMax[length], RightMin[length];
	srand(time(NULL));
	for(int i=0;i<k;i++){
		a[i] = rand()%100;
	}
	a[k] = 150;
	srand(time(NULL));
	for(int i=k+1;i<length;i++){
		a[i] = 200+rand()%100;
	}
	
	findLeftMax(a,LeftMax,length);
	findRightMin(a,RightMin,length);
	printArray(a,length);
	printArray(LeftMax,length);
	printArray(RightMin,length);
	printValidIndicies(a,LeftMax,RightMin,length);
}

void findLeftMax(int* a,int* LeftMax,int length){
	LeftMax[0] = -1;
	LeftMax[1] = a[0];
	for (int i=2;i<length;i++){
		if(a[i-1]>LeftMax[i-1]){
			LeftMax[i] = a[i-1];
		}else{
			LeftMax[i] = LeftMax[i-1];
		}
	}
}

void findRightMin(int* a,int* RightMin,int length){
	RightMin[length-1] = -1;
	RightMin[length-2] = a[length-1];
	for(int i=length-3;i>-1;i--){
		if(a[i+1]<RightMin[i+1]){
			RightMin[i] = a[i+1];
		}else{
			RightMin[i] = RightMin[i+1];
		}
	}
}
void printValidIndicies(int* a,int* LeftMax,int* RightMin, int length){
	cout<<"valid indices are : ";
	int count=0;
	for(int i=0;i<length;i++){
		if(LeftMax[i]<a[i] && a[i]<RightMin[i]){
			cout<<i<<"\t";
			count++;
		}
	}
	if(count == 0){
		cout<<endl<<"no such index found";
	}
}

void printArray(int* a,int length){
	for(int i=0;i<length;i++){
		cout<<a[i]<<"\t";
	}
	cout<<endl;
}
