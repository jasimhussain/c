#include<stdio.h>
void heapify(int arr[], int n, int h)
{
	int largest,l,r,i;
	l=2*h+1;
	r=2*h+2;
	largest=h;
	if(arr[l]>arr[largest] && l<n)
		largest=l;
	if(arr[r]>arr[largest] && r<n)
		largest=r;
	if(largest != h)
	{
		int temp=arr[largest];
		arr[largest]=arr[h];
		arr[h]=temp;
		heapify(arr,n,largest);
	}

}

void create_heap(int arr[],int n)
{
	int i,medium=n/2-1;
	for(i=medium;i>=0;i--)
	{
		heapify(arr,n,i);
	}

}

void heapsort(int arr[],int n)
{
	int temp,i,medium=n/2-1;
        for(i=medium;i>=0;i--)
        {
                heapify(arr,n,i);
        }
	for(i=n-1;i>0;i--)
	{
		temp=arr[i];
		arr[i]=arr[0];
		arr[0]=temp;
		heapify(arr,i,0);
	}
}

int main()
{
	int i,arr[6]={6,5,76,4,21,1};
	create_heap(arr,6);
	heapsort(arr,6);
	for(i=0;i<6;i++)
		printf(" %d ",arr[i]);
}
