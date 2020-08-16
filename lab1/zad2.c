#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
	int number;
	struct Node *next;
};

void push_front(struct Node** front_element, int num);
void push_back(struct Node** front_element, int num);
void push_by_index(struct Node** front_element, int num, int index);

void pop_front(struct Node** front_element);
void pop_back(struct Node** front_element);
void pop_by_index(struct Node** front_element, int index);

struct Node* last(struct Node** front_element);
struct Node* penultimate(struct Node** front_element);
struct Node* elem_by_index(struct Node** front_element, int index);

void show(struct Node* front_element);
int size(struct Node* front_element);

struct Node* copy(struct Node* front_element);
struct Node* merge(struct Node* first, struct Node* second);

void clear(struct Node** front_element);



int main()
{
	struct Node* list0 = NULL;	
	struct Node* list1 = NULL;

	
	srand(time(NULL));
	double msec = 0;	
	int attempts_amount=10000;		//liczba prob

	int amount = 1000;
	for(int i=0;i<amount;i++)
	{
		push_back(&list0, rand());
	}
	int list_size = size(list0);
	
	for(int attempt=0;attempt<1;attempt++)
	{
		clock_t before = clock();
		for(int i=0;i<attempts_amount;i++)		//liczba prob
		{
			elem_by_index(&list0, (rand()%list_size));
		}
		clock_t difference = clock() - before;		
		msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//liczba prob
		printf("\ntime for %d elements - %g msec(random element)",amount, msec);			
	}
	
	for(int attempt=0;attempt<10;attempt++)
	{
		clock_t before = clock();
		for(int i=0;i<attempts_amount;i++)		//liczba prob
		{
			elem_by_index(&list0, attempt*100);
		}
		clock_t difference = clock() - before;		
		msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//liczba prob
		printf("\ntime for %d elements - %g msec(%d-th element)",amount, msec,attempt*100);			
	}	
	clear(&list0);
	
}

// wstawia element na pierwsza pozycje
void push_front(struct Node** front_element, int num)
{
	struct Node* new_front = (struct Node*)malloc(sizeof(struct Node));
	new_front->number=num;
	new_front->next=(*front_element);
	*front_element=new_front;
	return;
}

// wstawia nowy ostatni element new_last
void push_back(struct Node** front_element, int num)
{
	struct Node* new_last = (struct Node*)malloc(sizeof(struct Node));
	new_last->number=num;
	new_last->next=NULL;
	
	if(*front_element == NULL)
	{
		*front_element=new_last;
	}
	else
	{
		struct Node* last_elem = last(front_element);
		last_elem->next=new_last;
	}
	return;
}

// wstawianie elementu na pozycje "index"
void push_by_index(struct Node** front_element, int num, int index)
{
	if(index<0 || index>size(*front_element))
	{
		printf("\nIndex jest niepoprawny, \nprosze wpisac indeks od 0 do %d(push_by_index)\n", size(*front_element));
	}
	else
	{
		if(index == 0)
		{
			push_front(front_element, num);
		}
		else
		{
			struct Node* previous_elem = elem_by_index(front_element, index-1);
			struct Node* next_elem = previous_elem->next;
			struct Node* elem = (struct Node*)malloc(sizeof(struct Node));
			elem->number = num;
			elem->next = next_elem;
			previous_elem->next = elem;
		}
	}
	return;
}

// usuwa pierwszy element
void pop_front(struct Node** front_element)
{
	if((*front_element)==NULL || (*front_element)->next == NULL)
	{
		*front_element = NULL;
	}
	else
	{
		struct Node* new_front = (*front_element)->next;
		free(*front_element);
		*front_element=new_front;
	}
	return;	
}

// usuwa ostatni element
void pop_back(struct Node** front_element)
{
	if((*front_element)==NULL || (*front_element)->next == NULL)
	{
		*front_element = NULL;
	}
	else
	{
		struct Node* penult_elem = penultimate(front_element);
		struct Node* last_elem = penult_elem->next;
		free(last_elem);
		penult_elem->next=NULL;
	}
	return;
}

