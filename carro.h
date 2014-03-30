#ifndef CARRO_H
#define CARRO_H

#include "Puente.h"

static unsigned long _id = 0;
struct Carro{
	unsigned long id;
	unsigned int velocidad;
	int x, y;
	pthread_t * thread;
};
typedef struct Carro Carro;

Carro * carro_init(unsigned int _v);
void * ingresar(void *);
void cruzar(Puente * p, Carro * c, char direccion);
void dejar(Puente * p, Carro * c, char direccion);

//#include "params.h"
#endif