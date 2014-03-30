#include "params.h"
params * init_parametros(Carro* c, Puente* p, char direccion){
		params * par = (params *) malloc(sizeof(params));
		par->c = c;
		par->p = p;
		par->direccion = direccion;
		return par;
}