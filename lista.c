#include "lista.h"

List* init_list(){
		List * l = (List*)malloc(sizeof(List));
		l->head = NULL;
		l->tail = NULL;
		l->size = 0;
}
Carro * deleteCar(int id, List * l){
		Carro * ret = NULL;
		nodo * tx = l->head;
		if(l->size < 1) return NULL;
		if(l->size == 1 && l->head->dato->id == id){
				ret = l->head->dato;
				free(l->head);
				l->head = NULL; l->tail = NULL;
				l->size--;
				return ret;
		}
		if(l->head->dato->id == id){
			nodo * t= l->head;
			l->head = l->head->next;
			ret = t->dato;
			free(t);
			l->size--;
			return ret;
		}
		while(tx->next != NULL && l->size > 0){
				if(tx->next->dato->id == id){
					nodo * t = tx->next;
					if(t == l->tail){
						l->tail = tx;
						ret = tx->next->dato;
						free(tx->next);
						tx->next = NULL;
						l->size--;
						return ret;
					}
					tx->next = t->next;
					ret = t->dato;
					free(t);
					l->size--;
					return ret;
				}
				tx = (tx->next);
		}
		return NULL;
}
void insertCar(Carro * c, List* l){
	nodo * n = (nodo *)malloc(sizeof(nodo));
	n->dato = c;
	n->next = NULL;
	if(l->size < 1){
		
		l->head = l->tail = n;
		l->head->next = l->tail;
		l->size++;
		return;
	}
	l->tail->next = NULL;
	l->tail->next = n;
	l->tail = n;
	l->size++; 
}
void autoClean(List* l){
		if(l->size == 0) return;
		nodo * n;
		n = l->head->next;
		while(n != NULL && (n->next != NULL && n->next != l->tail)){
				if(n->next->dato->x == 0 && n->next->dato->y == 0)
				{
							nodo * tmp;
							tmp = n->next;
							n->next = tmp->next;
							l->size--;
							free(tmp);
				}
		}
		if(l->size > 0 && (l->head->dato->x == 0 && l->head->dato->y == 0)) deleteCar(l->head->dato->id,l);
		if(l->size > 0 && (l->tail->dato->x == 0 && l->tail->dato->y == 0)) deleteCar(l->tail->dato->id,l);
}