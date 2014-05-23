#include <stdio.h>

int evalIfC(ifC* ifc) {
   if (interp(ifc->test))->numVal == 1) {
      return ifc->then;
   }
   else 
      return ifc->els
}
