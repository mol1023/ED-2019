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

typedef no No;
//insere sempre no topo
void empilhar(No** p, T valor){
	No* novo = (No*)malloc(sizeof(No));
		novo->valor = valor;
		novo->prox = *p;
		*p = novo;
}
/*desempilha retornando o topo ja
para nao ter que acessar mais de uma vez na main
reduzindo a complexidade do algoritmo*/
int desempilhar(No** p){
	No* aux;
    int x;
	if(*p == NULL) return 0;
	else{
        x = (*p)->valor;
		aux = *p;
		*p = (*p)->prox;
		free(aux);
	}
    return x;
}

void imprimir(No* p){
	No* percorre;
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
int vazia(No** p){
    if((*p) == NULL)
        return 1;
    else
        return 0;
}
//da free em todos elementos da pilha
void esvaziarpilha(No **p){
	No* aux;
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
void inicpilha(No** p){
    *p = NULL;
}

int Prioridade(char c, char t){
    int pc,pt;

    if(c == '^')
        pc = 4;
    else if(c == '*' || c == '/')
        pc = 2;
    else if(c == '+' || c == '-')
        pc = 1;
    else if(c == '(')
        pc = 4;
    
    if(t == '^')
        pt = 3;
    else if(t == '*' || t == '/')
        pt = 2;
    else if(t == '+' || t == '-')
        pt = 1;
    else if(t == '(')
        pt = 0;
    
    return (pc > pt);
}

void in2pos(char expr[]){
    No* p;
    int i = 0;
    char c,t;
    inicpilha(&p);
    empilhar(&p, '(');

    do{
        c = expr[i];
        i++;
        if(c >= 'a' && c <= 'z'){
            printf("%c", c);
        }
        else if(c == '('){
            empilhar(&p, '(');
        }
        else if(c == ')' || c == '\0'){
            do{
                t = desempilhar(&p);
                if(t != '(')
                printf("%c", t);
            }while(t != '(');
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){
            while(1){
                t = desempilhar(&p);
                if(Prioridade(c,t)){
                    empilhar(&p, t);
                    empilhar(&p, c);
                    break;
                }
                else{
                    printf("%c", t);
                }
            }
        }
    }while(c != '\0');
    printf("\n");
    esvaziarpilha(&p);
}

//
//
int main(){


	No* p;
	char regi[10];
    char a[10];
    char b[10] = "insere";
    char e[10] = "insereB";
    char c[10] = "imprime";
    char h[10] = "imprimeB";
    char d[10] = "remove";
    char f[10] = "binario";
    char k[10] = "intercala";
    
    char expr[] = "a-b";
    in2pos(expr);

    return 0;

}
