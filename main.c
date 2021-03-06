#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Puente.h"
#include "carro.h"
#include "params.h"
#include "lista.h"
#include "semaforos.h"
#include "oficial.h"

short toExit = 1;
Puente * puente; 
Carro ** carros;
List * l;
pthread_t printer;
int MAX;
long longpuente;
int distribucion,velauto,duracion,cantoficial,cantmaxcars;


void leer(char * path){
FILE *file;
file=fopen(path,"r");
if(file){
	fscanf(file,"%ld %d %d %d %d %d",&longpuente,&distribucion,&velauto,&duracion,&cantoficial,&cantmaxcars);
	printf("%ld %d %d %d %d %d",longpuente,distribucion,velauto,duracion,cantoficial,cantmaxcars);
	sleep(5);
	}
}
double distri(int m){
	srand(time(NULL ));
	double r = (double) rand() / RAND_MAX + 1;
	return (-m) * log(r);
}

void * printCars(void * argc){
	l = init_list();
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
		printf("\033[7;0H %ld",puente->cant_carros);
	}
	pthread_exit(NULL);
}

void FIFO(){
	int i;
for(i = 0; i< MAX ; i++){ // Normal Pasa Cuando Puede
		params * arg;
		srand(time(0) + getpid() + rand()*(rand()%10));
		arg = init_parametros(carros[i],puente,i % 2 ? IZQUIERDA : DERECHA);
		insertCar(carros[i],l);
		usleep(1 + rand()%1000);
		pthread_create(carros[i]->thread,NULL,ingresar,(void*)arg);
	}
	for(i = 0; i< MAX ; i++) 
	pthread_join(*carros[i]->thread, NULL);
	
}

void OficialTransito(){
	
	int i;
	arrancarOficial(puente, 1);//Poner en un metodo oficial
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

int main(int argc, char **argv){
	int i,opciones,bandera=1;
	leer(argv[1]);
	
	
		
	while(bandera){	
	system("/usr/bin/clear");
	printf("\t\t---------------------------------------\n");
	printf("\t\t**************Puente*******************\n");
	printf("\t\tEscoja la opcion que desea realizar\n");
	printf("\t\t-----------------------------------\n");
	printf("\t\t1.FIFO\n");
	printf("\t\t2.Semaforos\n");
	printf("\t\t3.Oficial de Transito\n");
	printf("\t\t4.Finalizar\n");
	printf("----->");
	scanf("%d",&opciones);
	printf("%d",opciones);
	system("/usr/bin/clear");
	
		
	switch(opciones){
		
	case 1:
	puente = puente_init(longpuente);
	MAX = cantmaxcars;
	
	carros = (Carro**) malloc( MAX * sizeof(Carro*) );
	
	for(i = 0; i< MAX ; i++) carros[i] = carro_init(1);
	pthread_create(&printer,NULL,printCars,&puente->distancia);
	
	printf("Arrancara en 2..");
	sleep(2);
	FIFO();
	break;
	case 2:
	
	break;
	
	case 3:
	puente = puente_init(longpuente);
	MAX = cantmaxcars;
	
	carros = (Carro**) malloc( MAX * sizeof(Carro*) );
	
	for(i = 0; i< MAX ; i++) carros[i] = carro_init(1);
	pthread_create(&printer,NULL,printCars,&puente->distancia);
	printf("Arrancara en 2..");
	sleep(2);
	OficialTransito();
	break;
	case 4:
	bandera=0;
	break;
	default:
	printf("Opcion Invalida\n");
	printf("Porfavor Inserte una Opcion del 1 al 4\n");
	break;	
		}
	}
	
	
	
	
}




