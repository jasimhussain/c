#include<stdio.h>
void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
int main()
{
	int i,j,arr[]={23,-4,-6,0,2,34};
	int n=sizeof(arr)/sizeof(arr[0]);
	for(i=0;i<n;i++)
	{
		int min=i;
		for(j=i+1;j<n;j++)
			if(arr[j]<arr[min])
				min=j;
		swap(&arr[i],&arr[min]);
	}
	for(i=0;i<n;i++)
		printf("%d\n",arr[i]);


}
