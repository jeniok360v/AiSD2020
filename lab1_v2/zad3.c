#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
	int number;
	struct Node *next;
	struct Node *prev;
};

struct Double_linked_list
{
	struct Node* head;
	int size;
};

void init (struct Double_linked_list** list);
void copy (struct Double_linked_list*  copy, struct Double_linked_list* paste);
void merge(struct Double_linked_list*  in_1, struct Double_linked_list* in_2, struct Double_linked_list* out);

void push_front(struct Double_linked_list* list, int num);
void push_index(struct Double_linked_list* list, int num, int index);

int** pop_front(struct Double_linked_list* list, int** out);
int** pop_index(struct Double_linked_list* list, int** out, int index);

struct Node* elem_by_index(struct Double_linked_list* list, int index);

void clear_list(struct Double_linked_list* list);
void print_list(struct Double_linked_list* list);


int main()
{
	struct Double_linked_list* list;
	init(&list);

	srand(time(NULL));
	double msec = 0;	
	int attempts_amount=10000;		//liczba prob

	int elem_amount = 1000;
	for(int i=0;i<elem_amount;i++)
	{
		push_front(list, rand());
	}		

	/*~~~ czas dostepu do elementu numer 0, 100, ... , 999 ~~~*/
	for(int hundreds=0;hundreds<1000;hundreds+=100)
	{
		clock_t before = clock();
		for(int i=0;i<attempts_amount;i++)		//liczba prob
		{
			elem_by_index(list, hundreds);
		}
		clock_t difference = clock() - before;		
		msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//liczba prob
		printf("\ntime for %d elements - %g msec(%d-th element)", elem_amount, msec, hundreds);			
	}

	/*~~~ czas dostepu do losowego elementu ~~~*/
	clock_t before = clock();
	for(int i=0;i<attempts_amount;i++)		//liczba prob
	{
		elem_by_index(list, rand()%list->size);
	}
	clock_t difference = clock() - before;		
	msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//liczba prob
	printf("\ntime for %d elements - %g msec(random element)\n", elem_amount, msec);			


	/*~~~merge test~~~*/ 
	struct Double_linked_list* list1;
	struct Double_linked_list* list2;
	struct Double_linked_list* list3;
	init(&list1);
	init(&list2);
	init(&list3);

	push_front(list1, 1);
	push_front(list1, 2);
	push_front(list1, 3);
	push_front(list1, 4);
	push_front(list1, 5);
	push_front(list1, 6);
	push_front(list1, 7);
	push_index(list1, 8, 0);
	print_list(list1);

	push_front(list2, 4333);
	push_front(list2, 5);
	push_front(list2, 324);
	push_front(list2, 122);
	push_front(list2, 662);
	push_front(list2, 432);
	push_front(list2, 554);
	push_index(list2, 736, 2);
	print_list(list2);	

	merge(list1, list2, list3);
	print_list(list3);

	push_front(list1, 1);
	push_front(list2, 2);
	push_front(list3, 3);	

	print_list(list1);
	print_list(list2);
	print_list(list3);
	return 0;
}


void init(struct Double_linked_list** list){

	*list = (struct Double_linked_list*)calloc(1, sizeof(struct Double_linked_list));

    if ((*list) == NULL)
    {
    	printf("Nie udało się zainicjalizować Double_linked_list\n");
        exit;
    }

    (*list)->head = NULL;
    (*list)->size = 0;
}

// zwraca kopie listy
void copy(struct Double_linked_list* list1, struct Double_linked_list* list2)
{
	if((list1)->head == NULL)
	{
		clear_list(list2);
		return;
	}
	else if((list1)->size == 1)
	{
		clear_list(list2);
		push_front(list2, list1->head->number);
		return;
	}
	else
	{
		clear_list(list2);
		int nums[list1->size];
		struct Node* elem;
		elem = list1->head;

		for(int i=0;i<list1->size;i++){
			nums[i] = elem->number;
			elem = elem->next;
		}

		for(int i=list1->size-1;i>=0;i--){
			push_front(list2, nums[i]);
		}
	}
	return;
}

void merge(struct Double_linked_list* in_1, struct Double_linked_list* in_2, struct Double_linked_list* out)
{
	clear_list(out);
	if(in_1->size == 0){
		copy(in_2, out);
		return;
	}
	else if (in_2->size == 0){
		copy(in_1, out);
		return;
	}

	int nums1[in_1->size];
	int nums2[in_2->size];
	struct Node* elem;

	elem = in_1->head;
	for(int i=0;i<in_1->size;i++){
		nums1[i] = elem->number;
		elem = elem->next;
	}

	elem=in_2->head;
	for(int i=0;i<in_2->size;i++){
		nums2[i] = elem->number;
		elem = elem->next;
	}


	for(int i=in_2->size-1;i>=0;i--){
		push_front(out, nums2[i]);
	}
	for(int i=in_1->size-1;i>=0;i--){
		push_front(out, nums1[i]);
	}
	return;
}


