#include<iostream>
using namespace std;

bool IsPalindrome(string s);

int main(){
	string s;
	cin>>s;
	cout<<s<<" is a "<<(IsPalindrome(s)?"Palidrome.":"not a Palindrome.");
}

bool IsPalindrome(string s){
	int i=0,j=s.length()-1;
	while(i<j && s[i]==s[j]){
		i++;j--;	
	}
	if(i<j){
		return false;
	}else return true;
}
