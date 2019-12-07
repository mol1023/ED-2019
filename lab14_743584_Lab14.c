/*
Nicolas Marcondes Molina
RA: 743584
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

typedef int T;
struct elemento{
    struct elemento *ant;
    T dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/*
criamos um no cabeca onde guardaremos
a qtd e teremos um ponteiro para o inicio e para o final
visando facilitar a insercao e remocao
*/

typedef struct Deque{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
}Deque;

/*
inicializamos o no cabeca, setando o ponteiro do fim
o ponteiro do inicio e a qtd de elementos
*/

Deque*cria_Deque(){
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    if(dq != NULL){
        dq->final = NULL;
        dq->inicio = NULL;
        dq->qtd = 0;
    }
    return dq;
}

/*
funcao para dar free em todos os elementos do deque
considerando 2 casos, quando o deque tem apenas um elemento
ou quando o deque tem mais de um elemento

para percorrer vemos se o ponteiro para inicio eh nulo ou nao
e iteramos ele com dq->inicio = dq->inicio->prox
*/

void libera_Deque(Deque* dq){
    if(dq!=NULL){
        Elem* no;
        while(dq->inicio != NULL){
            if(dq->inicio->prox == NULL){
                no = dq->inicio;
                dq->inicio = NULL;
                dq->final = NULL;
                dq->qtd--;
                free(no);
            }
            else{
                no = dq->inicio;
                dq->inicio->prox->ant = NULL;
                dq->inicio = dq->inicio->prox;
                dq->qtd--;
                free(no);
            }
        }
        free(dq);
    }
}

/*
Deque_vazio retorna 1 se a alocacao nao foi feita com sucesso
e 1 tambem se ela realmente estiver vazia(dq->inicio == NULL)
*/

int Deque_vazio(Deque* dq){
    if(dq == NULL)
        return 1;
    if(dq->inicio == NULL)
        return 1;
    return 0;
}

/*
retorna a quantidade de elementos guardada no no cabeça
essa quantidade sempre é considerada(incrementada ou decrementada)
conforme as operacoes de remover e inserir ocorrem
*/

int tamanho_Deque(Deque* dq){
    if(dq == NULL)
        return 0;
    return dq->qtd;
}

/*
insereInicio_Deque e insereFinal_Deque verifica se foi alocado com sucesso e
se a qtd que esta armazenada no no cabeca for menor que o tamanho
setado ele faz a insercao, caso seja maior ele printa cheia e nao
insere
*/

void insereInicio_Deque(Deque* dq, T x, int tamanho){
    if(dq == NULL) return ;
    if(dq->qtd < tamanho){
        Elem *no = (Elem*)malloc(sizeof(Elem));
        //caso ele nao tenha conseguido alocar o auxiliar
        if(no == NULL) return ;
        no->dados = x;
        no->prox = dq->inicio;
        //como eh no inicio obrigatoriamente o ponteiro ant tem q ser para NULL
        no->ant = NULL;
        //caso ela esteja vazia tem q incluir a mudanca do ponteiro final
        if(dq->inicio == NULL)
                dq->final = no;
        //caso ela nao esteja vazia temos q mudar o anterior do q esta primeiro
        else
            dq->inicio->ant = no;
        //agora por ultimo como estamos inserindo no inicio setamos
        //o ponteiro do inicio para apontar para o novo
        dq->inicio = no;
        dq->qtd++;
        return ;
    }
    printf("cheia\n");
}

void insereFinal_Deque(Deque* dq, T x, int tamanho){
    if(dq == NULL) return ;
    if(dq->qtd < tamanho){
        Elem *no = (Elem*)malloc(sizeof(Elem));
        if(no == NULL) return ;
        no->dados = x;
        no->prox = NULL;
        //caso esteja vazia apenas fazemos o anterior do novo apontar para NULL
        //pq o prox dele ja vai apontar pra NULL
        //alem disso colocamos dqinicio para apontar para ele
        if(dq->final == NULL){
            no->ant = NULL;
            dq->inicio = no;
        }
        //caso nao esteja vazia precisamos q o anterior dele aponte para o antigo fim
        // e precisamos q o prox do ultimo aponte para o novo no
        else{
            no->ant = dq->final;
            dq->final->prox = no;
        }
        //por ultimo, setamos para o final apontar para o novo no que vai ser o final
        // e incrementamos a quantidade
        dq->final = no;
        dq->qtd++;
        return ;
    }
    //caso nao entre e nao consiga inserir apenas printamos cheia
    printf("cheia\n");
}

