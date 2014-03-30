#include "Puente.h"
ptrpuente puente_init(long _distancia){
	int i = 0;
	ptrpuente p = (ptrpuente) malloc(sizeof(Puente));
	p->distancia = _distancia;
	p->direccion = IZQUIERDA;
	pthread_mutex_init (&p->semaforos[IZQUIERDA] , NULL);
	pthread_mutex_init (&p->semaforos[IZQUIERDA] , NULL);
	p->paso = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*p->distancia);
	for(i = 0; i < p->distancia ; i++)
		pthread_mutex_init(&p->paso[i], NULL);
	pthread_cond_init(&p->vacio, NULL);
	pthread_cond_init(&p->cont_dir,NULL);
	p->cant_carros = 0;
	return p;
}