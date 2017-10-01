#include<stdio.h>
#define size 500
struct pt
{
	char value;
	struct pt *left, *right;
};
struct pt stackTree[size];
int topST=-1;
void pushST()
{

}
struct pt* popST()
{

}
void inorder(struct pt *t)
{
	if(t)
	{
		inorder(t->left);
		printf("%c ",t->value);
		inorder(t->right);
	}
}
struct pt* newNode(char v)
{
	struct pt *temp;
	temp->left=NULL;
	temp->right=NULL;
	temp->value=v;
	return temp;
}
struct pt* constructTree()
{
	struct pt *t,*t1,*t2;
	for(int i=0;i<pLength;i++)
	{
		if(!(pofx[i]=='('||pofx[i]=='~'||pofx[i]=='+'||pofx[i]=='*'||pofx[i]=='>'))
		{
			t=newNode(pofx[i]);
			pushST(t);
		}
		else
		{
			t=newNode(pofx[i]);
			t1=popST();
			t2=popST();
			t->right=t1;
			t->left=t2;
			pushST(t);

		}
	}
	return stackTree[topST]; 
}

int main()
{
	struct pt* r=constructTree();
	inorder(r);
}
