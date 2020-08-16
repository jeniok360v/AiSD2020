#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
	int number;
	struct Node *next;
	struct Node *previous;
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

	int amount = 1000;		//ile wstawic elementow do listy
	for(int i=0;i<amount;i++)
	{
		push_back(&list0, rand());
	}
	int list_size = size(list0);	//rozmiar listy (to samo co i amount)
	for(int attempt=0;attempt<1;attempt++)
	{
		clock_t before = clock();
		for(int i=0;i<attempts_amount;i++)		//liczba prob
		{
			elem_by_index(&list0, (rand()%list_size));
		}
		clock_t difference = clock() - before;		
		msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//czas w milisekundach(10000 prob)
		printf("\ntime for %d elements - %g msec(random element)",amount, msec);			
	}
	
	for(int attempt=0;attempt<10;attempt++)	// czas dostepu nie do losowego elementu
	{
		clock_t before = clock();
		for(int i=0;i<attempts_amount;i++)		//liczba prob
		{
			elem_by_index(&list0, attempt*25);
		}
		clock_t difference = clock() - before;		
		msec = (double)(difference*1000/CLOCKS_PER_SEC)/attempts_amount;	//liczba prob
		printf("\ntime for %d elements - %g msec(%d-th element)",amount, msec,attempt*100);			
	}	
}

// wstawia element na pierwsza pozycje
void push_front(struct Node** front_element, int num)
{
	struct Node* new_front = (struct Node*)malloc(sizeof(struct Node));
	new_front->number=num;

	// jesli lista jest pusta
	if(*front_element == NULL)
	{
		new_front->next = new_front;
		new_front->previous = new_front;
	}
	else 
	{
		struct Node* last_elem = last(front_element);
		new_front->next=(*front_element);
		new_front->previous = last_elem;
		(*front_element)->previous=new_front;
		last_elem->next=new_front;
	}
	*front_element=new_front;		
	return;
}

// wstawia nowy ostatni element new_last
void push_back(struct Node** front_element, int num)
{
	struct Node* new_last = (struct Node*)malloc(sizeof(struct Node));
	new_last->number=num;
	if(*front_element == NULL)
	{
		new_last->next=new_last;
		new_last->previous=new_last;
		*front_element=new_last;
	}
	else
	{
		struct Node* last_elem = last(front_element);
		last_elem->next=new_last;
		(*front_element)->previous=new_last;
		
		new_last->next=(*front_element);
		new_last->previous=last_elem;
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
			elem->previous = previous_elem;
			
			previous_elem->next = elem;
			next_elem->previous = elem;
		}
	}
	return;
}

// usuwa pierwszy element
void pop_front(struct Node** front_element)
{
	if((*front_element)==NULL || (*front_element)->next == (*front_element))
	{
		*front_element = NULL;
	}
	else
	{
		struct Node* new_front = (*front_element)->next;
		struct Node* last_elem = (*front_element)->previous;
		new_front->previous=last_elem;
		last_elem->next=new_front;
		free(*front_element);
		*front_element=new_front;
	}
	return;	
}

// usuwa ostatni element
void pop_back(struct Node** front_element)
{
	if((*front_element)==NULL || (*front_element)->next == *front_element)
	{
		*front_element = NULL;
	}
	else
	{
		struct Node* penult_elem = penultimate(front_element);
		struct Node* last_elem = last(front_element);
		penult_elem->next=*front_element;
		(*front_element)->previous=penult_elem;
		free(last_elem);
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
			struct Node* elem = elem_by_index(front_element, index);
			struct Node* previous_elem = elem->previous;
			struct Node* next_elem = elem->next;
			
			previous_elem->next = next_elem;
			next_elem->previous = previous_elem;
			free(elem);
		}
	}
	return;
}

// zwraca poprzedni element glowy listy
struct Node* last(struct Node** front_element)
{
	struct Node* elem = (struct Node*)malloc(sizeof(struct Node));
	elem = NULL;
	if(*front_element == NULL)
	{
		printf("\nLista jest pusta!(last())\n");
		return elem;
	}
	else
	{
		elem = (*front_element)->previous;
		return elem;
	}
}

// zwraca element przedostatni
struct Node* penultimate(struct Node** front_element)
{
	struct Node* elem;
	if(*front_element == NULL )
	{
		elem = NULL;
	}
	else
	{
		elem = (*front_element)->previous->previous;
	}	
	return elem;
}

// zwraca element z indeksem, jesli taki istnieje
struct Node* elem_by_index(struct Node** front_element, int index)
{
	struct Node* elem;
	elem = NULL;
	if(!size(*front_element))	//size==0
	{
		printf("\nLista jest pusta!(elem_by_index)\n");	
	}
	else if(index<0 || index>=size(*front_element))
	{
		printf("\nNie ma takiego elementu, \nprosze wpisac liczbe od 0 do %d(elem_by_index)\n", size(*front_element)-1);
	}
	// jesli element jest w pierwszej polowie listy,
	// to szukamy za pomoca elem->next
	else if(index<size(*front_element)/2)
	{	
		elem = *front_element;
		int counter=0;
		while(counter<index)
		{
			elem=elem->next;
			counter++;
		}
	}
	// w przeciwnym przypadku szukamy z konca(elem->previous)
	else 
	{
		elem = *front_element;
		int counter=size(*front_element)-index;
		while(counter>0)
		{
			elem=elem->previous;
			counter--;
		}	
	}
	return elem;
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
		struct Node* last_elem = last(&front_element);
		struct Node* elem;
		elem = front_element;
		printf("\n%d ", elem->number);
		while(elem != last_elem)
		{
			elem=elem->next;
			printf("%d ", elem->number);
		}
	}
	return;
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
	struct Node* last_elem = last(&front_element);
	struct Node* elem = front_element;
	while (elem != last_elem)
	{
		counter++;
		elem=elem->next;
	}
	return counter;
}

// kopia listy
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
	int co=0;
	while(temp->next != front_element)
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
		struct Node* first1 = first;		
		struct Node* last1 = last(&first);
		struct Node* first2 = second;		
		struct Node* last2 = last(&second);
		last1->next = first2;
		first2->previous = last1;
		first1->previous = last2;
		last2->next = first1;
		
		ret = copy(first1);
		
		last1->next = first1;
		first1->previous = last1;
		last2->next = first2;
		first2->previous = last2;
	}
	return ret;
}

// usuwanie wszystkich elementow listy
void clear(struct Node** front_element)
{
	if(*front_element == NULL)
	{
		return;
	}
	struct Node* elem = *front_element;
	struct Node* next_elem;
	struct Node* last_elem = last(front_element);
	while(elem != last_elem)
	{
		next_elem=elem->next;
		free(elem);
		elem = next_elem;
	}
	free(elem);
	free(next_elem);
	free((*front_element)->previous);
	*front_element=NULL;
	return;
}
