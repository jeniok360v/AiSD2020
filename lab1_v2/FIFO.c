#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node 
{ 
	struct Node* next;
	int number;
}; 

struct FIFO
{
	struct Node* head;
	struct Node* tail;
	int size;
};

void init(struct FIFO** queue);
void push(struct FIFO*  queue, int num);
int** pop(struct FIFO*  queue, int** output);
void list(struct FIFO*  queue);


int main() 
{
	struct FIFO* queue;
	init(&queue);

	srand(time(NULL));
	for(int i = 0;i<100;i++){
		int r = rand()%256-128;
		push(queue, r);
		printf("added %i to FIFO\n", r);
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

void init(struct FIFO** queue)
{
    *queue = (struct FIFO*)calloc(1, sizeof(struct FIFO));

    if ((*queue) == NULL)
    {
    	printf("Nie udało się zainicjalizować kolejkę FIFO");
        exit;
    }

    (*queue)->head = NULL;
    (*queue)->tail = NULL;
    (*queue)->size = 0;

    return;
}

// dodaje element na koniec kolejki
void push(struct FIFO* queue, int num)
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
		new_last->next = NULL;
		new_last->number = num;


		queue->tail->next = new_last;
		queue->tail = new_last;
	}
	queue->size++;
	return;
}



// usuwa pierwszy element
int** pop(struct FIFO* queue, int** output)
{
	if(queue->head != NULL)
	{
		**output = queue->head->number;
		struct Node* new_head = queue->head->next;
		free(queue->head);
		queue->head = new_head;
		queue->size--;	
		if(queue->size == 0)
		{
			queue->tail = NULL;
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
void list(struct FIFO* queue)
{
	if (queue->head != NULL)
	{
		printf ("\ngłowa -<--<- kolejka -<--<- ogon (rozmiar %i)\n", queue->size); 		
		struct Node* elem = queue->head;
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