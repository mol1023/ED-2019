#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
// Nicolas Marcondes Molina
// RA: 743584

typedef int T;

//tanto para inserir e para realizar a recursao precisamos de inicio e fim principalmente na struct
//alem do padrao do vetor v;
typedef struct{
	int inicio;
	int tam;
	int fim;
	T *v;
}fila;

//inicializa fila, alocando dinamicamente de acordo com o tamanho inserido (n)
void inicializaFila(fila *f, int n){
	f->inicio=0;
	f->tam=0;
	f->fim=0;
	f->v = (T*)malloc(n*sizeof(T));
}

//insercao na fila, onde ao inves de se ter uma funcao para verificar se esta cheia, vemos pelo tamanho(f->tam)
int inserirElementoFila(fila *f, T reg, int n){
	if(f->tam >= n) return 0;
	f->fim++;
	f->tam++;
	f->v[f->fim-1]=reg;
	return 1;
}

//remove e deixa salvo num registro caso quera printar o removido
/*int removerElementoFila(fila *f, T *reg){
	if(f->tam==0) return 0;
	*reg = f->v[f->inicio];
	f->inicio++;
	f->tam--;
	return 1;
} sem necessidade de remover elementos nesse problema*/

//inverte a fila baseada na recursao onde o caso base eh quando inicio=fim
//usamos um auxiliar para fazer a troca de elementos e logo apos chamamos a recursao
//a recursao vai incrementando no inicio e decrementando no fim para que elementos na posicao por exemplo 0 e 4 possam ser trocados
//e assim por diante com 1 e 3 ate chegar no meio
//tambem temos um if para caso a lista esteja vazia
int inverte(fila *f, int inicio, int fim){
	if(f->tam==0) return 0;
	else{
		if(inicio<fim){
			int aux = f->v[fim];
			f->v[fim] = f->v[inicio];
			f->v[inicio] = aux;
			inverte(f,inicio+1,fim-1);
		}
		else return 0;
	}
}

//warning perguntar ->Lab11.c:61:1: warning: control reaches end of non-void function [-Wreturn-type]
int main(){
	int n, i;
	fila f;
	T registro;

	scanf("%d", &n);
	inicializaFila(&f, n);

	for(i = 0; i<n; i++){
		scanf("%d", &registro);
		inserirElementoFila(&f, registro, n);
	}

	inverte(&f, f.inicio, f.fim-1);
	for(i = 0; i<n; i++){
		if(i + 1 == n) goto label;
		printf("%d ", f.v[i]);
	}
	label:
	printf("%d\n", f.v[i]);
	return 0;
}
