#include <stdio.h>
/*
Nicolas Marcondes Molina
RA:743584
exercicio lab2
*/
//escolhi usar o bubble sorte pela simples implementacao para ordenar o vetor
void bubble(int vetor[], int n){
    int aux;

    for (int i = 1; i < n; i++){
        for (int j = 0; j < n - 1; j++){
            if (vetor[j] > vetor[j+1]){
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}

/*int bb(int vetor[], int tam, int x){
    int e = -1, d = tam;

    while (e < d-1){
        int m = (e + d)/2;
        if(vetor[m] < x)
            e = m;
        else
            d = m;
    }
    return d;
}*/
//busca binaria para achar o elemento que estamos procurando como foi passado nos slides
int bb(int vetor[], int tam, int key){
	int imin = 0;
	int imax = tam-1;
	int imid;

	while(imax >= imin){
		imid = imin  + ((imax - imin) / 2);
		if(key > vetor[imid]){
			imin = imid+1;
		} else if(key < vetor[imid]){
			imax = imid-1;
		} else {
			return key;
		}
	}

	return -1;
}
//busca binaria retorna um indice
int main(){
	int qtd, qtdgar, tamemb[10000], tamgar[1000000], i, j, aux, x, maior = 0;

	scanf("%d", &qtd);

    if (qtd > 10000 || qtd < 1){
        return 0;
    }//condicionais

	for (i=0; i < qtd; i++){
		scanf("%d", &tamemb[i]);
		if (tamemb[i] > maior)
			maior = tamemb[i];
	}

	scanf("%d", &qtdgar);

    if (qtdgar > 1000000 || qtdgar < 1){
        return 0;
    }//condicionais

	for (j=0; j < qtdgar; j++){
		scanf("%d", &tamgar[j]);
	}

    bubble(tamemb,qtd);

    /*for (int k = 0; k < qtd; k++)
        printf("%d ", tamemb[k]);
testes

    for (int l = 0; l < qtdgar; l++)
        printf("%d ", tamgar[l]);*/

	for (i=0; i < qtdgar; i++){
		x = tamgar[i];
		if (x <= maior) {
			while (x <= maior){
				aux = bb(tamemb, qtd, x);
                if (aux == -1)
					x++;
				else
					x = maior + 1;// condicao para retornar = ou > o tamanho da embalagem
			}

			if (aux == -1)
				printf("descartar");
			else
				printf("%d", aux);

			printf("\n");
			aux = 0;
		}
        else
			printf("descartar\n");
	}

	return 0;
}
