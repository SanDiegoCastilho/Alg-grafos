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

//Assinaturas das funções da HEAP.
Heap* ConstruirHeap(int n);

void InserirChave(Heap* h, No* v);

void DiminuirChave(Heap *h, int i, No* v);

void Trocar(Heap* h, int i, int j);

No* ExtrairMin(Heap* h);

void AmontoarMin(Heap* v, int i);

int Pertinencia(Heap *h, No* u);

int Pai(int i);

int FEsquerdo(int i);

int FDireito(int i);

int HeapVazia(Heap* h);

int ChecaExistencia(Heap *h, int indice);


int main(){
      int n = 0, v1 = 0, v2 = 0;
      double p = 0, soma = 0;

      // char c;
      // int entrada = 0;

      // //parte de receber o código.
      // char leitura[40];
      // int cont = 0;
      // do {
      //       scanf("%s", &leitura);
      //       printf("passo 0\n");
      //       cont ++;
      // } while (cont != 3);

      // int convert = 1;
      // int lei;
      // for (int i = 2; leitura[i] != '\0'; i++) {
      //       n *= convert;
      //       lei = leitura[i]-48;
      //       n += lei;
      //       convert = 10;
      // }
      scanf("%d", &n);
      printf("passo 1\n");
      int* pai = (int*)malloc(sizeof(int) * n);
      int* atingido = (int*)malloc(sizeof(int) * n);
      GrafoLA* g = AlocaGrafoLA(n);
      Heap *h = ConstruirHeap(n);

      // char lixo;
      // int n_argumentos;
      // scanf("%s", &lixo);
      // do {
      //       n_argumentos = scanf("%d %d %lg", &v1, &v2, &p);
      //       if (n_argumentos == 3 && 0 < v1 <= n && 0 < v2 <= n && v1 != v2) {

            for (int i = 0; i < 24; i++){
                  scanf("%d %d %lg", &v1, &v2, &p);
                  IncluirNo(g, AlocaNo((v2-1), p), (v1-1));
                  IncluirNo(g, AlocaNo((v1-1), p), (v2-1));
            }

      //       } else
      //             n_argumentos = 0;

      // } while (n_argumentos == 3);


      for (int i = 0; i < n; i++){
            pai[i] = -1;
            atingido[i] = 0;
      }

     

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

            No* z = (No*)malloc(sizeof(No));
            z = g->LA[w->valor];

            while(z != NULL){
                  if (!atingido[z->valor]){
                        atingido[z->valor] = 1;
                        pai[z->valor] = w->valor;

                  }else{
                        int t = Pertinencia(h, z);
                        if(t){
                              DiminuirChave(h, t, z);
                              pai[z->valor] = w->valor; 
                        }
                  }
            }
      }

      printf("%g", soma);

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
      if (h != NULL && v != NULL){
            h->Htamanho = (h->Htamanho + 1);
            h->val[h->Htamanho] = NULL;
            DiminuirChave(h, h->Htamanho, v);
      }
}

void DiminuirChave(Heap *h, int i, No* v){
      if (h != NULL && v != NULL){
            if (ChecaExistencia(i)){
                  h->val[i]->peso = v->peso;
                  while(i >= 1 && h->val[Pai(i)]->peso > h->val[i]->peso){
                        Trocar(h, i, Pai(i));
                        i = Pai(i);
                  }
            }
      }
}

void Trocar(Heap* h, int i, int j){
      No* aux = (No*)malloc(sizeof(No));
      if (ChecaExistencia(i)){
            aux = h->val[i];
            h->val[i] = h->val[j];
            h->val[j] = aux;
      }
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

      if (h !== NULL && ChecaExistencia(e) && ChecaExistencia(d) && ChecaExistencia(i)){
            
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

}

int Pertinencia(Heap *h, No* u){
      if (h != NULL && u != NULL){
            for (int i = 0; i <= h->Htamanho; i++){
                  if(h->val[i]->valor == u->valor){
                        if (h->val[i]->peso > u->peso){
                              return i;
                        }

                  }else{
                        return 0;
                  }
            }
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

int ChecaExistencia(Heap *h, int indice){
      if (h->val[indice] != NULL){
           return 1;
      }

      return 0;
}