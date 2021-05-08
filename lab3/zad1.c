#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RAND_TABLE_MAX_NUMBER 25//32767
#define SIZE_TO_SWITCH_TO_INSETION_SORT 15
//#define MEDIAN_GROUPS_SIZE 5


int* rand_table(int count);
void shuffle(int *array, int n);

int random_select(int n, int number[n], int left, int right, int* compare, int* swap, int kth_elem);
void insertion_sort(int n, int arr[n], int left, int right, int* compare, int* swap);
void quick_sort(int n, int number[n],int left,int right, int* compare, int* swap);
int partition(int array[], int low, int high, int* compare, int* swap);
int random_partition(int array[], int low, int high, int* compare, int* swap);

void swap_(int *a, int *b, int *swap);

int main(){
	int* mytable = rand_table(100);
	for(int i =0;i<100;i++)
		printf("%i ", mytable[i]);
	free(mytable);
	printf("\n");


	int* arr = rand_table(25);//malloc(25*sizeof(int));
	for(int i=0;i<25;i++){
		//arr[i]=i+5;
		printf("%i ", arr[i]);
	}
	printf("\n");

	shuffle(arr, 25);
	for(int i =0;i<25;i++)
		printf("%i ", arr[i]);	
	printf("\n");	
	int swap = 0;
	int compare = 0;
	//quick_sort(25, arr, 0, 24, &compare, &swap);
	insertion_sort(25, arr, 0, 24, &compare, &swap);	
	//int ret = random_select(25, arr, 0, 24, &compare, &swap, 10);
	//printf("\n%i\n", ret);
	for(int i =0;i<25;i++)
		printf("%i ", arr[i]);
	free(arr);
	printf("\n");
	return 0;
}

int* rand_table(int count) {
    int *ret = malloc(count*sizeof(int));
    if(!ret)
	{
        return NULL;
	}
	srand(time(NULL));
    for(int i = 0; i < count; ++i) 
	{
        ret[i] = rand()%RAND_TABLE_MAX_NUMBER;	
	}
    return ret;
}

void shuffle(int *array, int n)
{
    if (n > 1) {
		for (int i = 0; i < n - 1; i++) {
			int j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
    }
}


int select(int n, int number[n], int left, int right, int *compare, int* swap, int group_size){
	int size = right-left+1;
	if(size<=SIZE_TO_SWITCH_TO_INSETION_SORT)
	{
		insertion_sort(n, number, left, right, compare, swap);
		//????
	}
	int full_groups_amount = size/group_size;
	for(int i=0;i<full_groups_amount;i+=group_size){
		insertion_sort(n, number, left+i, left+i+group_size-1, compare, swap);
	}
	int remainder = size%group_size;
	if(remainder){
		insertion_sort(n, number, left, right, compare, swap);
	}
	
}




int random_select(int n, int number[n], int left, int right, int* compare, int* swap, int kth_elem)
{
	if(left==right)
	{
		return number[left];
	}
	int rand_pivot = random_partition(number, left, right, compare, swap);
	int k = rand_pivot-left+1;
	if(kth_elem==k)
	{
		return number[rand_pivot];
	}
	else if(kth_elem < k)
	{
		return random_select(n, number, left, rand_pivot-1, compare, swap, kth_elem);
	}
	return random_select(n, number, rand_pivot+1, right, compare, swap, kth_elem-k);
} 

void insertion_sort(int n, int arr[n], int left, int right, int* compare, int* swap)
{
	for(int i=left;i<=right;i++)
	{
		for(int j=i;j>left;j--)
		{
			if(arr[j]<arr[j-1])
			{
				//fprintf(stderr, "arr[%d]<arr[%d]\n", j, j-1);
				++*compare;
				
				int temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				
				//fprintf(stderr, "swap(arr[%d],arr[%d])\n", j, j-1);
				*swap = 2+*swap;
			}
			else
			{
				//fprintf(stderr, "arr[%d]>=arr[%d]\n", j, j-1);
				++*compare;
				break;
			}
		}
	}
}

void quick_sort(int n, int number[n],int left,int right, int* compare, int* swap)
{
	if(left<right)
	{
		int p = random_partition(number, left, right, compare, swap);
		quick_sort(n, number,left,p-1, compare, swap);
		quick_sort(n, number,p+1,right, compare, swap);
	}
}

int partition(int array[], int low, int high, int* compare, int* swap) {
	int pivot = array[high];
	int i = (low - 1);
	for (int j = low; j < high; j++) {
		if (array[j] <= pivot) {
			//fprintf(stderr, "number[%d]<=pivot(%d)\n", j, pivot);
			++*compare;
			i++;
			swap_(&array[i], &array[j], swap);
			//fprintf(stderr, "swap(number[%d],number[%d])\n", i, j);
		}
	}
	swap_(&array[i + 1], &array[high], swap);
	//fprintf(stderr, "swap(number[%d],number[%d])\n", i+1, high);
	return (i + 1);
}

int random_partition(int array[], int low, int high, int* compare, int* swap){
	int r = low + rand() % (high - low);
	swap_(&array[r], &array[high], swap);
	return partition(array, low, high, compare, swap);
}

void swap_(int *a, int *b, int *swap) {
	*swap = 2+*swap;
	int t = *a;
	*a = *b;
	*b = t;
}

