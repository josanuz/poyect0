#include <stdio.h>
#include <stdlib.h>
#include "Puente.h"
#include "carro.h"
#include "params.h"
#include "lista.h"
short toExit = 1;
Puente * puente; 
Carro * carros[8];
List * l = init_list();
pthread_t printer;

void * printCars(void *){
	int i = 0, x;
	while(toExit){
		printf("\033[5;0H",i);
		for(i = 0;i < 10; i++){
			printf("=");
		}
		printf("\033[5;0H");
		//autoClean(l);
		nodo * tmp = l->head;
		while(tmp != NULL){
			x = tmp->dato->x;
			printf("\033[5;%dH",x+1);
			printf("%d",tmp->dato->id);
			tmp = tmp->next;
		}
		usleep(1000);
		printf("\033[7;0H %d",puente->cant_carros);
	}
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	int i;
	printf("Iniciar\n");
	puente = puente_init(atoi(argv[1]));
	//Carro * carros = (Carro*) malloc(4*sizeof(Carro));
	for(i = 0; i< 8 ; i++) carros[i] = carro_init(2);
	
	pthread_create(&printer,NULL,printCars,NULL);
	printf("Arrancara en 2..");
	sleep(2);
	for(i = 0; i< 8 ; i++){
		params * arg;
		arg = init_parametros(carros[i],puente,i < 4 ? IZQUIERDA : DERECHA);
		if(carros[i]->thread) ;
		insertCar(carros[i],l);
		pthread_create(carros[i]->thread,NULL,ingresar,(void*)arg);
	}
	for(i = 0; i< 8 ; i++) pthread_join(*carros[i]->thread, NULL);
	toExit = 0;
}
