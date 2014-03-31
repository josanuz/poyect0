#include "carro.h"
#include "Puente.h"
#include "params.h"

pthread_t oficial;
unsigned int cantMaxCars = 0;
int r_ofi = 1;
int waiting[] = {0 , 0};
int advance = 0;

void cruzarOficial(Puente *p, Carro* c, char dir);
void * administrar(void * argv);
void arrancarOficial(Puente * p, int Ccar);
void detenerOficial();
void * ingresarOficial(void * argv);
void dejarOficial(Puente * p, Carro * c, char direccion);
void setMaxCantCarsOficial(unsigned int cant);

void * administrar(void * argv){ 
	Puente * p = (Puente*) argv;
	while(r_ofi){

	}	
}
void setMaxCantCarsOficial(unsigned int cant){
		cantMaxCars = cant;
}
void arrancarOficial(Puente * p, int Ccar){
	cantMaxCars = Ccar;
	pthread_create(&oficial,NULL, administrar,(void*)p);
	
}
void detenerOficial(){
		r_ofi = 0;
}

void * ingresarOficial(void * argv){
	params * p = (params*) argv;
	Puente * puente = p->p; Carro * c = p->c; char dir = p->direccion;
	waiting[dir]++;
	pthread_mutex_lock(&puente->semaforos[0]);
	usleep(100);
	while((puente->cant_carros > cantMaxCars && puente->cant_carros > 0) || puente->direccion != dir){
		pthread_cond_wait(&puente->vacio, &puente->semaforos[0]);
	}
	puente->cant_carros++;
	waiting[dir]--;
	if(puente->cant_carros == 0) puente->direccion = dir;
	pthread_mutex_unlock(&puente->semaforos[0]);
	cruzarOficial(puente,c,dir);
	pthread_exit(NULL);
}
void cruzarOficial(Puente * p, Carro * c, char direccion){
	int i;
	if(direccion == IZQUIERDA){
		 	
		for(i=0 ; i < p->distancia; i++){
			pthread_mutex_lock(&p->paso[i]);
			c->x = i; c->y = 0;
			sleep(c->velocidad);
			pthread_mutex_unlock(&p->paso[i]);
		}
	}
	else
	{
		for(i = p->distancia -1 ; i >= 0; i--){
			pthread_mutex_lock(&p->paso[i]);
			c->x = i; c->y = 0;
			sleep(c->velocidad);
			pthread_mutex_unlock(&p->paso[i]);
		}
	}
	dejarOficial(p,c,direccion);
	
}

void dejarOficial(Puente * p, Carro * c, char direccion){
		pthread_mutex_lock(&p->semaforos[0]);
		p->cant_carros--;
		sleep(c->velocidad);
		c->x = c->y = 1000;
		if(p->cant_carros == 0)  {
			if(waiting[!direccion] > 0)p->direccion = !p->direccion;
			pthread_cond_broadcast(&p->vacio);
		}
		pthread_mutex_unlock(&p->semaforos[0]);

}