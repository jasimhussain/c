#include<stdio.h>
#include<stdlib.h>
typedef struct btree
{
	struct btree *right,*left;
	int data;
}btree;
btree *root;

void insert_in_btree(btree **root1,int data);
btree * delete_from_tree(btree *root,int data);
void preorder(btree *root);
void inorder(btree *root);
void postorder(btree *root);
btree * getminvalue(btree *root);

int main()
{
	int data,choice,arr[] = {12, 56, 2, 11, 1, 90,33,988,41},i;
	for(i=0;i<9;i++)
	{
		insert_in_btree(&root,arr[i]);
	}
	while(1)
	{
		printf("Choose from following:\n \
				1. Insert node in tree.\n \
				2. Delete the node from the tree.\n \
				3. Display in Preorder.\n \
				4. Display in Inorder.\n \
				5. Displayin Postorder.\n");
		printf("Enter your choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the number you want in tree\n");
				scanf("%d",&data);
					insert_in_btree(&root,data);
				break;
			case 2:
				printf("Enter the number you want to delete\n");
				scanf("%d",&data);
				delete_from_tree(root,data);
				break;
			case 3:
				preorder(root);
				break;
			case 4:
				inorder(root);
				break;
			case 5:
				postorder(root);
				break;
			case 6:
				printf("\n Min value is %d \n",getminvalue(root)->data);
				break;
			default:
				exit(0);
		}
	}
}

void insert_in_btree(btree **root1,int data)
{
	btree *temp;
	temp=(btree *)malloc(sizeof(btree));
	temp->data=data;
	temp->right=NULL;
	temp->left=NULL;
	if(*root1 == NULL)
		*root1=temp;
	if(data<(*root1)->data)
		insert_in_btree(&(*root1)->left, data);
	if(data>(*root1)->data)
		insert_in_btree(&(*root1)->right, data);
}
btree * delete_from_tree(btree *root,int data)
{
	if(root == NULL)
		return NULL;
	if(data < root->data)
		root->left=delete_from_tree(root->left,data);
	else if(data > root->data)
		root->right=delete_from_tree(root->right,data);
	else
	{
		if(root->left==NULL)
		{
			btree *temp=root->right;
			free(root);
			return temp;
		}
		else if(root->right==NULL)
		{
			btree *temp=root->left;
			free(root);
			return temp;
		}
		else
		{
			btree *temp=getminvalue(root);
			root->data=temp->data;
			root->right=delete_from_tree(root->right,temp->data);
		}
	}
	return root;
}
btree * getminvalue(btree *root)
{
	btree *current=root;
	while(current!=NULL && current->left!=NULL)
		current=current->left;
	return current;
}
void preorder(btree *root)
{
	if(root != NULL )
	{
		printf("%d\n",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(btree *root)
{
	if(root != NULL )
	{
		inorder(root->left);
		printf("%d\n",root->data);
		inorder(root->right);
	}
}
void postorder(btree *root)
{
	if(root != NULL )
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d\n",root->data);
	}
}
