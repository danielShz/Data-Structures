#include <stdlib.h>
#include <stdio.h>

typedef struct Lista_ {
  int vert;
  struct Lista_ *prox;
} Lista;

void insere(Lista **ptlista, int x) {
  Lista *novo = malloc(sizeof(Lista));
  novo->vert = x;
  novo->prox = *ptlista;
  *ptlista = novo;
}

int main(int argc, char **argv) {
  // Armazenar entrada

  char entrada[100];
  char *token;
  const char espaco[2] = " ";
	char temp;

  int n, m;

	scanf("%[^\n]", entrada);
  sscanf(entrada, "%d %d", &n, &m);
  scanf("%c", &temp);

  Lista **adj = malloc(sizeof(Lista*) * (n + 1));

  for(int i = 0; i <= n; i++)
    adj[i] = NULL;

  entrada[0] = '\0';
  for(int i = 1; i <= n; i++) {
    scanf("%[^\n]", entrada);
    token = strtok(entrada, espaco);

    if(token != NULL)
      insere(&adj[i], atoi(token));

    while(token != NULL) {
      token = strtok(NULL, espaco);

      if(token != NULL)
        insere(&adj[i], atoi(token));
    }

    scanf("%c", &temp);
    entrada[0] = '\0';
  }

  // Ordenação topológica

  Lista *pt;

  int *gent = malloc(sizeof(int) * (n + 1));
  int *ordem = malloc(sizeof(int) * n);

  for(int i = 1; i <= n; i++)
    gent[i] = 0;

  for(int i = 0; i < n; i++)
    ordem[i] = 0;

  int fim = 0, inicio = 0;

  for(int i = 1; i <= n; i++) {
    pt = adj[i];

    while(pt != NULL) {
      gent[pt->vert]++;
      pt = pt->prox;
    }
  }

  for(int i = 1; i <= n; i++) {
    if(gent[i] == 0) {
      ordem[fim] = i;
      fim++;
    }
  }

  while(inicio != fim) {
    int v = ordem[inicio];
    inicio++;
    pt = adj[v];

    while(pt != NULL) {
      gent[pt->vert]--;

      if(gent[pt->vert] == 0) {
        ordem[fim] = pt->vert;
        fim++;
      }

      pt = pt->prox;
    }
  }

  for(int i = 0; i < n; i++)
    printf("%d ", ordem[i]);
}