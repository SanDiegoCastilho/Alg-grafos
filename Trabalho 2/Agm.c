#include <stdio.h>
#include <stdlib.h>


typedef struct no{
      struct no* prox;
      int valor;
      double peso;
} No;

typedef struct heap{
      No** val;
      int comprimento;
      int Htamanho;
} Heap;

typedef struct grafo{
      No** LA;
      int Gtamanho;
} GrafoLA;


//Assinaturas das funçῶoes do Grafo.
No* AlocaNo(int v, double p);

GrafoLA* AlocaGrafoLA(int t);

void IncluirNo(GrafoLA* g, No* no, int indice);

 // double RetornaPeso(double** pesos, int i, int j);

// void AdicionarPeso(double** pesos, int i, int j, double p);

//Assinaturas das funções da HEAP.
Heap* ConstruirHeap(int n);

void InserirChave(Heap* h, No* v);

void DiminuirChave(Heap *h, int i, No* v);

void Trocar(Heap* h, int i, int j);

No* ExtrairMin(Heap* h);

void AmontoarMin(Heap* v, int i);

int Pai(int i);

int FEsquerdo(int i);

int FDireito(int i);

int HeapVazia(Heap* h);


int main(){
      int n = 0, v1 = 0, v2 = 0;
      double p = 0, soma = 0;

      scanf("%d", &n);
      int* pai = (int*)malloc(sizeof(int) * n);
      int* atingido = (int*)malloc(sizeof(int) * n);
      GrafoLA* g = AlocaGrafoLA(n);
      Heap *h = ConstruirHeap(n);

      for (int i = 0; i < n; i++){
            pai[i] = -1;
            atingido[i] = 0;
      }

      IncluirNo(g, AlocaNo((v2-1), p), (v1-1));
      IncluirNo(g, AlocaNo((v1-1), p), (v2-1));

      /*Rever esse algoritmo*/
      No* u = g->LA[0];
      atingido[0] = 1;

      while(u != NULL){
            atingido[u->valor] = 1;
            InserirChave(h, u);
            pai[u->valor] = 0;
            u = u->prox;
      }

      while(!HeapVazia(h)){
            No* w = (No*)malloc(sizeof(No));
            w = ExtrairMin(h);

            soma += w->peso;

            w = g->LA[w->valor];
            while(w != NULL){
                  if (!atingido[w->valor]){
                        atingido[w->valor] = 1;
                        // pai[w->valor] = w->valor;

                  }else{
                        if(Pertence(z, h) && ){

                        }
                  }
            }
      }



     

      return 0;
}

Heap* ConstruirHeap(int n){
      Heap* h = (Heap*)malloc(sizeof(Heap));
      h->val = (No**)malloc(sizeof(No*) * n);
      h->comprimento = n;
      h->Htamanho = -1;

      for (int i = 0; i < n; i++){
            h->val[i] = NULL;
      }

      return h;
}

void InserirChave(Heap* h, No* v){
      h->Htamanho = (h->Htamanho + 1);
      h->val[h->Htamanho] = NULL;
      DiminuirChave(h, h->Htamanho, v);
}

void DiminuirChave(Heap *h, int i, No* v){
      h->val[i] = v;
      while(i >= 1 && h->val[Pai(i)]->peso > h->val[i]->peso){
            Trocar(h, i, Pai(i));
            i = Pai(i);
      }
}

void Trocar(Heap* h, int i, int j){
      No* aux = (No*)malloc(sizeof(No));

      aux = h->val[i];
      h->val[i] = h->val[j];
      h->val[j] = aux;
}

No* ExtrairMin(Heap* h){
      if (h->Htamanho < 0){
            printf("Heap Underflow\n");
      }

      No* min = (No*)malloc(sizeof(No));
      min = h->val[0];
      h->val[0] = h->val[h->Htamanho];
      h->Htamanho = (h->Htamanho - 1); 

      AmontoarMin(h, 0);

      return min;
}

void AmontoarMin(Heap* h, int i){
      int e = FEsquerdo(i);
      int d = FDireito(i);
      int menor = 0;

      if ((e <= h->Htamanho) && (h->val[e]->peso < h->val[i]->peso)){
            menor = e;

      }else{
            menor = i;

      }

      if ((d <= h->Htamanho) && (h->val[d]->peso < h->val[i]->peso)){
            menor = d;
      }

      if (menor != i){
            Trocar(h, i, menor);
            AmontoarMin(h, menor);
      }
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

int HeapVazia(Heap* h){
      if (h->Htamanho == -1){
            return 1;
      }

      return 0;
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

// double RetornaPeso(double** pesos, int i, int j){
//       return pesos[i][j];
// }

// void AdicionarPeso(double** pesos, int i, int j, double p){
//       pesos[i][j] = p;
// }
