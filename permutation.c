#include<stdio.h>
#define MAX_LIMIT 4
static int return_value=0;
void print_array(int arr[],int i)
{
	int k;
	for(k=0;k<i;k++)
		printf("%d",arr[k]);
	printf("\n");
        return_value++;
}
int get_combination(int n, int i)
{
	static int arr[MAX_LIMIT];
	int k;
	if(n==0)
	{
		print_array(arr,i);
	}
	else if(n>0)
	{
		int k;
		for(k=1;k<=MAX_LIMIT;k++)
		{
			if(k==2)
				continue;
			arr[i]=k;
			get_combination((n-k),i+1);
		}
	}
	//return return_value;
	return 0;
}
int main()
{
	int n;
	scanf("%d",&n);
	get_combination(n,0);
	printf("\n\tThe number combinations using 1,2,3 are %d\n",return_value);
}
