#ifndef PARAMS_H
#define PARAMS_H

#include "carro.h"
#include "Puente.h"

struct params{
	Carro * c;
	Puente * p;
	char direccion;
};
typedef struct params params;
params * init_parametros(Carro* c, Puente* p, char direccion);

#endif 
