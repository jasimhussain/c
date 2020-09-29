#include<stdio.h>
#include<stdlib.h>
struct node
{
int data;
struct node *next;
};
struct node *top=NULL;


void enqueue(int data)
{
struct node *new_node=(struct node *)malloc(sizeof(struct node));
struct node *temp=top;
if(top==NULL)
{
new_node->next=NULL;
new_node->data=data;
top=new_node;
}
else
{
while(temp->next!=NULL)
	temp=temp->next;
new_node->next=NULL;
new_node->data=data;
temp->next=new_node;
}
}



void dequeue()
{
if(top==NULL)
{
printf("queue is empty\n");
return;
}
printf("\n%d\n",top->data);
struct node *temp=top;
top=top->next;
free(temp);
}

void display()
{
struct node *temp;
temp=top;
if(top==NULL)
{
printf("Queue is empty\n");
return;
}
while(temp!=NULL)
{
printf("\n%d\n",temp->data);
temp=temp->next;
}
}

int main()
{
int data,choice;
while(1)
{
printf("Enter your choice:\n\t1. Enqueue\n\t2. Dequeue\n\t3. Display elements\n\t4. exit \n");
scanf("%d",&choice);
switch(choice)
{
	case 1:
		printf("Enter data\n");
		scanf("%d",&data);
		enqueue(data);
		break;
	case 2:
		dequeue();
		break;
	case 3:
		display();
		break;
	default:
		exit(1);

}
}
}
