#include <stdio.h>
#include <stdlib.h>
#include "Puente.h"
#include "carro.h"
#include "params.h"
#include "lista.h"
#include "semaforos.h"
#include "oficial.h"
#include <time.h>
short toExit = 1;
Puente * puente; 
Carro ** carros;
List * l = init_list();
pthread_t printer;

void * printCars(void * argc){
	int i = 0, x, dis;
	dis = *((int *)argc);
	while(toExit){
		printf("\033[5;0H",i);
		for(i = 0;i < dis; i++){
			printf("=");
		}
		printf("\033[5;0H");
		//autoClean(l);
		nodo * tmp = l->head;
		while(tmp != NULL){
			x = tmp->dato->x;
			printf("\033[5;%dH",x+1);
			printf("@");
			//else printf(">");
			tmp = tmp->next;
		}
		//usleep(1000);
		printf("\033[7;0H   ");
		printf("\033[7;0H %d",puente->cant_carros);
	}
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	int i;
	printf("Iniciar\n");
	puente = puente_init(atoi(argv[1]));
	int MAX = atoi(argv[2]);
	
	carros = (Carro**) malloc( MAX * sizeof(Carro*) );
	for(i = 0; i< MAX ; i++) carros[i] = carro_init(1);
	pthread_create(&printer,NULL,printCars,&puente->distancia);
	
	printf("Arrancara en 2..");
	sleep(2);
	/*for(i = 0; i< MAX ; i++){ // Normal Pasa Cuando Puede
		params * arg;
		srand(time(0) + getpid() + rand()*(rand()%10));
		arg = init_parametros(carros[i],puente,i % 2 ? IZQUIERDA : DERECHA);
		insertCar(carros[i],l);
		usleep(1 + rand()%1000);
		pthread_create(carros[i]->thread,NULL,ingresar,(void*)arg);
	}
	for(i = 0; i< MAX ; i++) pthread_join(*carros[i]->thread, NULL);*/
	arrancarOficial(puente, 2);
	for(i = 0; i < MAX ; i++){
		params * arg;
		srand(time(0) + getpid() + rand()*(rand()%10));
		arg = init_parametros(carros[i],puente,i % 4 ? IZQUIERDA : DERECHA);
		insertCar(carros[i],l);
		//sleep(1 + rand()%2);
		sleep(1);
		pthread_create(carros[i]->thread,NULL,ingresarOficial,(void*)arg);
	}
	for(i = 0; i< MAX ; i++) pthread_join(*carros[i]->thread, NULL);
	detenerOficial();
	toExit = 0;
}
