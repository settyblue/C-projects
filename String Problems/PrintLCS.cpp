//LCS Problem Statement: Given two sequences, find the length of longest subsequence 
//present in both of them. A subsequence is a sequence that appears in the same relative order, 
//but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are 
//subsequences of “abcdefg”. So a string of length n has 2^n different possible subsequences.
//Print the longest subsequence.
#include<iostream>
using namespace std;

void printLCS(char* X, char* Y, int m, int n);

int main(){
	char X[] = "AGGATB";
	char Y[] = "BAGTB";
	int m = sizeof(X);
	int n = sizeof(Y);
	printLCS(X,Y,m,n);
	return 0;
}

void printLCS(char* X, char* Y, int m, int n){
	int L[m+1][n+1];
	
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			if(i==0 || j==0)
				L[i][j] = 0;
			else if(X[i-1] == Y[j-1])
				L[i][j] = L[i-1][j-1] + 1;
			else
				L[i][j] = max(L[i-1][j],L[i][j-1]);
		}
	}
	
	//Length of lcs = L[m][n];
	int index = L[m][n];
	char lcs[index+1];
    lcs[index] = '\0'; // Set the terminating character
	
	// Start from the right-most-bottom-most corner and
   	// one by one store characters in lcs[]
  	int i = m, j = n;
   	while (i > 0 && j > 0){
   		// If current character in X[] and Y[] are same, then
      	// current character is part of LCS
      	if(X[i-1] == Y[j-1]){
      		lcs[index-1] = X[i-1];
      		i--; j--; index--;
		}else if (L[i-1][j] > L[i][j-1]){
			i--;
		}else{
			j--;
		}
	}
    // Print the lcs
    cout << "LCS of " << X << " and " << Y << " is " << lcs;
}

void printMatrix(int **L,int m, int n){
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			cout<<L[i][j]<<"\t";
		}
		cout<<endl;
	}
}
