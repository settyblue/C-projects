//given array of integers find the window of k integers having maximum sum.
#include<iostream>
using namespace std;

void printArray(int* a,int length);
int findMaxSumIndex(int* a, int k,int length);
int main(){
	int a[] = {3,4,1,6,7,3,9,3,10,22,3,4,25};
	int k = 3;
	int length = sizeof(a)/sizeof(a[0]);
	printArray(a,length);
	cout<<"max sum is : "<<findMaxSumIndex(a,k,length);
}

void printArray(int* a,int length){
	for(int i=0;i<length;i++){
		cout<<a[i]<<"\t";
	}
	cout<<endl;
}
int findMaxSumIndex(int* a, int k,int length){
	int maxSum;
	int temp = 0;
	for(int i=0;i<k;i++){
		temp+= a[i];
	}
	maxSum = temp;
	for(int i=0;i<length-k;i++){
		temp = temp + a[i+k] - a[i];
		maxSum = max(maxSum,temp);
	}
	return maxSum;
}