/*
removeInicio_Deque e removeFim_Deque verificam se a alocacao foi feita e
verificam se o deque esta vazio, para ja printar e retornar a main
alem disso em ambos passamos o endereco de x na main para conseguir alterar
o conteudo e armazenar o valor que vai ser retirado(assim podemos printar que valor foi
retirado)
*/

void removeInicio_Deque(Deque* dq, int *x){
    if(dq == NULL) return ;
    if(dq->inicio == NULL){
        printf("vazia\n");
        return ;
    }
    Elem *no = dq->inicio;
    *x = dq->inicio->dados;
    //mudamos o inicio para ser o prox
    dq->inicio = dq->inicio->prox;
    //vemos se o deque ficou vazio
    if(dq->inicio == NULL)
        dq->final = NULL;
    //se ele tiver mais elementos apenas setamos o anterior do novo inicio incrementado
    //para ser nulo, nao precisamos alterar o ponteiro do final
    else
        dq->inicio->ant = NULL;
    //por fim apenas damos free no no removido e decrementamos a qtd
    free(no);
    dq->qtd--;

}

void removeFim_Deque(Deque* dq, int *x){
    if(dq == NULL) return ;
    if(dq->inicio == NULL){
        printf("vazia\n");
        return ;
    }
    Elem *no = dq->final;
    *x = dq->final->dados;
    //caso tenha apenas um elemento
    if(no == dq->inicio){
        dq->inicio = NULL;
        dq->final = NULL;
    }
    //caso tenha mais de um elemento temos que mudar o proximo do anterior
    //afinal ele vai ter q apontar agora para nulo por estarmos removendo o ultimo elemento
    //alem disso mudamos para onde o final esta apontando
    else{
        no->ant->prox = NULL;
        dq->final = no->ant;
    }
    free(no);
    dq->qtd--;
}

/*
na funcao imprimir pegamos um auxiliar e apenas fazemos com que ele aponte para
o inicio(afinal nao precisamos dar malloc porque nao vamos inserir), utilizaremos ele
para percorrer o deque
essa funcao foi utilizada com o intuito de teste para o inserir e remover
*/

void imprimir(Deque* dq){
    if(dq->inicio == NULL)
        printf("vazio");
    Elem *aux = dq->inicio;
    while(aux!=NULL){
      //o if dentro do while eh apenas para o print sair "certo" com relacao aos espacos
        if(aux->prox == NULL){
            printf("%d", aux->dados);
            aux = aux->prox;
        }
        else{
            printf ("%d ", aux->dados);
            aux = aux->prox;
        }
    }
    printf("\n");
}

/*
na main utilizaremos 5 strings para usar ifs com strcmp,
possibilitando um tipo de switch, alem disso usamos ctop para
printar o elemento que foi removido. No fim liberamos o deque.
*/

int main(){
    int comandos, tamanho;
    T numero;
    char b[10] = "insereI";
    char c[10] = "insereF";
    char d[10] = "removeI";
    char e[10] = "removeF";
    char a[10];//sera o comando de cada rodada
    Deque* dq = cria_Deque();
    scanf("%d %d", &comandos, &tamanho);
    for (int i = 0; i < comandos; i++) {
        int ctop;
        scanf("%s", a);
        if((strcmp(a, b))==0){
            scanf("%d", &numero);
            insereInicio_Deque(dq, numero, tamanho);
        }
        if((strcmp(a, c))==0){
            scanf("%d", &numero);
            insereFinal_Deque(dq, numero, tamanho);
        }
        if((strcmp(a, d))==0){
            if(dq->inicio!=NULL){
            removeInicio_Deque(dq, &ctop);
            printf("%d\n", ctop);
            }
            else
                removeInicio_Deque(dq, &ctop);
        }
        if((strcmp(a, e))==0){
            if(dq->inicio!=NULL){
            removeFim_Deque(dq, &ctop);
            printf("%d\n", ctop);
            }
            else
                removeFim_Deque(dq, &ctop);
        }
    }
    libera_Deque(dq);
    return 0;
}
