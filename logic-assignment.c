/*
The following programs implements the construction of a parse tree for a propositional logic formula.
The input should be a well formed propositional logic formula in the infix form.
The output consists of the postfix and inorder traversal of the given input.

Contributors:
Aditya Addepalli   2015B1A70719H
Phani Shankar Ede  2015B3A70420H
Ayush Pandey       2015B3A70517H
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define sSize 10000
#define size 100000
typedef struct nodeStruct node;
// Creating custom datatype node to represent each node of our Binary Tree
struct nodeStruct
{
	char val;
	node* left;
	node* right;
};
// Initializing stack for Postfix expression
char stack[sSize];int topPostStack=-1;
// Initializing stack for Parse Tree
node* B[sSize];int topTreeStack=-1;
// Initializing PostFix String
char pofx[size];int pLength=0;

// Functions to manipulate elements in the stacks
char pop();
void push(char element);
node* popNode();
void pushNode(node* c);

// Peripheral Functions for performing inbetween tasks
int giveBracketStart();
int givePrecedence(char op);
int greaterPrecedence(char op);

// Important Functions that perform desired tasks
void inToPost(int l,char infx[]);// Task 1
node* makePT();// Task 2
void inorder(node* ptr);// Task 3
int main()
{
	char infx[size];int length=0;
	scanf("%s",infx);
	inToPost(strlen(infx),infx);
	pofx[pLength]='\0';
	printf("The postfix is: %s\n",pofx);
	node* ptr = makePT();// Task 2
	printf("The inorder traversal gives the infix: ");
	inorder(ptr);// Task 3
	printf("\n");
	return 0;
}

// This Function returns the topmost operator on the staack
char pop()
{
	if(topPostStack<=-1)
		return 0;
	else
		return stack[topPostStack--];
}

// This Function pushes the passed operator onto the stack
void push(char op)
{
	stack[++topPostStack]=op;
}

// This Function extracts the topmost tree node from the stack and returns it.
node* popNode()
{
	if(topTreeStack<=-1)
		return 0;
	else
    	return(B[topTreeStack--]);
}

// This Function pushes the passed tree node on top of the stack
void pushNode(node* c)
{
    B[++topTreeStack]=c;
}

// Gives the position of the closest ( from the top of the postfix stack
int giveBracketStart()
{
	for(int i=topPostStack;i>=0;i--)
	{
		if(stack[i]=='(')
			return i;

	}
}

// Returns the precedence of the operator according to logic rules
int givePrecedence(char op)
{
	if(op=='(')
		return 5;
	else if(op=='~')
		return 1;
	else if(op=='*')
		return 2;
	else if(op=='+')
		return 3;
	else if(op=='>')
		return 4;
}

// Returns the comparison between the passed operator and top operator on the stack
int greaterPrecedence(char op)
{
	if(givePrecedence(op)>=givePrecedence(stack[topPostStack]))
		return 1;
	else
		return 0;
}

// Returns the Postfix Expression for the passed infix
void inToPost(int l,char infx[])
{
	// Iterating through the length of the Infix String after accounting for '\0'
	for(int i=0;i<l;i++)
	{
		// Checking if extracted character is an operator
		if(infx[i]=='~'||infx[i]=='+'||infx[i]=='*'||infx[i]=='>')
		{
			// Directly pushing if stack is empty
			if(topPostStack==-1)
			{
				push(infx[i]);
			}
			// Checking for precedence of operators if stack is non-empty
			else if(topPostStack>-1)
			{
				while((topPostStack>-1)&&(greaterPrecedence(infx[i])))
				{
					pofx[pLength++]=pop();
				}
					push(infx[i]);
			}
		}
		// Emptying Stack until the nearest '(' into the postfix expression
		else if(infx[i]==')')
		{
			for(int j=topPostStack;j>giveBracketStart();j--)
			{
				pofx[pLength++]=pop();
			}
			pop();
		}

		else if(infx[i]=='(')
		{
			push(infx[i]);
		}
		else
		{
			pofx[pLength++]=infx[i];
		}
	}
	// Emptying all the remaining elements of the stack into the postfix
	while(topPostStack>=0)
		{
			pofx[pLength++]=pop();
		}
}

//  Converts the Postfix String into a Parse Tree and returns pointer to the root of the Parse Tree
node* makePT()
{
	int n = strlen(pofx);
	int i;
	// Iterating through the elements of the postfix
	for(i=0;i<n-1;i++){
		//  Checking if character is a propositional atom.
		//  In this case, we create a tree node with no children and push it on to the stack directly
		if(isalnum(pofx[i]))
		{
			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = pofx[i];
			ptr->left = NULL;
			ptr->right = NULL;
			pushNode(ptr);
		}
		// Checking if character is Unary negation operator.
		// In this case, we create a tree node with topmost element of stack as right child node and push it on to the stack
		else if(pofx[i]=='~')
		{
			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = pofx[i];
			ptr->left = NULL;
			ptr->right = popNode();
			pushNode(ptr);
		}
		// Checking if character is Binary propositional operator.
		// In this case, we create a tree node with the 2 top elements of stack as children and push it on to the stack
		else
		{
			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = pofx[i];
			ptr->right = popNode();
			ptr->left = popNode();
			pushNode(ptr);
		}
	}
	// Once the construction of the subtrees are done, we combine them into a single rooted parse tree with each of the subtrees as it's children.
	// In case root is ~, only one subtree exists.
	node *ptr = (node *) malloc(sizeof(node));
			ptr->val = pofx[i];
			if (pofx[i] == '~')
			{
				ptr->left = NULL;
				ptr->right = popNode();
			}
			else
			{
				ptr->right = popNode();
				ptr->left = popNode();
			}
	return ptr;
}

// Takes the root of the Binary Parse Tree as input and generates the prefix expression by doing inorder traversal of the parse tree
void inorder(node* ptr)
{
	if(ptr)
	{
		if(ptr->left != NULL && ptr->right != NULL )
			printf("(" );
		inorder(ptr->left);
		printf("%c",ptr->val );
		inorder(ptr->right);
		if(ptr->left != NULL && ptr->right != NULL )
			printf(")" );
	}
}
