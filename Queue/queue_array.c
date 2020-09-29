#include<stdio.h>
#include<stdlib.h>
#define QUEUE_SIZE 5
int queue[QUEUE_SIZE];
int head=-1,tail=-1;
void push(int n);
int pop();
void display();
int main()
{
	int choice,num;
	while(1)
	{
		printf("Please enter the one number for the follwing choices\n1. Push\n2. Pop\n3. Display\n");
		printf("Enter you choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the number you want to push\n");
				scanf("%d",&num);
				push(num);
				break;
			case 2:
				pop();
				break;
			case 3:
				display();
				break;
			default:
				exit(0);
		}

	}
}
void push(int n)
{
	if(((tail+1) == head) || ((head == 0) && (tail == QUEUE_SIZE-1)))
	{
		printf("queue is full\n");
		return;
	}
	if(head == -1)
		head=0;
	tail=(tail +1)%QUEUE_SIZE;
	queue[tail]=n;
}
int pop()
{
	int temp;
	if(head == -1)
	{
		printf("Queue is empty nothing is there to pop\n");
		return -1;
	}
	else
	{
		temp=queue[head];
		printf("Popped element =%d\n",queue[head]);
		if(head == tail)
		{
			head =tail =-1;
		}
		else
		{
			head++;
			head%=QUEUE_SIZE;
		}
	}
}
void display()
{
	int i;
	if(head==-1)
	{
		printf("Queue is empty\n");
		return;
	}
	if( tail >= head)
	{
		for(i=head;i<=tail;i++)
		{
			printf("%d ",queue[i]);
		}
	}
	else
	{
		for(i=head;i<QUEUE_SIZE;i++)
		{
			printf("%d ",queue[i]);
		}
		for(i=0;i<=tail;i++)
		{
			printf("%d ",queue[i]);
		}
	}
	printf("\n");
}
