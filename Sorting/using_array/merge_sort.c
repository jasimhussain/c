#include<stdlib.h>
#include<stdio.h>
int merge(int arr[],int l,int h,int m)
{
	int i=0,j=0,k=l,n1,n2;
	n1=m-l+1;
	n2=h-m;
	int arr1[n1],arr2[n2];
	for(i=0;i<n1;i++)
		arr1[i]=arr[l+i];
	for(i=0;i<n2;i++)
		arr2[i]=arr[m+1+i];
	i=0;
	while((i<n1)&&(j<n2))
	{
		if(arr1[i]<arr2[j])
		{
			arr[k]=arr1[i];
			i++;k++;
		}
		else
		{
			arr[k]=arr2[j];
			j++;k++;
		}
	}
	while(i<n1)
		{	arr[k]=arr1[i];
			i++;k++;

		}
	while(j<n2)
		{	arr[k]=arr2[j];
			j++;k++;

		}
	
}
int mergesort(int arr[],int l,int h)
{
	if(l<h)
	{
		int m=(l+h)/2;
		mergesort(arr,l,m);
		mergesort(arr,m+1,h);
		merge(arr,l,h,m);
	}
}
int main()
{
int i,n;
printf("Enter size of array:\n");
scanf("%d",&n);
int *ptr=(int *)malloc(n*sizeof(int));
printf("Enter the elements of array\n");
for(i=0;i<n;i++)
	scanf("%d",&ptr[i]);
mergesort(ptr,0,n-1);
for(i=0;i<n;i++)
	printf(" %d ",ptr[i]);
}
