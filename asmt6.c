#include <stdio.h>


int evalBinop(binopC* binop) {
   if (strcmp(binop->operator, "+") == 0) {
      return binop->bozor1 + binop->bozor2;
      //note, must eval these binops later
   }
   else if (strcmp(binop->operator, "-") == 0) {
      return binop->bozor1 - binop->bozor2;
   }
   else if (strcmp(binop->operator, "*") == 0) {
      return binop->bozor1 * binop->bozor2;
   }
   else if (strcmp(binop->operator, "/") == 0) {
      return binop->bozor1 / binop->bozor2;
   }
   else if (strcmp(binop->operator, "<=") == 0) {
      return binop->bozor1 <= binop->bozor2;
   }
   else if (strcmp(binop->operator, "eq?") == 0) {
      return binop->bozor1 == binop->bozor2;
   }

}

