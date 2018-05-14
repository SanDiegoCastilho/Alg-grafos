#include <stdio.h>
#include <stdlib.h>

typedef struct conexo {
	int tamanho;
	int *conexos;
} Conexo;

int add_aresta(Conexo **vetor_conexo, int vertice1, int vertice2);
int exibe_componentes(Conexo **vetor_conexo, int n);

int main() {
	char leitura[40];
	int cont = 0;
	do {
		scanf("%s", &leitura);
		cont ++;
	} while (cont != 3);

	int n = 0;
	int convert = 1;
	int lei;
	for (int i = 2; leitura[i] != '\0'; i++) {
		n *= convert;
		lei = leitura[i]-48;
		n += lei;
		convert = 10;
	}

	Conexo **vetor_conexos = (Conexo**)malloc((n+1)*sizeof(Conexo*));
	for (int i = 1; i < n+1; i++) {
		Conexo *conexo = (Conexo*)malloc(sizeof(Conexo));
		vetor_conexos[i] = conexo;
		int *vetor = (int*)malloc((n+1)*sizeof(int));
		vetor[0] = i;
		vetor_conexos[i]->tamanho = 1;
		vetor_conexos[i]->conexos = vetor;

	}
	
	int a , b, n_argumentos, maior, menor;

	char lixo;
	scanf("%s", &lixo);
	do {
		n_argumentos = scanf("%d %d", &a, &b);
		if (n_argumentos == 2 && 0 < a <= n && 0 < b <= n && a != b) {
			add_aresta(vetor_conexos, a, b);

		} 
		else n_argumentos = 0;

	} while (n_argumentos == 2);

	exibe_componentes(vetor_conexos, n);


	return 0;
}

int add_aresta(Conexo **vetor_conexo, int vertice1, int vertice2){
	int maior, menor, maior_tam, menor_tam;
	if (vetor_conexo[vertice1]->tamanho > vetor_conexo[vertice2]->tamanho) {
		maior = vertice1;
		menor = vertice2;
		maior_tam = vetor_conexo[vertice1]->tamanho;
		menor_tam = vetor_conexo[vertice2]->tamanho;

	}
	else {
		maior = vertice2;
		menor = vertice1;
		maior_tam = vetor_conexo[vertice2]->tamanho;
		menor_tam = vetor_conexo[vertice1]->tamanho;
	}


	if (vetor_conexo[menor]->conexos != vetor_conexo[maior]->conexos)	{
		int *aux;
		aux = vetor_conexo[menor]->conexos;
			for (int i = maior_tam; i < maior_tam+menor_tam; i++) {
			vetor_conexo[maior]->conexos[i] = aux[i-maior_tam];
			vetor_conexo[aux[i-maior_tam]] = vetor_conexo[maior];
		}

		vetor_conexo[maior]->tamanho = maior_tam+menor_tam;
		free(aux);
	}
	
}

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int exibe_componentes(Conexo **vetor_conexo, int n){
	printf("\n");
	for (int i = 1; i < n+1; i++) {
		if (vetor_conexo[i] != NULL){
			int *valores;
			valores = vetor_conexo[i]->conexos;
			int tam = vetor_conexo[i]->tamanho; 
			qsort (valores, tam, sizeof(int), compare);

			for (int j = 0; j < tam; j++) {
				printf("%d ", valores[j]);
				vetor_conexo[valores[j]] = NULL;
			}
			printf("\n");
		}	
	}
}
