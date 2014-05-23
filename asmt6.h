typedef struct binopC {
   char *type;
   char *operator;
   void *bozor1;
   void *bozor2;
} binopC;

typedef struct numC {
   char *type;
   double numVal;
} numC;

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

typedef struct numV {
  char *type;
  double numVal;
} numV;
