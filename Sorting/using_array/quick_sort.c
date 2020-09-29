#include<stdio.h>
#include<stdlib.h>
void quicksort(int arr[],int low,int high)
{
if(low<high)
{
int pi=partition(arr,low,high);
quicksort(arr,low,pi-1);
quicksort(arr,pi+1,high);
}
}

int partition(int arr[],int low,int high)
{
int pivot,i,j,temp;
pivot=arr[high];
i=(low-1);
for(j=low;j<=(high-1);j++)
{
if(arr[j]<=pivot)
{
i++;
temp=arr[i];
arr[i]=arr[j];
arr[j]=temp;
}
}
temp=arr[i+1];
arr[i+1]=arr[high];
arr[high]=temp;
return (i+1);
}

int main()
{
int n,i,j;
scanf("%d",&n);
int *ptr=(int *)malloc(n*4);
for(i=0;i<n;i++)
{
scanf("%d",&j);
ptr[i]=j;
}
quicksort(ptr,0,n-1);
for(i=0;i<n;i++)
printf("%d\n",ptr[i]);
}
