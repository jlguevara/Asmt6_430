#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "LinkedList.h"

/* mini interpreter */

/* core syntax */
typedef enum {
    numC,
    boolC,
    idC,
    ifC,
    appC,
    binopC,
    lamC,
    numV,
    closV,
    boolV
} Type;

typedef struct {
    Type type;
    double n;
} NumC;

typedef struct {
    Type type;
    char *v;
} BoolC;

typedef struct {
    Type type;
    char *name;
} IdC;

typedef struct {
    Type type;
    void *test;
    void *then;
    void *othewise;
} IfC;

typedef struct {
    Type type;
    void *fun;
    void *arg;
} AppC;

typedef struct {
    Type type;
    char *op;
    void *left;
    void *right;
} BinopC;

typedef struct {
    Type type;
    char *param;
    void *body;
} LamC;

typedef struct {
    Type type;
    double n;
} NumV;

typedef struct {
    Type type;
    char *param;
    void *body;
    LinkedList *env;
} ClosV;

typedef struct {
    Type type;
    char *v;
} BoolV;

typedef struct {
    char *name;
    void *value;
} Binding;

// clones a value to be used by the cloned list
void *cloneValue(void *val) {
    NumV *nValue;
    BoolV *bValue;
    ClosV *cValue;

    switch(*(int *) val) {
        case closV:
            cValue = malloc(sizeof(ClosV));
            cValue->type = closV;
            strcpy(cValue->param, ((ClosV *)val)->param);
            cValue->body = ((ClosV *) val)->body;
            cValue->env = LinkedList_clone(((ClosV *) val)->env);
            return cValue;
            break;
        case numV:
            nValue = malloc(sizeof(NumV));
            nValue->type = numV;
            nValue->n = ((NumV *)val)->n;
            return nValue;
            break;
        case boolV:
            bValue = malloc(sizeof(BoolV));
            bValue->type = boolV;
            strcpy(bValue->v, ((BoolV *)val)->v);
            return bValue;
            break;
        default:
            printf("cloneValue: unsupported value");
            return NULL;
    }
}

// used to clone binding in a list
void *cloneBinding(void *og) {
    Binding *old = (Binding *)og;
    Binding *result = malloc(sizeof(Binding));
    result->name = malloc(sizeof(old->name));
    strcpy(result->name, old->name);
    result->value = cloneValue(old->value);
    return result;
}

// used to compare bindings in a list
int compare(void *b1, void *b2) {
    char *n1 = ((Binding *)b1)->name;
    char *n2 = ((Binding *)b2)->name;

    return strcmp(n1, n2);
}

// compute a binary operation, currently limited to +, -, *, /
void *interpBinop(char *op, void *left, void *right) {
    if (op == NULL || left == NULL || right == NULL) {
        printf("binop: null values not allowed\n");
        return NULL;
    }

    if (*(int *)left != numV || *(int *)right != numV) {
        printf("binop: I only take numbers right now\n");
        return NULL;
    }
    
    NumV *lNum = left;
    NumV *rNum = right;
    NumV *result = malloc(sizeof(NumV));
    result->type = numV;

    if (*op == '+')
        result->n = lNum->n + rNum->n;
    else if (*op == '-')
        result->n = lNum->n - rNum->n;
    else if (*op == '*')
        result->n = lNum->n * rNum->n;
    else if (*op == '/') {
        if (rNum->n == 0) {
            printf("division by zero not allowed!\n");
            return NULL;
        }
        result->n = lNum->n / rNum->n;
    }
    else {
        printf("unsuppored operation\n");
        return NULL;
    }
    return result;
}

