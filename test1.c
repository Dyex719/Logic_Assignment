#include<stdio.h>
#define size 500
int stack[size], top=-1,pLength=0;
char pofx[100];
int pop()
{
	if(top<=-1)
		return 0;
	else 
		return stack[top--];
}
int push(int element)
{
	if(top==size-1)
		return 0;
	else
	{
		stack[++top]=element;
		return 1;
	}
}
int giveBracketStart()
{
	for(int i=top;i>=0;i--)
	{
		if(stack[i]=='(')
			return i;

	}
}
int givePrecedence(char op)
{
	if(op=='(')
		return 0;
	else if(op=='~')
		return 1;
	else if(op=='*')
		return 2;
	else if(op=='+')
		return 3;
	else if(op=='>')
		return 4;
}
int greaterPrecedence(char op)
{
	if(givePrecedence(op)>givePrecedence(stack[top]))
		return 1;
	else return 0;
}
void inToPost(int l,char infx[])
{
	for(int i=0;i<l;i++)
	{
		if(infx[i]=='('||infx[i]=='~'||infx[i]=='+'||infx[i]=='*'||infx[i]=='>')
		{
			if(greaterPrecedence(infx[i]))
			{
				pofx[pLength++]=pop();
				push(infx[i]);
			}
			else 
			{
				push(infx[i]);
			}
		}
		else if(infx[i]==')')
		{
			for(int j=top;j>giveBracketStart();j--)
			{
				pofx[pLength++]=pop();
			}
			pop();			
		}
		else
		{
			pofx[pLength++]=infx[i];
		}
	}
	for(;top>=0;)
		pofx[pLength++]=pop();
}
int main()
{
	char infx[100];
	scanf("%s",infx);
	int length=sizeof(infx)/sizeof(infx[0]);
	inToPost(length,infx);
}
