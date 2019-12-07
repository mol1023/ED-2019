/*
Nicolas Marcondes Molina
RA: 743584
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>


typedef struct auxElem {
  char reg;
  struct auxElem* ant;
  struct auxElem* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT cabeca;
  int qtd;
} lista;
/*
na inicializacao apenas alocamos o espaco para o no cabeca e
setamos os campos dele, alem disso verificamos se o no cabeca
foi alocado com sucesso
*/
void cria_Lista(lista* dq){
    dq->cabeca = (PONT)malloc(sizeof(ELEMENTO));
    if(dq->cabeca != NULL){
        dq->cabeca->prox = dq->cabeca;
        dq->cabeca->ant = dq->cabeca;
        dq->qtd = 0;
    }
}

/*
em imprimir verificamos se esta vazia e percorremos ela printando se nao estiver
o if dentro do while eh para cobrir o caso de nao dar espaco no ultimo registro
*/

void imprimir(lista* d){
  PONT end = d->cabeca->prox;
  if(end == d->cabeca){
      printf("vazia");
  }
  while (end != d->cabeca){
    if(end->prox == d->cabeca){
        printf("%c", end->reg);
        end = end->prox;
    }
    else{
        printf("%c ", end->reg);
        end = end->prox;
    }
  }
  printf("\n");
}

/*
no remover primeiro vemos se a lista esta vazia, caso nao esteja
iremos precisar de dois ponteiros para realizar o free, um percorrendo e outro aux
onde realmente iremos dar free, de modo que o de percorrer(apagar) eh utilizado para
alterar os ponteiros e iteramos ele, fazendo com que possamos dar free sem
perder a referencia.
os outros 2 ifs sao para cobrir o caso de ser o ultimo, visto que nao entraria no while(apagar->prox!=d->cabeca)
e o ultimo eh para caso tenha percorrido a lista inteira e nao tenha achado os elementos que
seriam removidos
*/

void remover(lista* d,char reg){
  if (d->cabeca->prox == d->cabeca) return ;

  PONT apagar = d->cabeca->prox;

  while((apagar->prox != d->cabeca) && (apagar->reg <= reg )){
      PONT aux = apagar;
      if(apagar->reg == reg){
        apagar->ant->prox = apagar->prox;
        apagar->prox->ant = apagar->ant;
        apagar = apagar->prox;
        d->qtd--;
        free(aux);
      }
      else
        apagar = apagar->prox;
  }

  if((apagar->reg == reg) && (apagar->prox == d->cabeca)){
    PONT aux = apagar;
    d->cabeca->ant = apagar->ant;
    apagar->ant->prox = d->cabeca;
    free(aux);
    d->qtd--;
    return;
  }
  if(apagar->reg!=reg)
      return ;

  d->qtd--;
  return ;
}

/*
swap utilizado para realizar o bubbesort
*/

void swap(char *xp, char *yp)
{
   char temp = *xp;
   *xp = *yp;
   *yp = temp;
}

/*
bubblesort utilizado para ordenar a lista, apenas alteramos onde os registros estao.
usamos o fato de termos a qtd de nos armazenada no no cabeca para conseguir percorrer
fazendo os swaps.
*/

void bubbleSort(lista* d)
{
  int i, j;
  PONT aux = d->cabeca->prox;
  for (i = 0; i < d->qtd; i++){
      aux = d->cabeca->prox;
      for (j = i+1; j < (d->qtd); j++){
          if (aux->reg > aux->prox->reg)
             swap(&aux->reg, &aux->prox->reg);
          aux = aux->prox;
         }
  }
}

/*
insere normal e geral visto que estamos tratando de uma lista circular
alem disso apenas alteramos a qtd que esta armazenada no no cabeca
*/

void insere(lista* d,char reg) {
  PONT i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->ant = d->cabeca;
  i->prox = d->cabeca->prox;
  d->cabeca->prox = i;
  i->prox->ant = i;
  d->qtd++;
  bubbleSort(d);
}

/*
libera, funcao onde percorremos a lista inteira dando free nos nos, e apos
isso setamos o no cabeca como estava no inicializar
*/

void libera(lista* d) {
  PONT end = d->cabeca->prox;
  while (end != d->cabeca){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  d->cabeca->prox = d->cabeca;
  d->cabeca->ant = d->cabeca;
}

int main(){
    char regi;
    lista dq;
    cria_Lista(&dq);
    char a[10];
    char b[10] = "insere";
    char c[10] = "imprime";
    char d[10] = "remove";

/*
scanf ate o usuario parar de digitar, end of file
*/

    while(scanf("%s", a)!=EOF) {
        getchar();
        if((strcmp(a, b))==0){
            scanf("%c", &regi);
            insere(&dq, regi);
        }
        if((strcmp(a, d))==0){
            scanf("%c", &regi);
            remover(&dq, regi);
        }
        if((strcmp(a, c))==0){
            imprimir(&dq);
        }
    }
    libera(&dq);
    return 0;
}
