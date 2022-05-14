#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct Stack_ {
  int chave;
  struct Stack_ *prox;
} Stack;

void init(Stack** ptTopo);
int push(Stack** ptTopo, int x);
int pop(Stack** ptTopo, int *x);

int precedencia(char operador);
int calcularOperacao(int operando1, int operando2, char operador);
int calcularExpressao(char* expressao);
char* removerEspacos(char* texto);

int main() {
	char *entrada = malloc(sizeof(char) * 100), *temp;

	scanf("%[^\n]", entrada);

	temp = entrada;
	entrada = removerEspacos(entrada);

	printf("%d", calcularExpressao(entrada));

	free(temp);
	free(entrada);

  return 0;
}

void init(Stack** ptTopo) {
  *ptTopo = NULL;
}

int push(Stack** ptTopo, int x) {
  Stack* novo = (Stack*) malloc(sizeof(Stack));

  if(novo == NULL)
    return 1;
  
  novo->chave = x;
  novo->prox = *ptTopo;
  *ptTopo = novo;

  return 0;
}

int pop(Stack** ptTopo, int *x) {
  if(*ptTopo == NULL)
    return 1;
  
  *x = (*ptTopo)->chave;

  Stack* pt = *ptTopo;
  *ptTopo = (*ptTopo)->prox;

  free(pt);

  return 0;
}

int precedencia(char operador) {
	switch(operador) {
    case '+':
    case '-':
			return 1;
    case '*':
    case '/':
			return 2;
		default:
			return 0;
  }
}
 
int calcularOperacao(int operando1, int operando2, char operador) {
  switch(operador) {
    case '+':
			return operando1 + operando2;
    case '-':
			return operando1 - operando2;
    case '*':
			return operando1 * operando2;
    case '/':
			return operando1 / operando2;
  }
}

int calcularExpressao(char* expressao) {
  Stack *operandos, *operadores;

  init(&operandos);
  init(&operadores);
    
  for(int i = 0; expressao[i] != '\0'; i++) {
    if(expressao[i] == ' ')
      continue;

    if(expressao[i] == '(')
      push(&operadores, (int)expressao[i]);
    else if(isdigit(expressao[i])) {
      int operando = 0;

      while(expressao[i] != '\0' && isdigit(expressao[i])) {
        operando = (operando * 10) + (expressao[i] - '0');
        i++;
      }
        
      push(&operandos, operando);
      i--;
    }
    else if(expressao[i] == ')') {
      int operando1, operando2, operador;

      while(((char)operadores->chave) != '(' && operadores != NULL) {
        pop(&operandos, &operando2);
        pop(&operandos, &operando1);
        pop(&operadores, &operador);
        push(&operandos, calcularOperacao(operando1, operando2, (char) operador));
      }
          
      if(operadores != NULL)
        pop(&operadores, &operador);
    } 
    else {
      while(operadores != NULL && precedencia(operadores->chave) >= precedencia(expressao[i])) {
        int operando1, operando2, operador;
        pop(&operandos, &operando2);
        pop(&operandos, &operando1);
        pop(&operadores, &operador);

        push(&operandos, calcularOperacao(operando1, operando2, (char) operador));
      }
          
      push(&operadores, (int)expressao[i]);
    }
  }
     
  while(operadores != NULL) {
    int operando1, operando2, operador;
    pop(&operandos, &operando2);
    pop(&operandos, &operando1);
    pop(&operadores, &operador);

    push(&operandos, calcularOperacao(operando1, operando2, (char) operador));
  }

  return operandos->chave;
}

char* removerEspacos(char* texto) {
	char* novoTexto = malloc(sizeof(char) * 100);
  int contador = 0;

  for(int i = 0; texto[i] != '\0'; i++)
    if(texto[i] != ' ')
      novoTexto[contador++] = texto[i];
	
	novoTexto[contador] = '\0';
	return novoTexto;
}