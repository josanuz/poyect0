#ifndef PUENTE_H
#define PUENTE_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datos.h"

struct Puente{
	unsigned long distancia;
	short direccion;
	pthread_mutex_t semaforos[2];
	pthread_mutex_t * paso;
	pthread_cond_t vacio;
	pthread_cond_t cont_dir;
	unsigned long cant_carros;
	
};
typedef struct Puente Puente;
typedef Puente * ptrpuente;

ptrpuente puente_init(long _distancia);

#endif