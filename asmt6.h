typedef struct Binop {
   char *type;
   char *operator;
   void *bozor1;
   void *bozor2;
} Binop;

typedef struct NumC {
   char *type;
   double numVal;
} NumC;

typedef struct ifC {
   char *type;
   void *test;
   void *then;
   void *els;
} ifC;

typedef struct idC {
   char *type;
   char *id;
} idC;

typedef struct boolC {
   char *type;
   int val;
} boolC;



