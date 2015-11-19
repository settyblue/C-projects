#include<stdio.h>
#include<iostream>
using namespace std;
#include<ctype.h>
#include<math.h>
#include<vector>
#include<string.h>
int distance(string s[],string r,string t)
{
       int n=sizeof(s)/sizeof(s[0]);
       int i,min=9999,count=0;
       for(i=0;i<n;i++)
       {
       cout<<i;
       if(s[i]==r)
       {
       for(int j=i+1;j<n;j++)
       {
       if(s[j]==t)
       {
       count=j-i;
       if(count<min)
       min=count;
       }
       }
       }
       cout<<i;
       if(s[i]==t)
       {
       for(int j=i+1;j<n;j++)
       {
       if(s[j]==r)
       {
       count=j-i;
       if(count<min)
       min=count;
       }
       }
       }
       }
       return min;
}
int main()
{
   string s[]={"good", "fox","person","the", "quick", "brown", "fox", "quick"};
   string t="fox";
   string r="quick";
   int q=distance(s,t,r);
   cout<<q;
   return 0;
}

