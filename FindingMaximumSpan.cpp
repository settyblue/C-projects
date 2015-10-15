#include<iostream>
#include<stack>
using namespace std;

int* FindingSpan(int A[],int* S, int n);

int main(){
	int A[10] = {1,3,5,6,3,4,2,7,1,0};
	int S[10] = {0,0,0,0,0,0,0,0,0,0}; 
	int* s = FindingSpan(A,s,10);
	for (int i=0;i<10;i++){
		cout<<A[i]<<" : "<<s[i]<<",";
	}
}

int* FindingSpan(int A[],int* B, int n){
	int i,p,S[10];
	stack <int> rates;
	for (int i=0;i<n;i++){
		while(!rates.empty()){
			if(A[i]<A[rates.top()]){
				rates.pop();
			}
		}
		if(rates.empty()) p = -1;
		else p = rates.top();
		cout<<"debug"<<i<<" "<<p<<endl;
		S[i] = i-p;
		rates.push(i);
	}
	return S;
}
