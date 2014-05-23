#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "asmt6.h"

#define makeString(P, S) \
  (P) = malloc(sizeof(char) * 16); \
  strcpy((P), (S));

numV *interp(void *e);

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

void* evalIfC(ifC* ifc) {
   if (interp(ifc->test)->numVal == 1) {
      return ifc->then;
   }
   else 
      return ifc->els;
}

numV *interp(void *e) {
  char *type = ((numC *) e)->type;

  if (strcmp(type, "binopC") == 0) {
    binopC *expr = (binopC *) e;
    return evalBinop(expr);
  }
  else if (strcmp(type, "numC") == 0) {
    numV *result = malloc(sizeof(numV));
    makeString(result->type, "numV");

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
    makeString(result->type, "numV");
    result->numVal = ((boolC *) e)->val;
    return result;
  }

  return NULL;
}

int main(int argc, char const* argv[])
{
  numC *e = malloc(sizeof(numC));
  makeString(e->type, "numC");
  e->numVal = 1;

  numC *f = malloc(sizeof(numC));
  makeString(f->type, "numC");
  f->numVal = 0;

  numC *g = malloc(sizeof(numC));
  makeString(g->type, "numC");
  g->numVal = -1;

  ifC *i = malloc(sizeof(ifC));
  makeString(i->type, "ifC");
  i->test = e;
  i->then = f;
  i->els = g;



  printf("%lf\n", interp(i)->numVal);
  return 0;
}
