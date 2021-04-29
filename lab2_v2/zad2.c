#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_TO_SWITCH_TO_INSETION_SORT 5

typedef enum 
{
	insertSort, 
	mergeSort, 
	quickSort,
	DPquickSort,
	hybridSort
} sortType;

typedef struct
{
	int lpivot;
	int rpivot;
} pair;

int* rand_table(int count);

void sort(int n, int arr[n], sortType sort_type, bool increase, int* compare, int* swap, double* timer_time);

void insertion_sort(int n, int arr[n], bool increase, int* compare, int* swap); 

void merge_sort(int n, int arr[n], int top, int bottom, bool increase, int* compare, int* swap);
void merge(int n, int arr[n], int top, int middle, int bottom, bool increase, int* compare, int* swap);

void quick_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap);
int  partition(int array[], int low, int high, int* compare, int* swap);

void dual_pivot_quick_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap);
void double_partition(int array[], int low, int high, int* compare, int* swap, int* i_ret, int* j_ret);

void dualPivotQuickSort(int* array, int start, int end, int* compares, int* moves, bool comp);
bool dualPivotFirstCompare(int x, int lp, int rp, bool flag, bool comp);
bool dualPivotSecondCompare(int x, int lp, int rp, bool flag, bool comp);
int dualPivotPartition(int* array, int start, int end, int* leftPivot, int* compares, int* swap, bool comp);

void hybrid_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap);

void swap_(int *a, int *b, int *swap);
void reverse(int arr[], int n);

int main(int argc, char* argv[])
{
   FILE *plotting;
   int repeats=1;

   //fp = fopen("/tmp/test.txt", "w+");
   //fprintf(fp, "This is testing for fprintf...\n");
   //fclose(fp);	
	
	
	bool manual = true;		//default bez argumentu --stat
	bool increase = true;	//default rosnancy
	sortType sort_type = 2;	//default quickSort
	printf("%li clock\n", CLOCKS_PER_SEC);
	
	for(int i=1;i<argc-1;i++)
	{
		if(!strcmp(argv[i], "--comp"))
		{
			if(!strcmp(argv[i+1], "inc"))
			{
				increase = true;		// ’<=’
			}
			else if(!strcmp(argv[i+1], "dec"))
			{
				increase = false;		// ’>=’
			}
			else
			{
				printf("Zla opcja dla parametru --comp, prosze wpisac '>=' lub '<='\n");
			}
			i++;
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
			else if (!strcmp(argv[i+1], "dpquick"))
			{
				sort_type=3;
			}
			else if (!strcmp(argv[i+1], "hybrid"))
			{
				sort_type=4;
			}			
			else 
			{
				printf("Zla opcja dla parametru --type, prosze wpisac \"insert\", \"merge\", \"quick\", \"dpquick\"  lub \"hybrid\"\n");
			}
			i++;
		}
		else if(!strcmp(argv[i], "--stat"))
		{
			plotting = fopen(argv[i+1], "w+");
			repeats = atoi(argv[i+2]);
			manual = false;
			i+=2;
		}
	}
	
	if(manual)
	{
		int i=0;
		int arr_size;
		int swap=0;
		int compare=0;
		double timer_time=0.0;
		
		//input, rozmiar tablicy do posortowania	
		scanf("%d", &arr_size);
		
		int nums[arr_size];
		while (i < arr_size && scanf("%d", &nums[i]) == 1)
			i++;
		
		sort(arr_size, nums, sort_type, increase, &compare, &swap, &timer_time);
		printf("\n[");
		for (int jk = 0;jk<arr_size;jk++){
			printf("%i, ", nums[jk]);
		}
		printf("]\n");


	}
	else
	{
		const int SIZE = 50;
		//int sizes[11] = { 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000, 10000 };
		/*
		int sizes[100];
		for(int i=0;i<100;i++){
			sizes[i]=i*100+100;
		}
		*/
		int sizes[50];
		for(int i=0;i<50;i++){
			sizes[i]=i+1;
		}		

		for(int j=0;j<SIZE;j++){
			int compare;// = 0;
			int swap;// = 0;
			double timer_time;// = 0.0; 

			double compare_ = 0;
			double swap_ = 0;
			double timer_time_ = 0.0;

			for(int i=0;i<repeats;i++){
				compare = 0;
				swap = 0;
				timer_time = 0;
				int* my_table = rand_table(sizes[j]);
				//printf("sorting...\n");
				sort(sizes[j], my_table, sort_type, increase, &compare, &swap, &timer_time);
				compare_+=((double)compare/(double)repeats);
				swap_+=((double)swap/(double)repeats);
				timer_time_+=((double)timer_time/(double)repeats);
				//printf("time2 - %g msec\n", timer_time_);	
				free(my_table);
			}	
			fprintf(plotting, "%i\t%lf\t%lf\t%lf\t%lf\t%lf\n", sizes[j], compare_, swap_, (double)compare_/(double)sizes[j], (double)swap_/(double)sizes[j], timer_time_);
		}	

		fclose(plotting);
	}
	return 0;
}

