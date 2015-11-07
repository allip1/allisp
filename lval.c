
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lval {
  int type;
  long num;
  char* err;
  char* sym;

  int count;
  struct lval** cell;
} lval;

enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };




lval* lval_ctr(int type) {
  lval* v = malloc(sizeof(lval));
  v->type = type;
  return v;
}

lval* lval_num(long x) {
  lval* v = lval_ctr(LVAL_NUM);
  v->num = x;
  return v;
}

/* Create a new error type lval */
lval* lval_err(char* m) {
  lval* v = lval_ctr(LVAL_ERR);
  v->err = malloc(strlen(m)+1);
  strcpy(v->err, m);
  return v;
}

lval* lval_sym(char* s) {
 lval* v = lval_ctr(LVAL_SYM);
 v->sym = malloc(strlen(s) + 1);
 strcpy(v-> sym, s);
 return v;
}

lval* lval_sexpr(void){
  lval* v = lval_ctr(LVAL_SEXPR);
  v->count = 0;
  v->cell = NULL;

 return v;
}


lval* lval_qexpr(void){
  lval* v = lval_ctr(LVAL_QEXPR);
  v->count = 0;
  v->cell = NULL;
  return v;
}

void lval_del(lval* v) {

  switch (v->type) {
    /* Do nothing special for number type */
    case LVAL_NUM: break;

    /* For Err or Sym free the string data */
    case LVAL_ERR: free(v->err); break;
    case LVAL_SYM: free(v->sym); break;

    /* If Sexpr then delete all elements inside */
    case LVAL_SEXPR:
    case LVAL_QEXPR:
      for (int i = 0; i < v->count; i++) {
        lval_del(v->cell[i]);
      }
      /* Also free the memory allocated to contain the pointers */
      free(v->cell);
    break;
  }

  /* Free the memory allocated for the "lval" struct itself */
  free(v);
	}
