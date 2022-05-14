#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum Algoritmo {
  BubbleSort,
  MergeSort,
  QuickSort
};

void bubbleSort(int* vetor, int n);
void mergeSort(int* vetor, int inicio, int fim);
void merge(int* vetor, int inicio, int meio, int fim);
void quickSort(int* vetor, int inicio, int fim);
int particiona(int* vetor, int inicio, int fim);

void printVetor(int* vetor, int tamanho);
void executarAlgoritmo(int* vetor, int tamanho, enum Algoritmo algoritmo);
int algoritmoValido(char algoritmo, char* algoritmos, int tamanho);
bool numeroValido(char* texto);

int main(int argc, char **argv) {
  int tamanho = 0;
  char algoritmos[] = { 'b', 'm', 'q' };
  char algoritmo = 'b';

  for(int i = 0; i < argc; i++) {
    if(strcmp(argv[i], "-n") == 0)
      tamanho = atoi(argv[i + 1]);
    else if(!numeroValido(argv[i]) && strlen(argv[i]) == 2)
      algoritmo = argv[i][1];
  }

  int algoritmoDeOrdenacao = algoritmoValido(algoritmo, algoritmos, 3);

  if(tamanho == 0 || algoritmoDeOrdenacao == -1)
    return 1;

  int* vetor = malloc(tamanho * sizeof(int));

  srand(time(NULL));

  for(int i = 0; i < tamanho; i++)
    vetor[i] = rand();

  executarAlgoritmo(vetor, tamanho, algoritmoDeOrdenacao);
  printVetor(vetor, tamanho);

  free(vetor);

  return 0;
}

void executarAlgoritmo(int* vetor, int tamanho, enum Algoritmo algoritmo) {
  switch(algoritmo) {
    case BubbleSort:
      bubbleSort(vetor, tamanho);
      break;

    case MergeSort:
      mergeSort(vetor, 0, tamanho);
      break;

    case QuickSort:
      quickSort(vetor, 0, tamanho - 1);
      break;
    
    default:
      break;
  }
}

bool numeroValido(char* texto) {
  for(int i = 0; texto[i] != '\0'; i++) {
    if (isdigit(texto[i]) == 0)
      return false;
  }

  return true;
}

int algoritmoValido(char algoritmo, char* algoritmos, int tamanho) {
  for(int i = 0; i < tamanho; i++)
    if(algoritmos[i] == algoritmo)
      return i;

  return 0;
}

void printVetor(int* vetor, int tamanho) {
  for(int i = 0; i < tamanho; i++)
    printf("%d%s", vetor[i], i == tamanho - 1 ? "\n" : " ");
}

void bubbleSort(int* vetor, int tamanho) {
  int i = 0, temp;
  bool trocou = true;

  while(i < tamanho && trocou) {
    trocou = false;

    for (int j = 0; j < tamanho - 1 - i; j++) {
      if (vetor[j] > vetor[j + 1]) {
        temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;

        trocou = true;
      }
    }
  }
}

void mergeSort(int* vetor, int inicio, int tamanho) {
  if(inicio < tamanho - 1) {
    int meio = (inicio + tamanho) / 2;

    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio, tamanho);
    merge(vetor, inicio, meio, tamanho);
  }
}

void merge(int* vetor, int inicio, int meio, int tamanho) {
  int i, j, pos;
  int* temp;

  temp = malloc((tamanho - inicio) * sizeof(int));

  i = inicio;
  j = meio;
  pos = 0;

  while(i < meio && j < tamanho) {
    if(vetor[i] <= vetor[j]) {
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

void quickSort(int* vetor, int inicio, int fim) {
  if(inicio < fim) {
    int pivot = particiona(vetor, inicio, fim);

    quickSort(vetor, inicio, pivot - 1);
    quickSort(vetor, pivot + 1, fim);
  }
}

int particiona(int* vetor, int inicio, int fim) {
  int temp, i, pivot, pospivot;

  i = inicio;

  srand(time(NULL));
  pospivot = inicio + rand() % (fim - inicio);

  temp = vetor[pospivot];
  vetor[pospivot] = vetor[fim]; 
  vetor[fim] = temp;

  pivot = vetor[fim];

  for(int j = inicio; j < fim; j++) {
    if (vetor[j] <= pivot) {
      temp = vetor[i];
      vetor[i] = vetor[j]; 
      vetor[j] = temp;

      i++; 
    } 
  }

  temp = vetor[i];
  vetor[i] = vetor[fim];
  vetor[fim] = temp;

  return i;
}