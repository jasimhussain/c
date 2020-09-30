#include<stdio.h>
#include<stdlib.h>
struct link
{
	struct link *next;
	int data;
};
struct link *head=NULL;
void insert_at_begin(struct link **head, int data);
void bubble_sort_ll(struct link *head);
int main()
{
	int arr[] = {12, 56, 2, 11, 1, 90},i;
	struct link *temp;
	for(i=0;i<6;i++)
	{
		insert_at_begin(&head,arr[i]);
	}
	printf("Data before sorting\n");
	temp=head;
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp=temp->next;
	}
	bubble_sort_ll(head);
	temp=head;
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp=temp->next;
	}
}
void insert_at_begin(struct link **head, int data)
{
	struct link *temp;
	temp=(struct link *)malloc(sizeof(struct link));
	temp->next=*head;
	temp->data=data;
	*head=temp;
}
void bubble_sort_ll(struct link *head)
{
	printf("doing sorting\n");
	struct link *last=NULL,*tempi=head;
	int scanned=0,temp;
	if(head == NULL)
		return;
	do
	{
		tempi=head;
		scanned=0;
		while(tempi->next != last)
		{
			if(tempi->data > tempi->next->data)
			{
				temp=tempi->data;
				tempi->data=tempi->next->data;
				tempi->next->data=temp;
				scanned=1;
			}
			tempi=tempi->next;
		}
		last=tempi;
	}while(scanned);
}
