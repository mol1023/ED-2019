#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //caso use tolower ou toupper
/*
Nicolas Marcondes Molina
RA:743584
*/
double fatorial(double n){//calcula o fatorial para usar depois na funcao de binomial
    if(n == 0)
        return 1;
    else
        return n*fatorial(n-1);
}

double binomial(double n, double k){// calcula o binomial para usar depois na funcao de pascal
    return fatorial(n)/(fatorial(k)*fatorial(n-k));
}

int P(int n, int k){
    if(n == 0)
        return 1;
    if(n == 1)
        return 1;
    else
        return binomial(n, k);
}

unsigned long long int binomialit(int n, int k){//versao iterativa
    int i, j;
    unsigned long long int v[n+1][k+1];

    for(i = 0; i <= n; i++){
        for (j = 0; j <= k; j++){
            v[i][j] = 1;//inicializa todas com 1, que seriam bordas entre outros
        }
    }

    for(i = 0; i <= n; i++){
        for(j = 0; j <= k; j++){
            if((i != j) && (i!=0) && (j != 0))
                v[i][j] = v[i-1][j-1] + v[i-1][j];//o atual vai ser igual o da diagonal esquerda + o acima dele, uma linha antes
        }
    }

    return v[n][k];//retorna valor desejado atraves dos indices
}

int main(){
    int l, c;
    scanf("%d %d", &l, &c);//linha e coluna

    if(l < 10)
        printf("%d\n", P(l, c));
    else
        printf("%llu\n", binomialit(l, c));
    return 0;
}
