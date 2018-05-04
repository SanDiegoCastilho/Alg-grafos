#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

typedef struct no{
	int valor;
	struct no *prox;
} No;

No AlocaNo(int v){
	No n;

	n.valor = v;
	n.prox  = NULL;

	return n;
}

int main(){
	int n, v1, v2;
	No n1, n2;
	char x;

	scanf("%d", &n);

	No** v = (No**) malloc(n * sizeof(No*));

	do{
		scanf("%d %d", &v1, &v2);

		n1 = AlocaNo(v1);
		n2 = AlocaNo(v2);

		v[v1 - 1] = &n1;
		v[v2 - 1] = &n2;

	}while(getchar() != '\n');
		

	return 0;
}