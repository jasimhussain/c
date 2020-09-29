#define MAX 9
#include<stdio.h>
int top=-1;
int stack[10];
void push(int data)
{
if(top==MAX)
{
printf("Stack is full");
}
else
{
++top;
stack[top]=data;
}
}
void pop()
{
int i;
if(top==-1)
{
printf("Stack is empty");
}
else
{
printf("Popped element is  %d.",stack[top]);
--top;
}
}
void display()
{
int i;
for(i=0;i<=top;i++)
{
printf("\nElements in stack are\n");
printf("%d\n",stack[i]);
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
