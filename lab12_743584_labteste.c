/*
Nicolas Marcondes Molina
RA: 743584
*/

#include <stdio.h>
#include <stdlib.h>
//utilizei **, sem 2 structs, entao o topo permanece salvo em (*p)->valor
typedef char T;
typedef struct no{
	T valor;
	struct no* prox;
}no;

typedef no pilha;
//insere sempre no topo
void empilhar(pilha** p, T valor){
	pilha* novo = (pilha*)malloc(sizeof(pilha));
		novo->valor = valor;
		novo->prox = *p;
		*p = novo;
}
/*desempilha retornando o topo ja
para nao ter que acessar mais de uma vez na main
reduzindo a complexidade do algoritmo*/
void desempilhar(pilha** p, T *valor){
	pilha* aux;
	if(*p == NULL) return ;

	else{
		*valor = (*p)->valor;
		aux = *p;
		*p = (*p)->prox;
		free(aux);
	}
}

void imprimir(pilha* p){
	pilha* percorre;
	percorre = p;
	if(p == NULL) printf("pilha vazia\n");
	else{
		while(percorre != NULL){
			printf("%c", percorre->valor);
			percorre = percorre -> prox;
		}
		printf("\n");
	}
}
//verifica se esta vazia atraves do topo
int vazia(pilha** p){
    if((*p) == NULL)
        return 1;
    else
        return 0;
}
//da free em todos elementos da pilha
void esvaziarpilha(pilha **p){
	pilha* aux;
	if(*p == NULL) return;
	else{
	aux = *p;
	while(*p != NULL){
		aux = *p;
		*p = (*p)->prox;
		free(aux);
		}
	}
}

//como estou usando **, o topo eh *p
void inicpilha(pilha** p){
    *p = NULL;
}
//
//
int main(){


	pilha* p;
    inicpilha(&p);
	int entradas, flag, i, j, a;
	T c[100000];
	scanf("%d", &entradas);
	for(i = 0; i < entradas; i++){
		scanf("%s", c);
		flag = 1;
		for(j = 0; c[j]!='\0'; j++){
			/*se tivermos na entrada uma aberta empilhamos
			afinal depois iremos verificar se caso entrar uma ) qual o topo da pilha
			sem ter que empilhar as fechadas. Pegamos o topo e comparamos, se o topo n combinar com a fechada
			atual setamos a flag pra 0 para dizer que nao eh balanceada
			*/
			if((c[j]=='(')||(c[j]=='{')||(c[j]=='['))
				empilhar(&p, c[j]);
			else{
				if(vazia(&p)){
					//se estiver vazia e o primeiro inserido for }
					flag = 0;
					goto label;
				}
				char ctop;
				//top(&p, &ctop);//pega o top
				desempilhar(&p, &ctop);
				if((c[j]==')' && ctop!='(')||(c[j]==']' && ctop!='[')||(c[j]=='}' && ctop!='{'))
				{
					flag = 0;
					goto label;
				}
			}
		}
		label:
		//imprimir(p);
		if(!vazia(&p)){
			flag = 0;
			esvaziarpilha(&p);
			//while(vazia(&p)) desempilhar(&p);
		}
		if(flag){
            printf("S\n");
			esvaziarpilha(&p);
		}
        else{
            printf("N\n");
			esvaziarpilha(&p);
		}
		//imprimir(p);
	}
    return 0;
}
//perguntar do esvaziar pq ele da () N () S {sem ele so da certo na segunda pra frente com ele n da certo em nenhuma pq sempre da n}
