#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void radix_sort(int arr[],int n,int k);
void caller_radix(int arr[],int n,int max);
int main()
{
	int max,i,arr[]={ 82, 901, 100, 1, 150, 7, 55, 23 },n=8;
	max=arr[0];
	for(i=0;i<n;i++)
	{
		if(arr[i]>max)
			max=arr[i];
	}
	caller_radix(arr,n,max);
	for(i=0;i<n;i++)
	{
		printf("%d\n",arr[i]);
	}
}
void caller_radix(int arr[],int n,int max)
{
	int exp;
	for(exp=1;max/exp>0;exp*=10)
	{
		radix_sort(arr,n,exp);
	}
}
void radix_sort(int arr[],int n,int exp)
{
	int count[10],i,*out;
	out=(int *)malloc(n*sizeof(int));
	memset(count,0,sizeof(count));

	for(i=0;i<n;i++)
	{
		count[(arr[i]/exp)%10]++;
	}
	for(i=1;i<10;i++)
	{
		count[i]+=count[i-1];
	}
	for(i=n-1;i>=0;i--)
	{
		out[count[(arr[i]/exp)%10]-1]=arr[i];
		count[(arr[i]/exp)%10]--;
	}
	for(i=0;i<n;i++)
	{
		arr[i]=out[i];
	}
}
