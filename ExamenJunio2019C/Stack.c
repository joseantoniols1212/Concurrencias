/*
 * Stack.c
 *
 *  Created on: 11 jun. 2019
 *      Author: galvez
 */
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Creates an empty stack.
T_Stack create() {
  return NULL;
}

// Returns true if the stack is empty and false in other case.
int isEmpty(T_Stack q) {
  if(q == NULL) {
    return 1;
  } else {
    return 0;
  }
}

// Inserts a number into the stack.
void push(T_Stack * pq, int operand) {
  T_Stack nuevo = malloc(sizeof(struct Node));
  nuevo->number = operand;
  if(*pq == NULL) {
    nuevo->next = NULL;
  } else {
    nuevo->next = *pq;
  }
  *pq = nuevo;
}

// "Inserts" an operator into the stack and operates.
// Returns true if everything OK or false in other case.
int pushOperator(T_Stack * pq, char operator) {
  int operand1, operand2, ok = 1;

  if (!(pop(pq, &operand1) && pop(pq, &operand2))) ok = 0; // No existen suficientes operandos, false
  else {
    switch (operator) {
    case '+':
      push(pq, operand1+operand2);
      break;
    case '*':
      push(pq, operand1*operand2);
      break;
    case '/':
      push(pq, operand1/operand2);
      break;
    case '-':
      push(pq, operand1-operand2);
      break;
    default:
      ok = 0; // Se pasa un operador no valido, false
    }
  }
  return ok;
}

// Puts into data the number on top of the stack, and removes the top.
// Returns true if everything OK or false in other case.
int pop(T_Stack * pq, int * data) {

  if (*pq == NULL) return 0;

  T_Stack aux = (*pq)->next;
  *data = (*pq)->number;
  free(*pq);
  *pq = aux;
  return 1;
}

// Frees the memory of a stack and sets it to empty.
void destroy(T_Stack * pq) {
  int basura;
  while (pop(pq, &basura));
}
