#include<stdio.h>
#include<iostream>
using namespace std;
#include<ctype.h>
#include<math.h>
#include<vector>
#include<string.h>
int print(vector<int>v,int n)
{
    if(n<=0)
    {
    	if(v.size()!=1)	{
    		for(int i=0;i<v.size();i++){
    			cout<<v[i]<<" ";
    		}
    	cout<<endl; 
    	} 
    }else{
        for(int j=1;j<=n;j++){
        	v.push_back(j);
        	print(v,n-j);
        	v.pop_back();
        }
	}
}

int main(){
	int n;
	cin>>n;
	vector <int > m;
	print(m,n);
	return 0;
}
