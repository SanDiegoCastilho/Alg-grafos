#include <stdio.h>
#include <float.h>
#include <stdlib.h>

typedef struct no{
      struct no* prox;
      double peso;
      int valor;
} No;

typedef struct heap{
	No** valores;
	int comprimento;
	int tamanho;
} Heap;


//Assinaturas das funções da HEAP.
//Retorna a posição do Pai de um dado elemento.
int Pai(int i);

//Retorna a posição do Filho esquerdo de um dado elemento. 
int FEsquerdo(int i);

//Retorna a posição do Filho direito de um dado elemento.
int FDireito(int i);

//Extrai o peso mínimo armazenado na HEAP.
double ExtrairMin(Heap* h);

//Função responsável por manter a propriedade de HEAP.
void Descer(Heap* v, int i);

//Função auxiliar responsável por trocar dois Nós na HEAP.
void Trocar(Heap* h, int i, int j);

//Função responsável por Diminuir a Chave de um determinado Nó na HEAP.
void DiminuirChave(Heap *h, int i, double chave);

//Insere um Nó na HEAP.
void InserirChave(Heap* h, No* u);

//Inicializa A HEAP.
Heap* ConstruirHeap(int n);

//Verifica se a HEAP está vazia.
int HeapVazia(Heap* h);



No* AlocaNo(int v, double p);


int main(){
	int v1 = 0, v2 = 0;
	double p = 0;
	Heap* h = ConstruirHeap(10);

	for (int i = 0; i < 5; i++){
    	scanf("%d %d %lg", &v1, &v2, &p);
    	InserirChave(h, AlocaNo((v2 - 1), p));
	}


	for (int i = 0; i <= h->tamanho; i++){
		printf("H[%d] = > peso: %lg No: %d\n",i, h->valores[i]->peso, h->valores[i]->valor);
	}

	double min = 0;

	for (int i = 0; i < 5; i++){
		min = ExtrairMin(h);

		printf("min: %lg\n", min);

		for (int i = 0; i <= h->tamanho; i++){
			printf("H[%d] = > peso: %lg No: %d\n",i, h->valores[i]->peso, h->valores[i]->valor);
		}
	}

	// InserirChave(h, 300.45);
	// InserirChave(h, 290.15);
	// InserirChave(h, 30.95);
	// InserirChave(h, 3083.95);
	// InserirChave(h, 20.95);
	// InserirChave(h, 2150.95);

	// printf("\n");
	// for (int i = 0; i < h->comprimento; i++){
	// 	printf("valor : %g\n", h->val[i]);
	// }

	// printf("\n");
	// printf("valor minimo: %g\n", ExtrairMin(h));

	// printf("\n");
	// for (int i = 0; i <= h->tamanho; i++){
	// 	printf("valor: %g\n", h->val[i]);
	// }

	return 0;
}


//Definição das funções de manipulação de HEAP.
int Pai(int i){
	if (i != 0 && i % 2 == 0)
		return (i >> 1) - 1;

	return (i >> 1);
}

int FEsquerdo(int i){
	return (2 * i) + 1;
}

int FDireito(int i){
	return (2 * i) + 2;
}

//Extrai o peso mínimo armazenado na HEAP.
double ExtrairMin(Heap* h){
	if (h != NULL && h->tamanho >= 0){
		double min = h->valores[0]->peso;
		h->valores[0] = h->valores[h->tamanho];
		h->tamanho = (h->tamanho - 1); 
		Descer(h, 0);

		return min;
	}

	return 0;
}

//Função responsável por manter a propriedade de HEAP.
void Descer(Heap* h, int i){
	if (h != NULL && i >= 0 && i <= h->tamanho){
		int e = FEsquerdo(i);
		int d = FDireito(i);
		int menor = 0;

		if ((e <= h->tamanho) && (h->valores[e]->peso < h->valores[i]->peso))
			menor = e;
		else
			menor = i;
		

		if ((d <= h->tamanho) && (h->valores[d]->peso < h->valores[menor]->peso))
			menor = d;
		

		if (menor != i){
			Trocar(h, i, menor);
			Descer(h, menor);
		}
	}
}

//Função auxiliar responsável por trocar dois Nós na HEAP.
void Trocar(Heap* h, int i, int j){
	if (h != NULL){
		No* aux = (No*)malloc(sizeof(No));

		aux = h->valores[j];
		h->valores[j] = h->valores[i];
		h->valores[i] = aux;

	}
}

//Função responsável por Diminuir a Chave de um determinado Nó na HEAP.
void DiminuirChave(Heap *h, int i, double chave){
	if (h != NULL && chave < h->valores[i]->peso){
		h->valores[i]->peso = chave;

		// if (chave == -96.8){
		// 	printf("pai: %d\n", Pai(i));
		// 	printf("peso do pai: %lg\n", h->valores[Pai(i)]->peso);
		// }

		if (i % 2 == 0){
			printf("Pai (%d): %d\n",i, Pai(i));
		}
		while(i > 0 && h->valores[Pai(i)]->peso > h->valores[i]->peso){
			printf("chave: %lg\n", chave);
			Trocar(h, i, Pai(i));
			i = Pai(i);
		}
	}
}

//Insere um Nó na HEAP.
void InserirChave(Heap* h, No* u){
	if (h != NULL && u != NULL){
		double peso = u->peso;
		h->tamanho = (h->tamanho + 1);
		h->valores[h->tamanho] = u;
		h->valores[h->tamanho]->peso = DBL_MAX;

		DiminuirChave(h, h->tamanho, peso);
	}
}

//Inicializa A HEAP.
Heap* ConstruirHeap(int n){
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->valores = (No**)malloc(sizeof(No*) * n);
	h->comprimento = n;
	h->tamanho = -1;

	for (int i = 0; i < n; i++){
		h->valores[i] = NULL;
	}

	return h;
}

//Verifica se a HEAP está vazia.
int HeapVazia(Heap* h){
	if (h->tamanho == -1){
		return 1;
	}

	return 0;
}

No* AlocaNo(int v, double p){
      No* n = (No*) malloc(sizeof(No));

      n->valor = v;
      n->prox = NULL;
      n->peso = p;

      return n;
}