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

typedef struct grafo{
      No** LA;
      int Gtamanho;
} GrafoLA;

//Assinaturas das funçῶoes do Grafo.
No* AlocaNo(int v, double p);

GrafoLA* AlocaGrafoLA(int t);

void IncluirNo(GrafoLA* g, No* no, int indice);

//Assinaturas das funções da HEAP.
//Retorna a posição do Pai de um dado elemento.
int Pai(int i);

//Retorna a posição do Filho esquerdo de um dado elemento. 
int FEsquerdo(int i);

//Retorna a posição do Filho direito de um dado elemento.
int FDireito(int i);

//Extrai o peso mínimo armazenado na HEAP.
No* ExtrairMin(Heap* h);

//Função responsável por manter a propriedade de HEAP.
void Descer(Heap* v, int i);

//Função auxiliar responsável por trocar dois Nós na HEAP.
void Trocar(Heap* h, int i, int j);

//Função responsável por Diminuir a Chave de um determinado Nó na HEAP.
void DiminuirChave(Heap *h, int i, double chave);

//Insere um Nó na HEAP.
void InserirChave(Heap* h, No* u, double chave);

//Inicializa A HEAP.
Heap* ConstruirHeap(int n);

//Verifica se a HEAP está vazia.
int HeapVazia(Heap* h);

/*Checa se um determinado vértice pertence à HEAP, 
retornando o indice correspondente a sua posição nela.*/
int ChecaExistencia(Heap* h, int valor);



int main(){
    int n = 0, v1 = 0, v2 = 0;
    double p = 0;

      char c;
      int entrada = 0;

      //parte de receber o código.
      char leitura[40];
      int cont = 0;
      do {
            scanf("%s", leitura);
            cont ++;
      } while (cont != 3);

      int convert = 1;
      int lei;
      for (int i = 2; leitura[i] != '\0'; i++) {
            n *= convert;
            lei = leitura[i]-48;
            n += lei;
            convert = 10;
      }

      int* pai = (int*)malloc(sizeof(int) * n);
      int* atingido = (int*)malloc(sizeof(int) * n);
      double* dist  = (double*)malloc(sizeof(double) * n);
      GrafoLA* g = AlocaGrafoLA(n);
      Heap *h = ConstruirHeap(n);

      char lixo;
      int n_argumentos;
      scanf("%s", &lixo);
      do {
            n_argumentos = scanf("%d %d %lg", &v1, &v2, &p);
            if (n_argumentos == 3 && 0 < v1 <= n && 0 < v2 <= n && v1 != v2) {


            IncluirNo(g, AlocaNo((v2-1), p), (v1-1));

            } else
                  n_argumentos = 0;

      } while (n_argumentos == 3);


    //Algoritmo de DIJKSTRA.
    for (int i = 0; i < n; i++){
            pai[i] = -1;
            atingido[i] = 0;
            dist[i] = DBL_MAX;
    }

    atingido[0] = 1;
    dist[0] = 0;

    No* u = g->LA[0];

    while(u != NULL){
    	atingido[u->valor] = 1;
    	pai[u->valor] = 0;
    	InserirChave(h, u, u->peso);
    	u = u->prox;
    }

    No* w = (No*)malloc(sizeof(No));
    No* z = (No*)malloc(sizeof(No));

    while(!HeapVazia(h)){
      w = ExtrairMin(h);
    	dist[w->valor] = w->peso;

    	z = g->LA[w->valor];

    	while(z != NULL){
    		if (!atingido[z->valor]){
    			atingido[z->valor] = 1;
    			pai[z->valor] = w->valor;
    			InserirChave(h, z, z->peso + dist[w->valor]);
    		}else{
                  if(ChecaExistencia(h, z->valor) && (z->peso + dist[w->valor]) < h->valores[ChecaExistencia(h, z->valor) - 1]->peso){
                        DiminuirChave(h, ChecaExistencia(h, z->valor) - 1, z->peso + dist[w->valor]);
                        pai[z->valor] = w->valor;
                  }
    		}

            z = z->prox;
    	}
    }

    for(int i = 0; i < n; i++){
          if(dist[i] == DBL_MAX){
                printf("%d INFINITO", (i+1));
          }else{
                printf("%d %.3lf", (i+1), dist[i]);
          }

          if(i != n-1){
                printf("\n");
          }
    }



	return 0;
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

//Insere um Nó na HEAP.
void InserirChave(Heap* h, No* u, double chave){
      if (h != NULL && u != NULL){
            h->tamanho = (h->tamanho + 1);
            h->valores[h->tamanho] = u;
            h->valores[h->tamanho]->peso = DBL_MAX;

            DiminuirChave(h, h->tamanho, chave);
      }
}

//Função responsável por Diminuir a Chave de um determinado Nó na HEAP.
void DiminuirChave(Heap *h, int i, double chave){
      if (h != NULL && chave < h->valores[i]->peso){
            h->valores[i]->peso = chave;

            while(i > 0 && h->valores[Pai(i)]->peso > h->valores[i]->peso){
                  Trocar(h, i, Pai(i));
                  i = Pai(i);
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

// Extrai o peso mínimo armazenado na HEA
No* ExtrairMin(Heap* h){
      if (h != NULL && h->tamanho >= 0){
            No* min = (No*)malloc(sizeof(No));
            min = h->valores[0];

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

/*Checa se um determinado vértice pertence à HEAP,
  retornando o indice correspondente a sua posição nela.*/
int ChecaExistencia(Heap* h, int valor){
      if (h != NULL){
            for (int i = 0; i <= h->tamanho; i++){
                  if (h->valores[i]->valor == valor){
                        return (i + 1);
                  }
            }

            return 0;
      }
}

//Descrição das funçῶoes do Grafo;
GrafoLA* AlocaGrafoLA(int t){
      GrafoLA* g = (GrafoLA*)malloc(sizeof(GrafoLA));
      g->LA = (No**) malloc(t * sizeof(No*));

      g->Gtamanho = t;

      for (int i = 0; i < t; i++){
            g->LA[i] = NULL;
      }

      return g;
}

No* AlocaNo(int v, double p){
      No* n = (No*) malloc(sizeof(No));

      n->valor = v;
      n->prox = NULL;
      n->peso = p;

      return n;
}

void IncluirNo(GrafoLA* g, No* no, int indice){
      if (g != NULL && no != NULL){
            if (g->LA[indice] == NULL){
                  g->LA[indice] = no;

            }else{
                  no->prox = g->LA[indice];
                  g->LA[indice] = no;
            }
      }
}