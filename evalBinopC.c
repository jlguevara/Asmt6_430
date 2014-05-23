#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asmt6.h"


numV* evalBinop (binopC *binop) {
   numV *numV1, *numV2, *val = malloc(sizeof(numV));
   char *msg = malloc(5);
   strcpy(msg, "numV");

   val->type = msg;
   if (strcmp(binop->operator, "+") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal + numV2->numVal;
      //note, must eval these binops later
   }
   else if (strcmp(binop->operator, "-") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal - numV2->numVal;
   }
   else if (strcmp(binop->operator, "*") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal * numV2->numVal;
   }
   else if (strcmp(binop->operator, "/") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal / numV2->numVal;
   }
   else if (strcmp(binop->operator, "<=") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal <= numV2->numVal;

   }
   else if (strcmp(binop->operator, "eq?") == 0) {
      numV1 = interp(binop->bozor1);
      numV2 = interp(binop->bozor2);
      val->numVal = numV1->numVal == numV2->numVal;
   }

   return val;
}

