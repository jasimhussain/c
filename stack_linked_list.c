#include<stdio.h>
#include<stdlib.h>
struct linked_list
{
	int data;
	struct linked_list *next;
};
struct linked_list *top=NULL;
void push(int data)
{
	if(top==NULL)
	{
		top=(struct linked_list *)malloc(sizeof(struct linked_list));
		top->data=data;
		top->next=NULL;
	}
	else
	{
		struct linked_list *temp=(struct linked_list *)malloc(sizeof(struct linked_list));
		temp->data=data;
		temp->next=top;
		top=temp;
	}
}

void pop()
{
	if(top==NULL)
	{
		printf("Stack is empty");
	}
	else
	{
		struct linked_list *temp=top;
		printf("Popped element is %d\n",top->data);
		top=top->next;
		free(temp);
	}
}

void display()
{
	struct linked_list *temp=top;
	if(top==NULL)
	{
		printf("Stack is empty");
	}
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp=temp->next;
	}
}
int main()
{
	int choice;
	while(1)
	{
		int data;
		printf("Choose from following optons:\n\t1.PUSH\n\t2.POP\n\t3.DISPLAY\n\t4.ELSE EXIT\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case(1):
				{
					printf("Enter data for stack");
					scanf("%d",&data);
					push(data);
					break;
				}
			case(2):
				{
					pop();
					break;
				}
			case(3):
				{
					display();
					break;
				}
			default:
				exit(0);
		}
	}
}

