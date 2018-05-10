#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//Define um conjunto que representa um vétice na LA.
typedef struct no{
	int valor;
	struct no *prox;
} No;

//Variáveis globais referente a Fila;
int inicio , fim;

//Função responsável por alocar um nó na LA;
No AlocaNo(int v1, int v2, No **v);

//Aloca uma fila de nós para a busca em largura.
int* AlocaFila(int tamanho);

//Enfileira um nó.
void Enfileirar(int v, int *fila);

//Desenfileira um nó.
int* Desenfileirar(int *fila);

//Verifica se a fila está vazia.
bool FilaVazia();

//Função principal.
int main(){
	int n, v1, v2;
	No n1, n2;

	scanf("%d", &n);

	int* Dist = (int*) malloc(n * sizeof(int));
	No** ListaAdja = (No**) malloc(n * sizeof(No*));

	for (int i = 0; i < n; i++){
		Dist[i] = -1;
		ListaAdja[i] = NULL;
	}

	//parte de receber o código.
	do{
		scanf("%d %d", &v1, &v2);
		AlocaNo(v1, v2, ListaAdja);

	}while(getchar() != '\n');

	int *F = AlocaFila(n);

	for (int i = 0; i < n; i++){
	 	Enfileirar(i, F);

	 	while(!FilaVazia()){
	 		int aux = Desenfileirar(F);
	 		No *u 	= ListaAdja[aux];	 	}

	 		while((*u).prox != NULL){
	 			printf("lero\n" );
	 		}
	 } 

	return 0;
}

//Definindo a função principal.
No AlocaNo(int v1, int v2, No **v){
	No n;
	n.valor = v2;

	if (v[v1 - 1] == NULL){
		n.prox = NULL;
		v[v1 - 1] = &n;

	}else{
		n.prox = v[v1 - 1];
		v[v1 - 1] = &n;
	}

	return n;
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