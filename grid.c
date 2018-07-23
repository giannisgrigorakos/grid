#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int arr_idx[], int low, int high)
{
    int pivot = arr[high];    
    int i = (low - 1);  
 
    for (int j = low; j <= high-1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);    
            swap(&arr_idx[i], &arr_idx[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    swap(&arr_idx[i+1], &arr_idx[high]);
    return (i + 1);
}


void quickSort(int arr[],int arr_idx[] ,int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, arr_idx, low, high);
        quickSort(arr, arr_idx, low, pi - 1);
        quickSort(arr, arr_idx, pi + 1, high);
    }
}

int main(int argc, char *argv[])
{
	int N,i,j;
	i=0;
	j=0;
	scanf("%d", &N);
	int *x_idx, *y_idx;
	int   *x, *y, *z1, *z2;
	long long int *x_left, *x_right, *y_left, *y_right, *total;
	z1 = malloc(N * sizeof(long int));
	z2 = malloc(N * sizeof(long int));
	y = malloc(N * sizeof(long int));
	x = malloc(N * sizeof(long int));
	x_idx = malloc(N * sizeof(int));
	y_idx = malloc(N * sizeof(int));
	x_left = malloc(N * sizeof(long long int));
	y_left = malloc(N * sizeof(long long int));
	x_right = malloc(N * sizeof(long long int));
	y_right = malloc(N * sizeof(long long int));
	total = malloc(N * sizeof(long long int));

	for (i=0; i<N; ++i)
	{
		scanf("%d %d", &x[i], &y[i]);
		x_idx[i]=i;
		y_idx[i]=i;
		z1[i]=x[i];
		z2[i]=y[i];
	}
	
	quickSort(z1, x_idx, 0, N-1);
	quickSort(z2, y_idx, 0, N-1);

	x_left[0] = 0;
	y_left[0] = 0;
	
	for (i=1; i<N; ++i)
	{
		x_left[i] = x_left[i-1] + (x[x_idx[i]]-x[x_idx[i-1]])*i;	
		y_left[i] = y_left[i-1] + (y[y_idx[i]]-y[y_idx[i-1]])*i;
	}

	int k = 1;
	x_right[N-1]=0;
	y_right[N-1]=0;
	for (i=N-2; i>=0; --i)
	{
		x_right[i] = x_right[i+1] + (x[x_idx[i+1]]-x[x_idx[i]])*k; 	
		y_right[i] = y_right[i+1] + (y[y_idx[i+1]]-y[y_idx[i]])*k;
		k++;
	}

	for ( i = 0; i <N; ++i)
	{
		x_left[i] = x_left[i] + x_right[i];
		y_left[i] = y_left[i] + y_right[i];
		x_right[i]=0;
		y_right[i]=0;

	}

	for ( i = 0; i < N; ++i)
	{
		if (i != x_idx[i])
			x_right[x_idx[i]] = x_left[i]; 
		else
			x_right[i]=x_left[i];


		if (i!=y_idx[i])
			y_right[y_idx[i]] = y_left[i];
		else
			y_right[i] = y_left[i];
	}

	for (int i = 0; i < N; ++i)
	{
		total[i] = x_right[i] + y_right[i];
	}

	long long int min = LLONG_MAX;
	
	for (i = 0; i < N; ++i)
	{
		if (min > total[i])
		{
			min = total[i];
		}
	}
	free(z1);
	free(z2);
	free(y);
	free(x);
	free(x_idx);
	free(y_idx);
	free(x_left);
	free(y_left);
	free(x_right);
	free(y_right);
	free(total);
	printf("%llu\n",min);
	return 0;
}