#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//Define um conjunto que representa um vétice na LA.
typedef struct no No;

struct no{
	int valor;
	No* prox;
};

//Variáveis globais referente a Fila;
int inicio , fim, TamFila;

//Variável global que representa a componente no qual o vértice pertence.
int comp = 0;

//Função responsável por alocar um nó na LA;
No* AlocaNo(int valor);

//Adiciona um nó alocado na lista de adjacencias na posição correspondente.
void IncluirNo(No** ListaAdja, No* no, int indice);

//Recupera o valor de um nó na posição indicada.
No* RecuperaNo(int i, No** ListaAdja);

//Aloca uma fila de nós para a busca em largura.
int* AlocaFila(int tamanho);

//Enfileira um nó.
void Enfileirar(int v, int *fila);

//Desenfileira um nó.
int Desenfileirar(int *fila);

//Verifica se a fila está vazia.
bool FilaVazia();

//Mostra os componentes na tela.
void MostraComponentes(int* v, int n);

//Função principal.
int main(){
	int n, v1, v2;
	No n1, n2;

	scanf("%d", &n);

	int *Dist = (int*) malloc(n * sizeof(int));
	No** ListaAdja = (No**) malloc(n * sizeof(No*));
	bool *Atingido = (bool*) malloc(n * sizeof(bool));

	for (int i = 0; i < n; i++){
		Dist[i] = -1;
		Atingido[i] = false;
		ListaAdja[i] = NULL;
	}

	//parte de receber o código.
	// do{
	// 	scanf("%d %d", &v1, &v2);
	// 	AlocaNo(v1, v2, ListaAdja);

	// }while(getchar() != '\n');

	for (int i = 0; i < 3; i++){
		scanf("%d %d", &v1, &v2);
		IncluirNo(ListaAdja, AlocaNo((v2-1)), (v1-1));
		IncluirNo(ListaAdja, AlocaNo((v1-1)), (v2-1));
	}

	//Busca em largura.
	int *F = AlocaFila(n);
	int aux;

	for (int i = 0; i < n; i++){
		if (!Atingido[i]){
			
		 	Enfileirar(i, F);
		 	Atingido[i] = true;
		 	Dist[i] = comp;

		 	while(!FilaVazia()){
		 		aux = Desenfileirar(F);
		 		No* u = RecuperaNo(aux, ListaAdja);

		 		if (u == NULL){
		 			Dist[aux] = comp;
		 			Atingido[aux] = true;
		 		}

		 		while(u != NULL){
		 			if (!Atingido[u->valor]){

		 				Enfileirar(u->valor, F);
		 				Atingido[u->valor] = true;
		 				Dist[u->valor] = comp;

		 			}

		 			u = u->prox;
		 		}
		 	}
		}

	 	comp += 1;	
	 }

	 MostraComponentes(Dist, n);

	return 0;
}

//Definindo a função principal.
No* AlocaNo(int valor){
	No *n;

	n = (No*) malloc(sizeof(No));

	n->valor = valor;

	n->prox = NULL;
}

void IncluirNo(No** ListaAdja, No* no, int indice){
	if (ListaAdja != NULL && no != NULL){
		if (ListaAdja[indice] == NULL){
			ListaAdja[indice] = no;

		}else{
			no->prox = ListaAdja[indice];
			ListaAdja[indice] = no;
		}
	}
}

No* RecuperaNo(int i, No** ListaAdja){
	return ListaAdja[i]; 
}

//-----  Definições das funções da Fila -----
int* AlocaFila(int tamanho){

	int *fila = (int *)malloc(tamanho * sizeof(int));
	inicio = fim = 0;

	return fila;
}

void Enfileirar(int v, int *fila){
	fila[fim] = v;
	fim += 1;
}

int Desenfileirar(int *fila){
	inicio += 1;

	return fila[inicio-1];
}

bool FilaVazia(){
	if (inicio == fim){
		return true;
	}

	return false;
}

//Mostrando os componentes na tela.
void MostraComponentes(int* componentes, int n){
	int i = 0;

	while(i < n){
		for (int j = 0; j < n; j++){
			if (componentes[j] == i){
				printf("%d ", (j+1));
			}
		}
		printf("\n");
		i += 1;
	}
}