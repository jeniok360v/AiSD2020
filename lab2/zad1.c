#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef enum 
{
	insertSort, 
	mergeSort, 
	quickSort
} sortType;

void insertion_sort(int n, int arr[n], bool increase, int* compare, int* swap); 

void merge_sort(int n, int arr[n], int top, int bottom, bool increase, int* compare, int* swap);
void merge(int n, int arr[n], int top, int middle, int bottom, bool increase, int* compare, int* swap);

void quick_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap);

void sort(int n, int arr[n], sortType sort_type, bool increase);


int main(int argc, char* argv[])
{
	bool increase = true;	//default rosnancy
	sortType sort_type = 2;	//default quickSort
	
	for(int i=1;i<argc-1;i++)
	{
		if(!strcmp(argv[i], "--comp"))
		{
			if(!strcmp(argv[i+1], "rosn"))
			{
				increase = true;
			}
			else if(!strcmp(argv[i+1], "mal"))
			{
				increase = false;
			}
			else
			{
				printf("Zla opcja dla parametru --comp, prosze wpisac '>=' lub '<='\n");
			}
		}
		else if (!strcmp(argv[i], "--type"))
		{
			if(!strcmp(argv[i+1], "insert"))
			{
				sort_type=0;
			}
			else if(!strcmp(argv[i+1], "merge"))
			{
				sort_type=1;
			}
			else if (!strcmp(argv[i+1], "quick"))
			{
				sort_type=2;
			}
			else 
			{
				printf("Zla opcja dla parametru --type, prosze wpisac \"insert\", \"merge\" lub \"quick\"\n");
			}
		}
	}
	
	int i=0;
	int arr_size;
	
	//input	
	scanf("%d", &arr_size);
	int nums[arr_size];
	while (i < arr_size && scanf("%d", &nums[i]) == 1)
		i++;
	
	sort(arr_size, nums, sort_type, increase);
	return 0;
}


void sort(int n, int arr[n], sortType sort_type, bool increase)
{
	int compare=0;
	int swap=0;
	
	double msec=0;
	clock_t before = clock();
	if(sort_type == insertSort)
	{
		printf("insert sort\n");
		insertion_sort(n, arr, increase, &compare, &swap);
	}
	else if(sort_type == mergeSort)
	{
		printf("merge sort\n");	
		merge_sort(n, arr, 0, n-1, increase, &compare, &swap);		
	}
	else if(sort_type == quickSort)
	{
		printf("quick sort\n");	
		quick_sort(n, arr, 0, n-1, increase, &compare, &swap);
	}
	else
	{
		printf("Nie wybrano typu sortowania!\n");
	}
	clock_t difference = clock() - before;	
	msec = (double)(difference*1000/CLOCKS_PER_SEC);
	printf("time - %g msec\n", msec);	
	
	bool ordered =true;
	if(increase)
	{
		for(int i=0;i<n-1;i++)
		{
			if(!(arr[i]<=arr[i+1]))
			{
				ordered = false;
			}
		}
	}
	else
	{
		for(int i=0;i<n-1;i++)
		{
			if(!(arr[i]>=arr[i+1]))
			{
				ordered = false;
			}			
		}		
	}
	if(ordered)
	{
		printf("Array is ordered!\n");
	}
	else
	{
		printf("Array is not ordered!\n");
	}
	
	fprintf(stderr, "Liczba porownan: %d\n", compare);
	fprintf(stderr, "Liczba przemieszczen: %d\n", swap);
}


void insertion_sort(int n, int arr[n], bool increase, int* compare, int* swap)
{
	if (increase)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=i;j>0;j--)
			{
				if(arr[j]<arr[j-1])
				{
					fprintf(stderr, "arr[%d]<arr[%d]\n", j, j-1);
					++*compare;
					
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
					
					fprintf(stderr, "swap(arr[%d],arr[%d])\n", j, j-1);
					++*swap;
				}
				else
				{
					fprintf(stderr, "arr[%d]>=arr[%d]\n", j, j-1);
					++*compare;
					break;
				}
			}
		}
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			for(int j=i;j>0;j--)
			{
				if(arr[j]>arr[j-1])
				{
					fprintf(stderr, "arr[%d]>arr[%d]\n", j, j-1);
					++*compare;
					
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
					fprintf(stderr, "swap(arr[%d],arr[%d])\n", j, j-1);
					++*swap;
				}
				else
				{
					fprintf(stderr, "arr[%d]<=arr[%d]\n", j, j-1);
					++*compare;
					break;
				}
			}
		}		
	}
}


