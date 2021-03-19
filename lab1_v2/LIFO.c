#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node 
{ 
	struct Node* next;
	int number;
}; 

struct LIFO
{
	struct Node* head;
	struct Node* tail;
	int size;
};

void init(struct LIFO** queue);
void push(struct LIFO*  queue, int num);
int** pop(struct LIFO*  queue, int** output);
void list(struct LIFO*  queue);


int main() 
{
	struct LIFO* queue;
	init(&queue);

	srand(time(NULL));
	for(int i = 0;i<100;i++){
		int r = rand()%256-128;
		push(queue, r);
		printf("added %i to LIFO\n", r);
	}

	list(queue);

	for(int i=0;i<103;i++){ // 3 razy próbuję wyciągnąć element z pustej kolejki
		int* out;
		pop(queue, &out);
		if(out != NULL){
			printf("popped element %i\n", *out);
		}
	}
	return 0; 
}

void init(struct LIFO** queue)
{
    *queue = (struct LIFO*)calloc(1, sizeof(struct LIFO));

    if ((*queue) == NULL)
    {
    	printf("Nie udało się zainicjalizować kolejkę LIFO");
        exit;
    }

    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    (*queue)->size = 0;

    return;
}

// dodaje element na koniec kolejki
void push(struct LIFO* queue, int num)
{
	if (queue->head == NULL)
	{
		queue->head =(struct Node* )malloc(sizeof(struct Node));

		queue->head->next = NULL;
		queue->head->number = num;
		queue->tail = queue->head;
	}
	else
	{
		struct Node* new_last = (struct Node*)malloc(sizeof(struct Node));
		new_last->next = queue->tail;
		new_last->number = num;

		queue->tail = new_last;
	}
	queue->size++;
	return;
}



// usuwa pierwszy element
int** pop(struct LIFO* queue, int** output)
{
	if(queue->tail != NULL)
	{
		**output = queue->tail->number;
		struct Node* new_tail = queue->tail->next;
		free(queue->tail);
		queue->tail = new_tail;
		queue->size--;	
		if(queue->size == 0)
		{
			queue->head = NULL;
		}
	}
	else
	{
		printf("\nLista jest pusta!\n");
		*output = NULL;
	}

	return output;
}


// drukuje wszystkie elementy po kolei
void list(struct LIFO* queue)
{
	if (queue->tail != NULL)
	{
		printf ("\nogon ->-->- kolejka ->-->- glowa (rozmiar %i)\n", queue->size); 		
		struct Node* elem = queue->tail;
		printf ("%d ",elem->number); 
		while(elem->next != NULL)
		{
			elem=elem->next;	
			printf ("%d ",elem->number); 
		}
		printf("\n");
	}
	else
	{
		printf("\nLista jest pusta!\n");
	}
	return;
}