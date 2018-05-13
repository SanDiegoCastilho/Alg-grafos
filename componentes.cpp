#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//Define um conjunto que representa um vétice na LA.
typedef struct no No;

struct no{
	int valor;
	struct no *prox;
};

//Variáveis globais referente a Fila;
int inicio , fim, TamFila;

//Variável global que representa a componente no qual o vértice pertence.
int comp = 0;

//Função responsável por alocar um nó na LA;
void AlocaNo(int v1, int v2, No **v);

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

	TamFila = n;

	int Dist[n];
	bool Atingido[n];
	No* ListaAdja[n];

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

	for (int i = 0; i < n; i++){
		scanf("%d %d", &v1, &v2);
		AlocaNo((v1-1), (v2-1), ListaAdja);
		AlocaNo((v2-1), (v1-1), ListaAdja);
		No* v = ListaAdja[i];
		printf("%d aaaqui \n", v->valor);
	}


	//Busca em largura.
	int *F = AlocaFila(n);
	int aux;

	for (int i = 0; i < n; i++){
		if (!Atingido[i]){
			
		 	Enfileirar(i, F);

		 	while(!FilaVazia()){
		 		aux = Desenfileirar(F);
		 		No* u = ListaAdja[aux];

		 		if (u == NULL){
		 			Dist[aux] = comp;
		 			Atingido[aux] = true;
		 		}

		 		while(u != NULL){
		 			if (Dist[u->valor] == -1){

		 				Dist[u->valor] = comp;
		 				Enfileirar(u->valor, F);
		 				Atingido[u->valor] = true;

		 				u = u->prox;
		 			}
		 		}
		 	}
		}

	 	comp += 1;	
	 }

	 MostraComponentes(Dist, n);

	return 0;
}

//Definindo a função principal.
void AlocaNo(int v1, int v2, No **ListaAdja){
	No n;
	n.valor = v2;

	if (ListaAdja[v1] == NULL){
		n.prox = NULL;
		ListaAdja[v1] = &n;

	}else{
		n.prox = ListaAdja[v1];
		ListaAdja[v1] = &n;
	}
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
void MostraComponentes(int* v, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; i < n; i++){
			if (v[j] == i){
				printf("%d ", i+1);
			}

			cout << endl;
		}
	}
}