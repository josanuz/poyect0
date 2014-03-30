#ifndef LISTA_H
#define LISTA_H
#include "carro.h"

struct node{
		Carro * dato;
		struct node * next;
};
struct Lista{
	struct node * head;
	struct node * tail;
	size_t size;
}; 

typedef struct node nodo;
typedef struct Lista List;

List* init_list();
Carro* deleteCar(int id, List * l);
void insertCar(Carro * c, List*l);
void autoClean(List* l);

#endif