int* rand_table(int count) {
    int *ret = malloc(count*sizeof(int));
    if(!ret)
	{
        return NULL;
	}
    for(int i = 0; i < count; ++i) 
	{
        ret[i] = rand()%32767;	//liczba pseudolosowa z uzyciem adresu i rand()
	}
    return ret;
}


void sort(int n, int arr[n], sortType sort_type, bool increase, int* compare, int* swap, double* msec)
{
	
	clock_t before = clock();
	if(sort_type == insertSort)
	{
		//printf("insert sort\n");
		insertion_sort(n, arr, increase, compare, swap);
	}
	else if(sort_type == mergeSort)
	{
		//printf("merge sort\n");	
		merge_sort(n, arr, 0, n-1, increase, compare, swap);		
	}
	else if(sort_type == quickSort)
	{
		//printf("quick sort\n");	
		quick_sort(n, arr, 0, n-1, increase, compare, swap);
		if(!increase)
			reverse(arr, n);
	}
	else if(sort_type == DPquickSort)
	{
		//printf("dual pivot quick sort\n");	
		//dualPivotQuickSort(arr, 0, n-1, compare, swap, !increase);
		dual_pivot_quick_sort(n, arr, 0, n-1, increase, compare, swap);
		if(!increase)
			reverse(arr, n);
	}
	else if(sort_type == hybridSort)
	{
		//printf("hybrid sort\n");
		hybrid_sort(n, arr, 0, n-1, increase, compare, swap);
		if(!increase)
			reverse(arr, n);
	}		
	else
	{
		printf("Nie wybrano typu sortowania!\n");
	}
	clock_t difference = clock() - before;	
	*msec = (double)((double)difference*1000.0/(double)CLOCKS_PER_SEC);
	//printf("time - %g msec\n", *msec);	
	
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
		//printf("Array is ordered!\n");
	}
	else
	{
		//printf("Array is not ordered!\n");
	}
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
	else
	{
		for(int i=0;i<n;i++)
		{
			for(int j=i;j>0;j--)
			{
				if(arr[j]>arr[j-1])
				{
					//fprintf(stderr, "arr[%d]>arr[%d]\n", j, j-1);
					++*compare;
					
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
					//fprintf(stderr, "swap(arr[%d],arr[%d])\n", j, j-1);
					*swap = 2+*swap;
				}
				else
				{
					//fprintf(stderr, "arr[%d]<=arr[%d]\n", j, j-1);
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
				//fprintf(stderr, "temp1[%d]<temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp1[i];
				//fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
				++*swap;
				i++;
				k++;
			}
			else
			{
				//fprintf(stderr, "temp1[%d]>=temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp2[j];
				//fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
				++*swap;
				j++;
				k++;
			}
		}
		
		while(i<sup1)
		{
			arr[k]=temp1[i];
			//fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
			++*swap;
			i++;
			k++;
		}

		while(j<sup2)
		{
			arr[k]=temp2[j];
			//fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
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
				//fprintf(stderr, "temp1[%d]>temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp1[i];
				//fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
				++*swap;
				i++;
				k++;
			}
			else
			{
				//fprintf(stderr, "temp1[%d]<temp2[%d]\n", i, j);
				++*compare;
				arr[k] = temp2[j];
				//fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
				++*swap;
				j++;
				k++;
			}
		}
		
		while(i<sup1)
		{
			arr[k]=temp1[i];
			//fprintf(stderr, "arr[%d]=%d\n", k, temp1[i]);
			++*swap;
			i++;
			k++;
		}

		while(j<sup2)
		{
			arr[k]=temp2[j];
			//fprintf(stderr, "arr[%d]=%d\n", k, temp2[j]);
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
	if(left<right)
	{
		int p = partition(number, left, right, compare, swap);
		quick_sort(n, number,left,p-1, increase, compare, swap);
		quick_sort(n, number,p+1,right, increase, compare, swap);
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


void dual_pivot_quick_sort(int n, int number[n],int left,int right, bool increase, int* compare, int* swap)
{
	if(left+1<right)
	{
		int var1;
		int var2;
		int* i_ret = &var1;
		int* j_ret = &var2;
		*i_ret = 0;
		*j_ret = 0;
		//pair *p = double_partition(number, left, right, compare, swap);
		double_partition(number, left, right, compare, swap, i_ret, j_ret);

		dual_pivot_quick_sort(n, number, left,       (*i_ret)-1, increase, compare, swap);
		dual_pivot_quick_sort(n, number, (*i_ret)+1, (*j_ret)-1, increase, compare, swap);
		dual_pivot_quick_sort(n, number, (*j_ret)+1, right,      increase, compare, swap);
	}
	else if(right-left==1){
		if(number[left]>number[right]){
			++*compare;
			swap_(&number[left], &number[right], swap);
		}
	}
	
}

void double_partition(int array[], int low, int high, int* compare, int* swap, int* i_ret, int* j_ret) {
	int s = 0; //smaller then left pivot (counter)
	int l = 0; //larger then ritght pivot (counter)
	if(array[high]<array[low]){
		//printf("bounds swap!\n");
		swap_(&array[low], &array[high], swap);
	}

	int lpivot = array[low];
	int rpivot = array[high];
	int i = low+1;
	int j = high-1;
	int k = low+1;
	while(k<=j){
		if(s>l){
			if(array[k] <= lpivot){
				//fprintf(stderr, "number[%d]<=pivot(%d)\n", k, lpivot);
				swap_(&array[k], &array[i], swap);
				i++; k++; s++;
				*compare=*compare+1;

			}
			else if(array[k] >= rpivot){
				//fprintf(stderr, "number[%d]>=rpivot(%d)\n", k, rpivot);
				swap_(&array[k], &array[j], swap);
				j--; l++;
				*compare=*compare+2;
			}
			else{
				k++;
				*compare=*compare+2;
			}
		}
		else{
			if(array[k] >= rpivot){
				*compare=*compare+1;
				//fprintf(stderr, "number[%d]>=rpivot(%d)\n", k, rpivot);
				swap_(&array[k], &array[j], swap);
				j--; l++;
			}
			else if(array[k] <= lpivot){
				*compare=*compare+2;
				//fprintf(stderr, "number[%d]<=pivot(%d)\n", k, lpivot);
				swap_(&array[k], &array[i], swap);
				i++; k++; s++;
			}
			else{
				k++;
				*compare=*compare+2;			
			}
		}
	}
	i--;
	j++;
	swap_(&array[i], &array[low],  swap);
	swap_(&array[j], &array[high], swap);

	*i_ret = i;
	*j_ret = j;

	//pair *ret = NULL;
	//ret->lpivot = i;
	//ret->rpivot = j;
	//return ret;
}

/*
void dualPivotQuickSort(int* array, int start, int end, int* compares, int* moves, bool comp){
    if (start < end) {
        int leftPivot, rightPivot; 
        rightPivot = dualPivotPartition(array, start, end, &leftPivot, compares, moves, comp);	
		
        dualPivotQuickSort(array, start, leftPivot - 1, compares, moves, comp);	
        dualPivotQuickSort(array, leftPivot + 1, rightPivot - 1, compares, moves, comp);	
        dualPivotQuickSort(array, rightPivot + 1, end, compares, moves, comp);
    }
}
 
bool dualPivotFirstCompare(int x, int lp, int rp, bool flag, bool comp){
	if(!flag && !comp)    //left pivot, ascending
		return x < lp;
	
	if(flag && !comp)	//right pivot, ascending
		return x >= rp;
	
	if(!flag && comp)	//left pivot, descending
		return x >= lp;
	
	if(flag && comp)	//right pivot, descending
		return x < rp;
	
	return false;
}

bool dualPivotSecondCompare(int x, int lp, int rp, bool flag, bool comp){
	if(!flag && !comp) 		//right pivot, ascending
		return x >= rp;
	
	if(flag && !comp)		//left pivot, ascending
		return x < lp;
	
	if(!flag && comp)		//right pivot, descending
		return x < rp;
	
	if(flag && comp)		//left pivot, descending
		return x >= lp;
	
	return false;
}
	

int dualPivotPartition(int* array, int start, int end, int* leftPivot, int* compares, int* swap, bool comp){
    if(++(*compares) && array[start] > array[end] && !comp){		
        swap_(&array[start], &array[end], swap); 
	}
	else if(++(*compares) && array[start] < array[end] && comp){	
        swap_(&array[start], &array[end], swap); 
	}
	
    int i = start + 1;		
    int right = end - 1;	
	int left = start + 1;	
	int lp = array[start];	
	int rp = array[end];	
	int count = 0;			
	bool countFlag;			
	bool swapLeft = false;	
	bool swapRight = false; 	
	
    while (i <= right) {		
 		if (count > 0)				
			countFlag = true;
		else
			countFlag = false;
		
        if (++(*compares) && dualPivotFirstCompare(array[i], lp, rp, countFlag, comp)) { 
            if(!countFlag)		
				swapLeft=true;
			else 
				swapRight=true;
        }
        else if (++(*compares) && dualPivotSecondCompare(array[i], lp, rp, countFlag, comp)) {		
			if (!countFlag)
				swapRight=true;
			else
				swapLeft=true;
        }
		
		if(swapLeft){		
			swap_(&array[i], &array[left++], swap); 	
			count--;										
			swapLeft=false;										
		}
		else if(swapRight){		
			while (!countFlag && ++(*compares) && dualPivotSecondCompare(array[right],lp,rp, countFlag, comp) && i < right) 	
            	right--;
			while (countFlag && ++(*compares) && dualPivotFirstCompare(array[right],lp,rp, countFlag, comp) && i < right)  
            	right--;
			
            swap_(&array[i], &array[right--], swap);  
			count++;			
           
			if (!countFlag && dualPivotFirstCompare(array[i], lp, rp, countFlag, comp)) {		
				swap_(&array[i], &array[left++], swap); 	
				count--;
			}
			else if (countFlag && dualPivotSecondCompare(array[i], lp, rp, countFlag, comp)) { 
				swap_(&array[i], &array[left++], swap); 	
				count--;
			}
			swapRight=false;  
		}
		
        i++;		
    }
    left--;				
    right++;

	
    swap_(&array[start], &array[left], swap);		
    swap_(&array[end], &array[right], swap);

    *leftPivot = left; 			
    return right;				
}
*/

void hybrid_sort(int n, int number[n],int left, int right, bool increase, int* compare, int* swap)
{
	if(right<left+SIZE_TO_SWITCH_TO_INSETION_SORT){
		for(int i=left;i<=right;i++)
		{
			for(int j=i;j>0;j--) //j>left
			{
				if(number[j]<number[j-1])
				{
					++*compare;
					swap_(&number[j], &number[j-1], swap);
				}
				else
				{
					++*compare;
					break;
				}
			}
		}
	}
	else{
		int p = partition(number, left, right,           compare, swap);
		hybrid_sort(n, number,    left, p-1,   increase, compare, swap);
		hybrid_sort(n, number,    p+1,  right, increase, compare, swap);		
	}
}	


void swap_(int *a, int *b, int *swap) {
	*swap = 2+*swap;
	int t = *a;
	*a = *b;
	*b = t;
}

void reverse(int arr[], int n)
{
    for (int low = 0, high = n - 1; low < high; low++, high--)
    {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
}