void merge(int n, int arr[n], int left, int middle, int right, bool increase, int* compare, int* swap)
{
	int sup1 = middle-left+1;
	int sup2 = right-middle;	
	
	int temp1[sup1];
	int temp2[sup2];
	
	for(int i=0;i<sup1;i++)
	{
		temp1[i]=arr[left+i];
	}
	for(int i=0;i<sup2;i++)
	{
		temp2[i]=arr[middle+i+1];
	}
	
	int i=0;
	int j=0;
	int k=left;
	if(increase)
	{
		while(i<sup1 && j<sup2)
		{
			if(temp1[i] < temp2[j])
			{
				fprintf(stderr, "temp1[%d]<temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp1[i];
				fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
				++*swap;
				i++;
				k++;
			}
			else
			{
				fprintf(stderr, "temp1[%d]>=temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp2[j];
				fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
				++*swap;
				j++;
				k++;
			}
		}
		
		while(i<sup1)
		{
			arr[k]=temp1[i];
			fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
			++*swap;
			i++;
			k++;
		}

		while(j<sup2)
		{
			arr[k]=temp2[j];
			fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
			++*swap;
			j++;
			k++;
		}
	}
	else
	{
		while(i<sup1 && j<sup2)
		{
			if(temp1[i] > temp2[j])
			{
				fprintf(stderr, "temp1[%d]>temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp1[i];
				fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
				++*swap;
				i++;
				k++;
			}
			else
			{
				fprintf(stderr, "temp1[%d]<temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp2[j];
				fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
				++*swap;
				j++;
				k++;
			}
		}
		
		while(i<sup1)
		{
			arr[k]=temp1[i];
			fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
			++*swap;
			i++;
			k++;
		}

		while(j<sup2)
		{
			arr[k]=temp2[j];
			fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
			++*swap;
			j++;
			k++;
		}		
	}
}

void merge_sort(int n, int arr[n], int left, int right, bool increase, int* compare, int* swap)
{
	if (left < right)
	{
		int middle = left+(right-left)/2;
		merge_sort(n, arr, left, middle, increase, compare, swap);
		merge_sort(n, arr, middle+1, right, increase, compare, swap);
		merge(n, arr, left, middle, right, increase, compare, swap);
	}
}


void quick_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap)
{
	if (increase)
	{
		if(left<right)
		{
			int pivot=right;
			int i=left;
			int j=right;
			while(i<j)
			{
				while(number[i]<=number[pivot] && i<right)
				{
					fprintf(stderr, "number[%d]<=number[%d]\n", i, pivot);
					fprintf(stderr, "%d<%d\n", i, right);
					*compare=*compare+2;
					i++;
				}
				while(number[j]>number[pivot])
				{
					fprintf(stderr, "number[%d]>number[%d]\n", j, pivot);	
					++*compare;
					j--;
				}
				if(i<j)
				{
					fprintf(stderr, "%d<%d\n", i, j);
					++*compare;
					int temp=number[i];
					number[i]=number[j];
					number[j]=temp;
					fprintf(stderr, "swap(number[%d],numer[%d])\n", j, i);
					++*swap;
					
				}
			}
			int temp=number[pivot];
			number[pivot]=number[j];
			number[j]=temp;
			fprintf(stderr, "swap(number[%d],numer[%d])\n", j, pivot);
			++*swap;
			quick_sort(n, number,left,j-1, increase, compare, swap);
			quick_sort(n, number,j+1,right, increase, compare, swap);
		}
	}
	else
	{
		if(left<right)
		{
			int pivot=right;
			int i=left;
			int j=right;
			while(i<j)
			{
				while(number[i]>=number[pivot] && i<right)
				{
					fprintf(stderr, "number[%d]>=number[%d]\n", i, pivot);
					++*compare;
					fprintf(stderr, "%d<%d\n", i, right);
					++*compare;
					i++;
				}
				while(number[j]<number[pivot])
				{
					fprintf(stderr, "number[%d]<number[%d]\n", i, pivot);
					++*compare;
					j--;
				}
				if(i<j)
				{
					fprintf(stderr, "%d<%d\n", i, j);
					++*compare;
					int temp=number[i];
					number[i]=number[j];
					number[j]=temp;
					fprintf(stderr, "swap(number[%d],numer[%d])\n", j, i);
					++*swap;
				}
			}
			int temp=number[pivot];
			number[pivot]=number[j];
			number[j]=temp;
			fprintf(stderr, "swap(number[%d],numer[%d])\n", j, pivot);
			++*swap;
			quick_sort(n, number,left,j-1, increase, compare, swap);
			quick_sort(n, number,j+1,right, increase, compare, swap);
		}		
	}
}