// interpret an "ExprC" and return a "Value"
void *interp(void *e, LinkedList *env) {
    if (e == NULL) {
        printf("interp: got nothing\n"); 
        return NULL;
    }

    Binding *binding;
    NumV *numResult;
    BoolV *boolResult;
    BinopC *bc;
    ClosV *closure;
    LamC *lambda;
    AppC *app;

    // switch on type
    switch (*(int *)e) {
        case idC:
            binding = malloc(sizeof(Binding));
            binding->name = ((IdC *) e)->name;
            binding = LinkedList_lookup(env, binding);
            if (binding == NULL) {
                printf("interp: didn't find variable %s\n", binding->name);
                return NULL;
            }
            return binding->value;
            break;
        case numC:
            numResult = malloc(sizeof(NumV));
            numResult->type = numV;
            numResult->n = ((NumC *) e)->n;
            return numResult;
            break;
        case boolC:
            boolResult = malloc(sizeof(BoolV));
            boolResult->type = boolV;
            boolResult->v = ((BoolC *)e)->v;
            return boolResult;
            break;
        case binopC:
            bc = (BinopC *) e;
            void *left = interp(bc->left, LinkedList_clone(env));
            void *right = interp(bc->right, LinkedList_clone(env));
            return interpBinop(bc->op, left, right); 
            break;
        case lamC:
            lambda = (LamC *) e;
            closure = malloc(sizeof(ClosV));
            closure->type = closV;
            closure->param = malloc(sizeof(strlen(lambda->param)));
            strcpy(closure->param, lambda->param);
            closure->body = lambda->body;
            closure->env = LinkedList_clone(env);
            return closure;
            break;
        case appC:
            app = (AppC *) e;
            closure = interp(app->fun, env);
            if (closure == NULL || closure->type != closV) {
                printf("interp: appC got a non-function.\n");
                return NULL;
            } 

            binding = malloc(sizeof(Binding));
            binding->name = malloc(sizeof(strlen(closure->param)));
            strcpy(binding->name, closure->param); 
            binding->value = cloneValue(interp(app->arg, env));


            LinkedList_add(closure->env, binding);
            return interp(closure->body, closure->env); 
            break;
        default:
            printf("interp: unable to decipher your expression");
            return NULL;
    }
}

/* test {{{fn {x} {fn {y} {+ x y}}} 3} 7} */
void testClosures() {
    char *varName1 = "X";
    char *varName2 = "Y";
    char *op = "+";

    IdC idX = {idC, varName1};
    IdC idY = {idC, varName2};
    BinopC binop = {binopC, op, &idX, &idY};
    LamC innerLam = {lamC, varName2, &binop};
    LamC outerLam = {lamC, varName1, &innerLam};

    NumC arg1 = {numC, 3};
    AppC app1 = {appC, &outerLam, &arg1};

    NumC arg2 = {numC, 7};
    AppC app2 = {appC, &app1, &arg2};
    LinkedList *env = LinkedList_create(compare, cloneBinding);

    NumV *result = interp(&app2, env);

    assert(result->type == numV);
    assert(result->n == 10); 
}

void testAppC() {
    char *varName = "X";
    char *op = "*";

    IdC id = {idC, varName};
    BinopC binop = {binopC, op, &id, &id};
    LamC lambda = {lamC, varName, &binop};

    NumC arg = {numC, 7};
    AppC app = {appC, &lambda, &arg};
    LinkedList *env = LinkedList_create(compare, cloneBinding);

    NumV *result = interp(&app, env);
    assert(result->type == numV);
    assert(result->n == 49); 
}

void testLambda() {
    char *varName = "X";
    IdC id = {idC, varName};
    
    char *op = "*";
    BinopC binop = {binopC, op, &id, &id};

    LamC lambda = {lamC, varName, &binop};
    ClosV *closure = interp(&lambda, NULL);
    
    assert(closure->type == closV);
    assert(!strcmp(closure->param, varName));
    assert(closure->body == &binop);
    assert(closure->env == NULL);
}

void testInterp() {
    NumC *num = malloc(sizeof(NumC));
    num->n = 7;
    num->type = numC;
    assert(((NumV *)interp(num, NULL))->n == num->n);

    BoolC *boolean = malloc(sizeof(BoolC));
    boolean->type = boolC;
    boolean->v = "true";
    assert(!strcmp(((BoolV *)interp(boolean, NULL))->v, boolean->v));
}

void testInterpBinop() {
    char op = '+';
    NumV *result;

    NumV *x = malloc(sizeof(NumV));
    x->type = numV;
    x->n = 4;

    NumV *y = malloc(sizeof(NumV));
    y->type = numV;
    y->n = 2;

   result = interpBinop(&op, x, y);
   assert(result->n == 6);

   op = '-';
   result = interpBinop(&op, x, y);
   assert(result->n == 2);

   op = '*';
   result = interpBinop(&op, x, y);
   assert(result->n == 8);

   op = '/';
   result = interpBinop(&op, x, y);
   assert(result->n == 2);

   y->n = 0;
   result = interpBinop(&op, x, y);
   assert(result == NULL);
}

// master test function
int main() {
    testInterp();
    testInterpBinop();
    testLambda();
    testAppC();
    testClosures();
}
