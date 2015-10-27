//LCS Problem Statement: Given two sequences, find the length of longest subsequence 
//present in both of them. A subsequence is a sequence that appears in the same relative order, 
//but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are 
//subsequences of “abcdefg”. So a string of length n has 2^n different possible subsequences.
//
#include<iostream>
#include<stdlib.h>
using namespace std;

int lcs(char* X, char* Y, int m, int n);

int main(){
	char X[] = "AGGTAB";
  	char Y[] = "AXGTXAY";
 
  	int m = sizeof(X);
  	int n = sizeof(Y);
 
  	printf("Length of LCS is %d\n", lcs( X, Y, m, n )-1 );

  	return 0;
}

int lcs( char *X, char *Y, int m, int n )
{
   if (m == 0 || n == 0)
     return 0;
   if (X[m-1] == Y[n-1])
     return 1 + lcs(X, Y, m-1, n-1);
   else
     return max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
}
