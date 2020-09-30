#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void count_sort(int arr[],int n,int k);
int main()
{
	int max,i,arr[]={9,5,6,5,7,3,1,8,7,8,89,56,45,56,65},n=15;
	max=arr[0];
	for(i=0;i<n;i++)
	{
		if(arr[i]>max)
			max=arr[i];
	}
	count_sort(arr,n,max);
	for(i=0;i<n;i++)
	{
		printf("%d\n",arr[i]);
	}
}
void count_sort(int arr[],int n,int k)
{
	int count[100],i,*out;
	out=(int *)malloc(n*sizeof(int));
	memset(count,0,sizeof(count));

	for(i=0;i<n;i++)
	{
		count[arr[i]]++;
	}
	for(i=1;i<=k;i++)
	{
		count[i]+=count[i-1];
	}
	for(i=0;i<n;i++)
	{
		out[count[arr[i]]-1]=arr[i];
		count[arr[i]]--;
	}
	for(i=0;i<n;i++)
	{
		arr[i]=out[i];
	}
}
