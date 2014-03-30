#ifndef COLA_H
#define COLA_H

#define MAX 256
#include "carro.h"
#include "Puente.h"

struct Cola{
	Carro * cola[MAX];
	int head;
	int tail;	
	long size;
};

typedef struct Cola Cola;

Carro * descolar(Cola * c){
	if(c->head == c->tail) return NULL;
	c->size--;
	return c->cola[c->head++%MAX];
}
void encolar(Cola * col,Carro * c){
	col->cola[col->tail++] = c;
	col->tail %= MAX;
}
long size(Cola * c){
	return c->size %512;
}
#endif
