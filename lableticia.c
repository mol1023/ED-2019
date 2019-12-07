#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lista.h"
/*
Nicolas Marcondes Molina
RA: 743584
*/
typedef char Item;
struct no {
    struct no *prox;
    struct no *ant;
    Item item;

};
typedef struct no No;

struct lista {
    int (*funcao)( Item i1, Item i2);
    int quantidade;
    No *primeiro;
    No *sentinela;

};
typedef struct lista Lista;

struct iterador {
    No* p;
    Lista* l;
};
typedef struct iterador Iterador;

void inicializa( Lista* l, int (*menor_igual_maior)( Item i1, Item i2));
/*! Inicializa uma lista ordenada. Primeiro procedimento a ser
* chamado para permitir o uso da lista.
*
* \param l Endereco da lista a ser inicializada
* \param m Funcao que compara dois elementos da lista
*
*/
void destroi(Lista* l);
/*! Desaloca uma lista. Ultimo procedimento a ser chamado.
*
* \param l Endereco da lista a ser desalocada
*
*/

int vazia(Lista* l);
/*!
* Verifica se uma lista esta ou nao vazia.
*
* \param d EndereÃƒÂ§o da lista
* \return Verdadeiro (diferente de zero) se a lista estiver vazia
*
*/

void insere(Lista* l, Item item);
/*! Insere um determinado elemento na lista ordenada
*
* \param l Endereco da lista
* \param item Elemento a ser inserido
*
*/

void retira(Lista* l, Item item);
/*! Remove as ocorrencias de um determinado elemento na lista ordenada
*
* \param l Endereco da lista
* \param item Elemento a ser removido
*
*/

Iterador primeiro(Lista* l);
/*!
* Retorna um iterador para o elemento do inicio da lista, se houver.
*
* \param l EndereÃƒÂ§o da lista
* \return Iterador para o menor elemento da lista, se houver
*
*/

Iterador ultimo(Lista* l);
/*!
* Retorna um iterador para o elemento do final da lista, se houver.
*
* \param l EndereÃƒÂ§o da lista
* \return Iterador para o maior elemento da lista, se houver
*
*/
int elementov(Iterador it, Item *i);
Item elemento(Iterador it);
/*!
* Retorna o elemento referenciado pelo iterador, se houver
*
* \param i Iterador
* \return Elemento da lista, se houver
*
*/
int proximo(Iterador* it);
/*!
* Avanca o iterador e retorna verdadeiro caso nao seja o final da lista
*
* \param i Endereco do Iterador
* \return Falso caso nao tenha um proximo elemento
*
*/

int anterior(Iterador* it);
/*!
* Retrocede o iterador e retorna verdadeiro caso nao seja o inicio da lista
*
* \param i Endereco do Iterador
* \return Falso caso nao tenha um elemento anterior
*/

int acabou(Iterador it);

int funcao(Item i1, Item i2);
/*
basicamente o menor_igual_maior
*/

int main()
{
    //Iterador a, b;

    Item item, expressao[7];
    Lista l;

    inicializa (&l, funcao); //INICIANDO LISTA

    while (fscanf(stdin, "%s", expressao) != EOF)
    {
        if (!strcmp(expressao, "imprime")){
            if(vazia(&l)){
                printf("vazia");
            }
            //iremos printar utilizando o iterador
            //assim nao temos que colocar uma funcao que nao pertence a api
            Iterador z;
            z.p = l.sentinela->prox;

            while (z.p != l.sentinela){
              if(z.p->prox == l.sentinela){
                  printf("%c", z.p->item);
                  z.p = z.p->prox;
              }
              else{
                  printf("%c ", z.p->item);
                  z.p = z.p->prox;
              }
            }
            printf("\n");

        }

        else if (!strcmp(expressao, "insere"))
        {
            fscanf(stdin, "%*c%c", &item);
            insere(&l, item);
        }

        else if (!strcmp(expressao, "remove"))
        {
            fscanf(stdin, "%*c%c", &item);
            retira(&l, item);
        }
    }
    destroi(&l);

    return(0);
}

void destroi(Lista *l)
{

    while(l->sentinela->prox != l->sentinela)
    {
        No *extra;
        extra = l->sentinela->prox;
        l->sentinela->prox = l->sentinela->prox->prox;
        free(extra);
    }

    inicializa(l, funcao);

}

void inicializa(Lista* l, int (*menor_igual_maior)( Item i1, Item i2))
{
    l->quantidade = 0;
    No* no = (No*)malloc(sizeof (No));
    l->sentinela = no;

    l->funcao = menor_igual_maior;

    l->sentinela->prox = l->sentinela;
    l->sentinela->ant = l->sentinela;
}

int funcao(Item i1, Item i2)
{
    if(i1 < i2)
        return -1;
    if(i1 == i2)
        return 0;
    if(i1 > i2)
        return 1;
    //return (i1 < i2);
}

void insere(Lista* l, Item item)
{
    No *novo = (No*)malloc(sizeof(No));
    novo->item = item;

    if (vazia(l))
    {
        novo->prox = l->sentinela;
        novo->ant = l->sentinela;
        l->sentinela->prox = novo;
        l->sentinela->ant = novo;
        l->quantidade++;
    }
    else
    {
        Iterador percorre;
        //No *extra;
        percorre.p = l->sentinela->prox;

        while(percorre.p != l->sentinela && ((l->funcao(percorre.p->item, item)) == -1))
            percorre.p = percorre.p->prox;

        if(percorre.p != l->sentinela)
        {
            percorre.p->ant->prox = novo;
            novo->ant = percorre.p->ant;
            novo->prox = percorre.p;
            percorre.p->ant = novo;
        }
        else
        {
            novo->ant = l->sentinela->ant;
            l->sentinela->ant->prox = novo;
            l->sentinela->ant = novo;
            novo->prox = l->sentinela;
        }
        l->quantidade++;
    }
}

void retira(Lista* l, Item item)
{
    Iterador a, b;

    if (vazia(l))
        return;

    a.l = l;
    a.p = a.l->sentinela->prox;

    while((a.p != l->sentinela) && (elemento(a) != item))
        a.p = a.p->prox;

    while(a.p != l->sentinela && elemento(a) <= item)
    {
        l->quantidade--;

        a.p->ant->prox = a.p->prox;
        a.p->prox->ant = a.p->ant;

        b.l = l;
        b.p = l->sentinela->prox;

        while((b.p != b.l->sentinela) && (b.p->item != item))
            b.p = b.p->prox;

        free(a.p);
        a = b;

    }

}

int vazia(Lista *l)
{
    if (l->quantidade == 0)
        return (1);
    else
        return (0);
}

Item elemento(Iterador it)
{
        return(it.p->item);
}

Iterador primeiro(Lista *l)
{
    Iterador a;
    a.p = l->sentinela->prox;
    a.l = l;
    return (a);
}

Iterador ultimo(Lista *l)
{
    Iterador b;
    b.p = l->sentinela->ant;
    b.l = l;
    return (b);
}

int proximo(Iterador *it)
{
    int extra;
    if(it->p->prox != it->l->sentinela)
    {
        it->p = it->p->prox;
        extra = 1;
    }
    else
        extra = 0;

    return (extra);
}

int anterior(Iterador *it)
{
    int extra;
    if(it->p->ant != it->l->sentinela)
    {
        it->p = it->p->ant;
        extra = 1;
    }
    else
        extra = 0;

    return (extra);
}

int acabou(Iterador it)
{
    if (it.p == it.l) //se apontar para nada
        return 1;

    return 0;
}
