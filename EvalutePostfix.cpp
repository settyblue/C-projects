#include<iostream>
#include<string>
#include<stack>
#include<math.h>

using namespace std;

//Function to evaluate postfix.
float EvaluatePostfix(string postfixExpression);

// Function to verify whether a character is operator symbol or not. 
bool IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 
bool IsOperand(char C);

//Funciton to evaluate expression.
float Evaluate(float a,float b, char C);

//Convert char to Operand.
float GetOperand(char C);

int main(){
	string expression; 
	cout<<"Enter Postfix Expression \n";
	getline(cin,expression);
	cout<<"Output = "<<EvaluatePostfix(expression)<<"\n";
}

float EvaluatePostfix(string expression){
	stack<float> N;
	float value = 0.0;
	float a,b = 0.0;
	for (int i =0;i<expression.length();i++){
		
		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		if(expression[i] == ' ' || expression[i] == ',') continue; 

		else if(IsOperator(expression[i]))
		{	cout<<expression[i]<<endl;
			a = N.top();N.pop();
			b = N.top();N.pop();
			N.push(Evaluate(a,b,expression[i]));
			cout<<a<<'\t'<<b<<'\t'<<N.top()<<endl;
		}
		
		else if(IsOperand(expression[i]))
		{	a = GetOperand(expression[i]);
			N.push((float)a);
		}
	}
	value = N.top();N.pop();
	return value;
}

bool IsOperand(char C) 
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not. 
bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
		return true;

	return false;
}

float Evaluate (float a,float b, char C){
	float value;
	switch(C)
	{
	case '+':
		value = a+b;break;
	case '-':
		value = a-b;break;
	case '*':
		value = a*b;break;
	case '/':
		value = a/b;break;
	case '^':
		value = pow(a,b);break;
	}
	return value;
}

float GetOperand(char C){
	return (float)(C-'0');
}
