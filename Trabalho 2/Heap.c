#include <stdio.h>
#include <float.h>
#include <stdlib.h>

typedef struct heap{
	double *val;

	int comprimento;

	int tamanho;
} Heap;

//Assinaturas das funções da HEAP.
int Pai(int i);

int FEsquerdo(int i);

int FDireito(int i);

double ExtrairMin(Heap* h);

void AmontoarMin(Heap* v, int i);

void Trocar(Heap* h, int i, int j);

void DiminuirChave(Heap *h, int i, double v);

void InserirChave(Heap* h, double v);

Heap* ConstruirHeap(int n);

int HeapVazia(Heap* h);



int main(){

	Heap* h = ConstruirHeap(10);

	for (int i = 0; i < h->comprimento; i++){
		printf("valor : %g\n", h->val[i]);
	}

	InserirChave(h, 300.45);
	InserirChave(h, 290.15);
	InserirChave(h, 30.95);
	InserirChave(h, 3083.95);
	InserirChave(h, 20.95);
	InserirChave(h, 2150.95);

	printf("\n");
	for (int i = 0; i < h->comprimento; i++){
		printf("valor : %g\n", h->val[i]);
	}

	printf("\n");
	printf("valor minimo: %g\n", ExtrairMin(h));

	printf("\n");
	for (int i = 0; i <= h->tamanho; i++){
		printf("valor: %g\n", h->val[i]);
	}

	return 0;
}



int Pai(int i){
	return (i >> 1);
}

int FEsquerdo(int i){
	return (2 * i);
}

int FDireito(int i){
	return (2 * i) + 1;
}

double ExtrairMin(Heap* h){
	if (h->tamanho < 1){
		printf("Heap Underflow\n");
	}

	printf("valor de val[tamanho]: %g\n", h->val[h->tamanho]);
	double min = h->val[0];
	h->val[0] = h->val[h->tamanho];
	h->tamanho = (h->tamanho - 1); 

	AmontoarMin(h, 0);

	return min;
}

void AmontoarMin(Heap* h, int i){
	int e = FEsquerdo(i);
	int d = FDireito(i);
	int menor = 0;

	if ((e <= h->tamanho) && (h->val[e] < h->val[i])){

		menor = e;

	}else{
		menor = i;
	}

	if ((d <= h->tamanho) && (h->val[d] < h->val[i])){
		menor = d;
	}

	if (menor != i){
		Trocar(h, i, menor);
		AmontoarMin(h, menor);
	}
}

void Trocar(Heap* h, int i, int j){
	double aux;

	aux = h->val[i];

	h->val[i] = h->val[j];

	h->val[j] = aux;
}

void DiminuirChave(Heap *h, int i, double v){
	if (v > h->val[i]){
		printf("Valor é maior que a chave\n");
	}

	h->val[i] = v;
	while(i >= 1 && h->val[Pai(i)] > h->val[i]){
		Trocar(h, i, Pai(i));
		i = Pai(i);
	}
}

void InserirChave(Heap* h, double v){
	h->tamanho = (h->tamanho + 1);
	h->val[h->tamanho] = DBL_MAX;
	DiminuirChave(h, h->tamanho, v);
}

Heap* ConstruirHeap(int n){
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->val = (double*)malloc(sizeof(double) * n);
	h->comprimento = n;
	h->tamanho = -1;

	for (int i = 0; i < n; i++){
		h->val[i] = DBL_MAX;
	}

	return h;
}

int HeapVazia(Heap* h){
	if (h->tamanho == -1){
		return 1;
	}

	return 0;
}