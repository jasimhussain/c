#include<stdio.h>
void swap(int *a, int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void insertion_sort(int arr[],int n);
int main()
{
	int i,n=6,arr[]={98,-6,0,5,100,67};
	/*    
	int n,*array;
	printf("Enetr the number of integers required in an array\n");
	scanf("%d",&n);
	array=(int *)malloc(n*sizeof(int));
	printf("Enter the required integers\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	*/
	insertion_sort(arr,n);
	for(i=0;i<n;i++)
	{
		printf("%d\n",arr[i]);
	}
}
void insertion_sort(int arr[],int n)
{
	int i,j,key;
	for(i=1;i<n;i++)
	{
		key=arr[i];
		j=i-1;
		while(j>=0 && arr[j]>key)
		{
			arr[j+1]=arr[j];
			j--;
		}
		if(i!=(j+1))
		{
			arr[j+1]=key;
		}
	}
}
