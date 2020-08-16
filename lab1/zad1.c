#include <stdio.h>
#include <stdlib.h>

struct Node 
{ 
	struct Node* next;
	int number;
}; 


struct Node* head; 


void push(int num);
void pop();
void list();
int count ();
struct Node* last();



int main() 
{
	push(27);	//dodaj element
	push(-4);
	push(29);
	list();		//drukuj
	pop();		//usun
	list();
	push(24);
	list();
	printf("\nLiczba elementow - %d\n", count());
	pop();
	pop();
	pop();
	list();
	return 0; 
}

// dodaje element na koncu kolejki
void push(int num)
{
	if (head == NULL)
	{
		head =(struct Node* )malloc(sizeof(struct Node));
		head->next = NULL;
		head->number = num;
	}
	else
	{
		struct Node* next_node = (struct Node*)malloc(sizeof(struct Node));
		struct Node* last_elem = last();
		last_elem->next = next_node;
		next_node->next = NULL;
		next_node->number = num;
	}
	return;
}

// usuwa pierwszy element
void pop()
{
	if(head != NULL)
	{
		struct Node* new_head = head->next;
		free(head);
		head = new_head;	
	}
	else
	{
		printf("\nLista jest pusta!\n");
	}
	return;
}

// drukuje wszystkie elementy po kolei
void list()
{
	if (head != NULL)
	{
		printf ("\n<---- kolejka <----\n"); 		
		struct Node* elem = head;
		printf ("%d ",elem->number); 
		while(elem->next != NULL)
		{
			elem=elem->next;	
			printf ("%d ",elem->number); 
		}
	}
	else
	{
		printf("\nLista jest pusta!\n");
	}
	return;
}

// zwraca liczbe elementow
int count()
{
	int counter = 0;
	if (head != NULL)
	{
		counter = 1;
		struct Node* elem = head;
		while (elem->next != NULL)
		{
			counter++;
			elem=elem->next;
		}
	}
	return counter;
}

//zwraca ostatni element
struct Node* last()
{
	struct Node* elem = head;
	while(elem->next != NULL)
	{
		elem=elem->next;
	}
	return elem;
}

