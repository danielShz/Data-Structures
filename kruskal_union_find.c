#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Aresta_ {
  int vertice1;
  int vertice2;
  int peso;
} Aresta;

void merge(Aresta* vetor, int inicio, int meio, int tamanho) {
  int i, j, pos;
  Aresta* temp;

  temp = malloc((tamanho - inicio) * sizeof(Aresta));

  i = inicio;
  j = meio;
  pos = 0;

  while(i < meio && j < tamanho) {
    if(vetor[i].peso <= vetor[j].peso) {
      temp[pos] = vetor[i];
      i++;
    } else {
      temp[pos] = vetor[j];
      j++;
    }

    pos++;
  }

  while(i < meio) {
    temp[pos] = vetor[i];
    pos++;
    i++;
  }

  while(j < tamanho) {
    temp[pos] = vetor[j];
    pos++;
    j++;
  }

  for(i = inicio; i < tamanho; i++)
    vetor[i] = temp[i - inicio];
  
  free(temp);
}

void mergeSort(Aresta* vetor, int inicio, int tamanho) {
  if(inicio < tamanho - 1) {
    int meio = (inicio + tamanho) / 2;

    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio, tamanho);
    merge(vetor, inicio, meio, tamanho);
  }
}

int find(int* conj, int x) {
  if(x != conj[x])
    conj[x] = find(conj, conj[x]);
  return conj[x];
}

bool Union(int* conj, int* rank, int a, int b) {
  a = find(conj, a);
  b = find(conj, b);

  if(a != b) {
    if(rank[a] < rank[b])
      conj[a] = b;
    else {
      conj[b] = a;
      if(rank[a] == rank[b])
        rank[a] += 1;
    }

    return true;
  }

  return false;
}

int main(int argc, char **argv) {
  // Armazenar entrada
  char entrada[100];
	char temp;

  int n, m, vert1, vert2, peso;

	scanf("%[^\n]", entrada);
  sscanf(entrada, "%d %d", &n, &m);
  scanf("%c", &temp);

  Aresta *arestas = malloc(sizeof(Aresta) * m);

  for(int i = 0; i < m; i++) {
    scanf("%[^\n]", entrada);
    sscanf(entrada, "%d %d %d", &vert1, &vert2, &peso);

    arestas[i].vertice1 = vert1;
    arestas[i].vertice2 = vert2;
    arestas[i].peso = peso;

    scanf("%c", &temp);
  }

  mergeSort(arestas, 0, m);
  
  int *rank = malloc(sizeof(int) * (n + 1));
  int *conj = malloc(sizeof(int) * (n + 1));

  for(int i = 1; i <= n; i++) {
    conj[i] = i;
    rank[i] = 0;
  }

  int somaPesos = 0;

  for(int i = 0; i < m; i++) {
    if(Union(conj, rank, arestas[i].vertice1, arestas[i].vertice2))
      somaPesos += arestas[i].peso;
  }

  printf("%d", somaPesos);
}