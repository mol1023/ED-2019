/*
    Nicolas Marcondes Molina
    RA:743584
*/
#include <stdio.h>
#include <stdlib.h>
//
typedef int T;
typedef struct filaElem{
    T data;
    struct filaElem*next;
}filaELEM;
typedef struct q{
    struct filaElem*begin;
    struct filaElem*end;
}fila;
/*
inicializei de forma que na hora da declaracao da fila
ja consigo igualar pra ela ja ser inicializada na main
*/
fila*inicfila(){
    fila*q = (fila*)malloc(sizeof(fila));
    if(!q)
        exit(1);
    else{
     q->begin = NULL;
     q->end = NULL;
    }
    return q;
}
/*
pouco diferente da pilha vazia, como dessa vez tem
se outro struc apenas para o inicio e para o fim fica mais facil de verificar
*/
int filavazia(fila*q){
    if(q==NULL) return 1;
    if(q->begin==NULL) return 1;
    else return 0;
}
/*
precisamos desse tipo pq iremos retornar ela na funcao de inserir
e ficar menor a inserir facilitando
*/
filaELEM* alocar(T valor){
    filaELEM* no = (filaELEM*)malloc(sizeof(filaELEM));
    if(!no)
        exit(1);
    else{
        no->data = valor;
        no->next = NULL;
        return no;
    }
}
/*
como alocar eh do tipo filaELEM* que eh o nosso no
podemos igualar na declaracao ja pq ele vai retornar um tipo
filaELEM*
*/
void inserir(fila*q, T valor){
    filaELEM*no = alocar(valor);
    if(!no)
        exit(1);
    if(q->end == NULL)
        q->begin = no;
    else
        q->end->next = no;
    q->end = no;
}
/*
no remover tambem inclui o int a para facilitar na hora de inverter
visto que precisamos do valor do item removido para se fazer a pilha de
recursao funcionar e inverter os valores, sendo muito mais simples que o swap
*/
int remover(fila*q){
    int a;
    if(filavazia(q)) return 0;

    a = q->begin->data;
    filaELEM*no = q->begin;
    q->begin = q->begin->next;
    if(q->begin==NULL)
        q->end = NULL;
    free(no);
    return a;
}
/*
para imprimir criei um no auxiliar para percorrer a fila e printar
assim nao se tem a possibilidade de perder referencia
*/
void imprimir(fila*q){
    if(filavazia(q)){
        printf("fila vazia\n");
    }
    filaELEM*aux = q->begin;
    while(aux!=NULL){
        if(aux->next == NULL){
            printf("%i", aux->data);
            aux = aux->next;
        }
        else{
            printf ("%i ", aux->data);
            aux = aux->next;
        }
    }
    printf ("\n");
}
/*
na inverte, os elementos removidos ficam guardados na pilha de execucao,
de modo que na volta utilizamos chamamos inverte para assim inserir os elementos que
foram removidos, assim a fila fica invertida
*/
void inverte(fila*q){
    if(filavazia(q)) return;
    int x = remover(q);
    inverte(q);
    inserir(q, x);
}

void esvaziarfila(fila*q){
	filaELEM*aux = q->begin;
	if(filavazia(q)) return;
	else{
	while(!filavazia(q)){
            remover(q);
		}
	}
}

int main (void){
    fila*q = inicfila();
    int entradas, i;
    T numeros;

    scanf("%d", &entradas);
    for(i = 0; i < entradas; i++){
        scanf("%d", &numeros);
        inserir(q, numeros);
    }

    //while(f->prox!=NULL)
    //imprimir(f);
    inverte(q);
    imprimir(q);
    esvaziarfila(q);
    //imprimir(q);
    return 0;
}