// usuwa element z indeksem "index"
void pop_by_index(struct Node** front_element, int index)
{
	if(index<0 || index>=size(*front_element))
	{
		printf("\nIndex jest niepoprawny, \nprosze wpisac indeks od 0 do %d(pop_by_index)\n", size(*front_element)-1);
	}
	else
	{
		if(index == 0)
		{
			pop_front(front_element);
		}
		else
		{
			struct Node* previous_elem = elem_by_index(front_element, index-1);
			struct Node* elem = previous_elem->next;
			struct Node* next_elem = elem->next;
			previous_elem->next = next_elem;
			free(elem);
		}
	}
	return;
}

// zwraca ostatni element listy
struct Node* last(struct Node** front_element)
{
	if(*front_element == NULL)
	{
		return NULL;
	}
	else
	{
		struct Node* elem;
		elem = *front_element;
		while(elem->next != NULL)
		{
			elem=elem->next;
		}
		return elem;
	}
}

// zwraca element przedostatni
struct Node* penultimate(struct Node** front_element)
{
	if(*front_element == NULL || (*front_element)->next == NULL)
	{
		return NULL;
	}
	else
	{
		struct Node* elem;
		elem = *front_element;
		while(elem->next->next != NULL)
		{
			elem=elem->next;
		}
		return elem;
	}	
}

// zwraca element z indeksem, jesli taki istnieje
struct Node* elem_by_index(struct Node** front_element, int index)
{
	struct Node* elem;
	elem = NULL;
	if(!size(*front_element))	//size==0
	{
		printf("\nLista jest pusta!(elem_by_index)\n");	
		return elem;
	}
	else if(index<0 || index>=size(*front_element))
	{
		printf("\nNie ma takiego elementu, \nprosze wpisac liczbe od 0 do %d(elem_by_index)\n", size(*front_element)-1);
		return elem;
	}
	else
	{
		
		elem = *front_element;
		int counter=0;
		while(counter<index)
		{
			elem=elem->next;
			counter++;
		}
		return elem;
	}
}

// drukuje liste
void show(struct Node* front_element)
{
	if(front_element == NULL)
	{
		printf("\nLista jest pusta!(show)\n");
	}
	else
	{
		struct Node* elem;
		elem = front_element;
		printf("\n");
		while(elem != NULL)
		{
			printf("%d ", elem->number);
			elem=elem->next;
		}
	}
}

// rozmiar listy
int size(struct Node* front_element)
{
	int counter = 0;
	if (front_element == NULL)
	{
		return counter;
	}
	counter = 1;
	while (front_element->next != NULL)
	{
		counter++;
		front_element=front_element->next;
	}
	return counter;
}

// zwraca kopie listy
struct Node* copy(struct Node* front_element)
{
	struct Node* ret = (struct Node*)malloc(sizeof(struct Node));
	ret = NULL;
	if(front_element == NULL)
	{
		return ret;
	}
	push_front(&ret, front_element->number);
	struct Node* temp = front_element;
	while(temp->next != NULL)
	{
		temp = temp->next;
		push_back(&ret, temp->number);
	}
	return ret;
}

// zwraca nowa liste, zlozona z first i second
struct Node* merge(struct Node* first, struct Node* second)
{
	struct Node* ret = (struct Node*)malloc(sizeof(struct Node));
	ret = NULL;
	if(first == NULL)
	{
		ret = copy(second);
	}
	else if(second == NULL)
	{
		ret = copy(first);
	}
	else
	{
		struct Node* elem1 = last(&first);		
		struct Node* elem2 = second;
		elem1->next = elem2;
		ret = copy(first);
		elem1->next = NULL;
	}
	return ret;
}

// usuwa wszystkie elementy listy
void clear(struct Node** front_element)
{
	struct Node* elem = *front_element;
	struct Node* next_elem;
	while(elem != NULL)
	{
		next_elem=elem->next;
		free(elem);
		elem = next_elem;
	}
	free(elem);
	free(next_elem);
	free(*front_element);
	*front_element=NULL;
}














