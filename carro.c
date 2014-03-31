#include "carro.h"
#include "params.h"
static int enelpuente = 0;
Carro * carro_init(unsigned int _v){
		Carro * c = (Carro*) malloc(sizeof(Carro));
		c->id= _id++;
		c->velocidad = _v;
		c->x = c->y = 100;
		c->thread = (pthread_t*) malloc(sizeof(pthread_t));
		return c;
}
void * ingresar(void * argv){
	
	params * parametros = (params *) argv;
	
	char direccion = parametros->direccion;
	Puente * p = parametros->p;
	Carro * c = parametros->c;
	//printf("%c",direccion);
	
	pthread_mutex_lock(&p->semaforos[0]);
	while(p->direccion != direccion){
		pthread_cond_wait(&p->cont_dir,&p->semaforos[0]);
	}
  
	if(p->cant_carros == 0)
		p->direccion = direccion;
	p->cant_carros++;
	pthread_mutex_unlock(&p->semaforos[0]);
	
	cruzar(p , c, direccion);
	pthread_exit(NULL);
	return NULL;
}
void cruzar(Puente * p, Carro * c, char direccion){
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
	dejar(p,c,direccion);
	
}

void dejar(Puente * p, Carro * c, char direccion){
		pthread_mutex_lock(&p->semaforos[0]);
		p->cant_carros--;
		sleep(c->velocidad);
		c->x = c->y = 1000;
		pthread_mutex_unlock(&p->semaforos[0]);
		if(p->cant_carros == 0)  {
			p->direccion = !p->direccion;
			pthread_cond_broadcast(&p->cont_dir);
		}
}
