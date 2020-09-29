#include<stdio.h>
void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
void bubble_sort(int [],int);
int main()
{
	int i,arr[]={5,4,3,2,1};
	int n=sizeof(arr)/sizeof(arr[0]);
	bubble_sort(arr,n);
	for(i=0;i<6;i++)
	{
		printf("%d\n",arr[i]);
	}
}
void bubble_sort(int arr[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
			if(arr[j]>arr[j+1])
				swap(&arr[j],&arr[j+1]);
}
	
