#ifndef SEMA_H
#define SEMA_H

#include "carro.h"
#include "Puente.h"
#include "params.h"
int isGreen = 0, running = 1;
int started = 0;

pthread_t semaforo;

void cruzarSemaforo(Puente * p, Carro * c, char direccion);
void* runSemaphore(void * argv);
void arrancarSemaforo(Puente * p);
void detenerSemaforo();
void* llegar_a_Semaforo(void * argv);
void dejarSemaforo(Puente * p, Carro * c, char direccion);
int puenteVacio(Puente * p);

int puenteVacio(Puente * p){
	if(p->cant_carros <= 0) return 1;
	else return 0;
}

void* runSemaphore(void * argv){
	Puente * p = (Puente*) argv; 
		pthread_mutex_lock(&p->semaforos[0]);
		while(running){
			pthread_mutex_lock(&p->semaforos[1]);
			pthread_mutex_unlock(&p->semaforos[0]);
			sleep(2);
			pthread_mutex_lock(&p->semaforos[0]);
			pthread_mutex_unlock(&p->semaforos[1]);
			sleep(2);
			p->direccion = !p->direccion;
		}
		pthread_exit(NULL);
}
void arrancarSemaforo(Puente * p){
	started = 1;
	pthread_create(&semaforo,NULL,runSemaphore,(void *)p);
}
void detenerSemaforo(){
		running = 0;
}
void * llegar_a_Semaforo(void * argv){
	
	params * param = (params*) argv;
	Puente * p = param->p;
	Carro * c = param->c;
	char _dir = param->direccion;
	char dir = 0;
	pthread_mutex_lock(&p->semaforos[_dir]);
	while(!puenteVacio(p) && p->direccion != _dir){
			pthread_cond_wait(&p->vacio, &p->semaforos[_dir]);
	}
	p->cant_carros++;
	pthread_mutex_unlock(&p->semaforos[_dir]);
	cruzarSemaforo(p,c,_dir);
	pthread_exit(NULL);
	return NULL;
		
}
void cruzarSemaforo(Puente * p, Carro * c, char direccion){
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
	dejarSemaforo(p,c,direccion);
	
}

void dejarSemaforo(Puente * p, Carro * c, char direccion){
	p->cant_carros--;
	if(p->cant_carros == 0) pthread_cond_broadcast(&p->vacio);
	c->x = 1000;
}
#endif