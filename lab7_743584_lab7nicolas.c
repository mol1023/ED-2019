#include <stdio.h>
#include <limits.h>

typedef struct xama{
	int endereco;
	float input;
}xama;

void merge(xama v[],int l,int m, int r){
	int n1 = m - l + 1, n2 = r - m, i, j, k;
	xama L[n1], R[n2];

	for(i = 0; i < n1; i++){
    L[i] = v[l + i];
		/*L[i].input = v[l + i].input;
		L[i].endereco = v[l + i].endereco;*/
	}
	for(j = 0; j < n2; j++){
    R[j] = v[m + j + 1];
		/*R[j].input = v[m + j + 1].input;
		R[i].endereco = v[m + j + 1].endereco;*/
	}
	i = 0; j = 0;

  for(k = l; (i < n1 && j < n2); k++){
    //if(i < n1 && j < n2)
    //{
  		if(L[i].input <= R[j].input){
  			v[k] = L[i];
  			//v[k].endereco = L[i].endereco;
  			i++;
  		}
  		else{
  			v[k] = R[j];
  			j++;
  		}
    //}
	}

  for (; i < n1; i++)
  {
    v[k] = L[i];
    k++;
  }

  for (; j < n2; ++j)
  {
    v[k] = R[j];
    k++;
  }
}

void mergesort(xama v[],int l,int r){
	int m;
	if(l < r){
		m = (l + r)/2;
		mergesort(v, l, m);
		mergesort(v, m + 1, r);
		merge(v, l, m, r);
	}
}

/*int bb(xama vetor[], int tam, int key){
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
}*/

int main(){
	int n, i, l = 0, r;
	scanf("%d", &n);
	int indice[n];
	float numeros[n];
	r = n - 1;
	xama input[n];

	for(i = 0; i < n; i++){
		scanf("%f", &input[i].input);
		input[i].endereco = i;
		indice[i] = i;
		numeros[i] = input[i].input;
	}

	mergesort(input, l, r);
  printf("%d", input[0].endereco);
	for(i = 1; i < n; i++){
		printf(" %d", input[i].endereco);
	}

	printf("\n");
	return 0;
}

