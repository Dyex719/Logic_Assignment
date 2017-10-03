#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int topB=-1;
typedef struct nodeStruct node;

struct nodeStruct               // structure of the nodes in the Binary Tree
{
	char val;
	node* left;
	node* right;
};
node* B[50];
void pushStr(node* c)
{
    B[++topB]=c;
}
node* popStr()
{
    return(B[topB--]);
}


node* makeBT(char prefix[50]);                 //  Task 2
void inorder(node* ptr);

node* makeBT(char postfix[50]){            // From a given postfix expression, making a binary parsed tree

	int n = strlen(postfix);
	int i = 0;

	for(i=0;i<n-1;i++){

		if(isalnum(postfix[i])){
			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = postfix[i];
			ptr->left = NULL;
			ptr->right = NULL;

			pushStr(ptr);

		}else if(postfix[i]=='~'){

			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = postfix[i];
			ptr->left = NULL;
			ptr->right = popStr();

			pushStr(ptr);

		}else{
			node *ptr = (node *) malloc(sizeof(node));
			ptr->val = postfix[i];
			ptr->right = popStr();
			ptr->left = popStr();

			pushStr(ptr);
		}

	}
	node *ptr = (node *) malloc(sizeof(node));
			ptr->val = postfix[i];
			if (postfix[i] == '~')
			{
				ptr->left = NULL;
				ptr->right = popStr();
			}else{
			ptr->right = popStr();
			ptr->left = popStr();
			}

	return ptr;
}

void inorder(node* ptr){            // From a binary parsed tree, getting back to an infix notation through inorder traversal
	if(ptr){
		inorder(ptr->left);
		printf("%c",ptr->val );
		inorder(ptr->right);
	}
}

int main()
{
char* s = "pq+r*ts*>";
node* ptr = makeBT(s);
inorder(ptr);

return 0;
}
