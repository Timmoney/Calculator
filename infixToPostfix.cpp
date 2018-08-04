/*
convert infix to postfix
can check parameter, and precedence

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
//#include <string>
#define MAX 50
using namespace std;

int perform(char c, int op1, int op2);  //perfrom the basic operator
int EvaluatePostfix(char *c, int len);  //evaluate the postfix
bool precedence(char a, char b);		//compare the the precedence betwee a and b
int infixToPostfix(char *c, int len);	//convert infix to postfix
char postf[MAX]; //global

int main(){
	char c[50];
	int x;
	printf("Enter a string: ");
	gets(c);

	infixToPostfix(c, strlen(c));
	x = EvaluatePostfix(postf, strlen(postf));

	printf("The answer is %d\n", x);
}

int perform(char c, int op1, int op2){
	if(c == '+')
		return op1+op2;
	if(c == '-')
		return op1-op2;
	if(c == '*')
		return op1*op2;
	if(c == '/')	
		return op1/op2;
}

int EvaluatePostfix(char *c, int len){
	stack<int> s;
	int op1, op2, answer, result;
	int temp; //convert char to int

	for(int i =0;i<len;i++){
		if(c[i] != '+' && c[i] != '-' && c[i] != '*' && c[i] != '/'){
			temp = c[i] - '0'; //convert character to int 0-9 range
			if(temp<10){
				s.push(temp);
			}
				
			else{
				printf("Error, invalid string....\n");	
				return false;
			}		
		}
		else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/'){
			if(s.empty()){
				printf("Error, invalid string....\n");
				return false;
			}
				
			op2 = s.top();
			s.pop();
			if(s.empty()){
				printf("Error, invalid string....\n");
				return false;
			}	
			op1 = s.top();
			s.pop();
			result = perform(c[i], op1, op2);
			s.push(result);
		}
	}
	answer = s.top();
	return answer;
}

bool precedence(char a, char b){
	if(a == '*' || a == '/'){
		if(b == '-' || b == '+')
			return false;
	}
	else if (a == NULL){
		return false; // case when s.top() nothing
	}
	else{
		return true;
	}			
}

int infixToPostfix(char *c, int len){
	stack<char> s;
	int temp; //convert char to int
	char top;
	char* p = postf; //to point at the array

	//*p = postf;

	for(int i=0; i<len; i++){
		if(c[i] != '+' && c[i] != '-' && c[i] != '*' && c[i] != '/'){
			temp = c[i] - '0';
			if(temp<10){
				*p = c[i]; //push to the list
				p++;
			}else{
				printf("Errior...\n");
				return false; // need it to stop
			}
		}
		else if(c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/'){
			if(s.empty() || precedence(s.top(), c[i])){
				s.push(c[i]); //push to the stack
			}				
			else{
				while(!s.empty()){
					top = s.top();
					*p = top;
					p++;
					//cout << s.top() << endl;
					s.pop();
					
				}
				s.push(c[i]);
			}
		}
	}

	while(!s.empty()){
		top = s.top();
		*p = top;
		p++;
		s.pop();
	}

}
