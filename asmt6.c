#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "asmt6.h"

numV* evalBinop (binopC *binop) {
   numV *val = malloc(sizeof(numV));
   
   if (strcmp(binop->operator, "+") == 0) {
      val->numVal = *((double *) binop->bozor1) +  *((double *) binop->bozor2);
      //note, must eval these binops later
   }
   else if (strcmp(binop->operator, "-") == 0) {
      val->numVal = *((double *) binop->bozor1) -  *((double *) binop->bozor2);
   }
   else if (strcmp(binop->operator, "*") == 0) {
      val->numVal = *((double *) binop->bozor1) *  *((double *) binop->bozor2);
   }
   else if (strcmp(binop->operator, "/") == 0) {
      
      val->numVal = *((double *) binop->bozor1) /  *((double *) binop->bozor2);
   }
   else if (strcmp(binop->operator, "<=") == 0) {
      
      val->numVal = *((double *) binop->bozor1) <=  *((double *) binop->bozor2);
   }
   else if (strcmp(binop->operator, "eq?") == 0) {
   
      val->numVal = *((double *) binop->bozor1) ==  *((double *) binop->bozor2);
   }

   return val;
}

numV *interp(void *e) {
  char *type = ((numC *) e)->type;

  if (strcmp(type, "binopC") == 0) {
    binopC *expr = (binopC *) e;
    return evalBinop(expr);
  }
  else if (strcmp(type, "numC") == 0) {
    numV *result = malloc(sizeof(numV));
    result->type = malloc(sizeof(char) * 100);
    strcpy(result->type, "numV");

    numC *expr = (numC *) e;
    result->numVal = expr->numVal;
    return result;
  }
  else if (strcmp(type, "ifC") == 0) {
    ifC *expr = (ifC *) e;
    return interp(evalIfC(expr));
  }
  else if (strcmp(type, "boolC") == 0) {
    numV *result = malloc(sizeof(numV));
    result->type = malloc(sizeof(char) * 100);
    strcpy(result->type, "numV");
    result->numVal = ((boolC *) e)->val;
    return result;
  }

  return NULL;
}

int main(int argc, char const* argv[])
{
  numC *e = malloc(sizeof(numC));
  e->type = malloc(sizeof(char) * 100);
  strcpy(e->type, "numC");
  e->numVal = 3;

  printf("%lf\n", interp(e)->numVal);
  return 0;
}