void push_front(struct Double_linked_list* list, int num)
{
	struct Node* new_front = (struct Node*)malloc(sizeof(struct Node));
	new_front->number=num;
	if(!list->size){
		new_front->next=new_front;
		new_front->prev=new_front;
		list->head=new_front;
		list->size++;
		return;
	}
	new_front->next=list->head;
	new_front->prev=list->head->prev;

	list->head->prev->next=new_front; //??
	list->head->prev=new_front;

	list->head=new_front;
	list->size++;
	return;
}

// wstawianie elementu na pozycje "index"
void push_index(struct Double_linked_list* list, int num, int index)
{
	if(index<0 || index>list->size)
	{
		printf("\nIndex jest niepoprawny, \nprosze wpisac indeks od 0 do %d(push_index)\n", list->size);
		printf("Wpisany indeks: %d\n", index);
	}
	else
	{
		if(index == 0)
		{
			push_front(list, num);
		}
		else
		{
			struct Node* prev_elem = elem_by_index(list, index-1);
			struct Node* next_elem = prev_elem->next;
			struct Node* elem = (struct Node*)malloc(sizeof(struct Node));
			elem->number = num;

			elem->next = next_elem;
			elem->prev = prev_elem;

			prev_elem->next = elem;
			next_elem->prev = elem;

			list->size++;
		}
	}
	return;
}


// usuwa pierwszy element
int** pop_front(struct Double_linked_list* list, int** out)
{
	if(list->size==0)
	{
		*out = NULL;

		printf("Lista jest pusta!(pop_front)\n");
	}
	else if(list->size==1)
	{
		**out=list->head->number;

		list->head = NULL;
		list->size = 0;
	}
	else
	{
		**out=list->head->number;

		struct Node* new_front = list->head->next;
		struct Node* last_elem = list->head->prev;
		free(list->head);

		last_elem->next = new_front;
		new_front->prev = last_elem;
		
		list->head=new_front;
		list->size--;
	}
	return out;	
}

int** pop_index(struct Double_linked_list* list, int** out, int index)
{
	if(!list->size){ //size==0
		*out = NULL;

		printf("\nLista jest pusta!(pop_index)\n");	
	}
	else if(index<0 || index>=list->size)
	{
		*out = NULL;

		printf("\nIndex jest niepoprawny, \nprosze wpisac indeks od 0 do %d(pop_index)\n", list->size-1);
		printf("Wpisany indeks: %d\n", index);
	}
	else
	{
		if(index == 0)
		{
			pop_front(list, out);
		}
		else
		{
			struct Node* prev_elem = elem_by_index(list, index-1);
			struct Node* elem = prev_elem->next;
			struct Node* next_elem = elem->next;
			**out = elem->number;

			prev_elem->next = next_elem;
			next_elem->prev = prev_elem;

			free(elem);
			list->size--;
		}
	}
	return out;
}


// zwraca element z indeksem, jesli taki istnieje
struct Node* elem_by_index(struct Double_linked_list* list, int index)
{
	struct Node* elem;
	elem = NULL;
	if(!list->size)	//size==0
	{
		printf("\nLista jest pusta!(elem_by_index)\n");	
	}
	else if(index<0 || index>=list->size)
	{
		printf("\nNie ma takiego elementu, \nprosze wpisac liczbe od 0 do %d(elem_by_index)\n", list->size-1);
	}
	else
	{
		elem = list->head;
		if(index > list->size>>1){
			int c = list->size - index;
			while(c){
				elem=elem->prev;
				c--;
			}
		}
		else{
			int c = index;
			while(c)
			{
				elem=elem->next;
				c--;
			}
		}
	}
	return elem;
}

// usuwa wszystkie elementy z listy
void clear_list(struct Double_linked_list* list)
{
	if(!list->size){
		return;
	}
	struct Node* elem = list->head;
	for(int i=0;i<list->size-1;i++)
	{
		elem=elem->next;
		free(elem->prev);
	}
	free(elem);
	list->head = NULL;
	list->size = 0;
	return;
}

// drukuje liste
void print_list(struct Double_linked_list* list)
{
	if(list->head == NULL)
	{
		printf("\nLista jest pusta!(print_list)\n");
	}
	else
	{
		struct Node* elem;
		elem = list->head;
		printf ("\ngłowa ->-->- Double_linked_list ->-->- ogon (rozmiar %i)\n", list->size);
		for(int i=0;i<list->size;i++)
		{
			printf("%d ", elem->number);
			elem=elem->next;
		}
		printf("\n");
	}
}