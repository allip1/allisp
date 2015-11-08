
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;


typedef lval*(*lbuiltin)(lenv*, lval*);

struct lval {
  int type;

  long num;
  char* err;
  char* sym;
  lbuiltin fun;

  int count;
  lval** cell;
};


struct lenv {
  int count;
  char** syms;
  lval** vals;
};


enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN };


lval* lval_ctr(int t);
lval* lval_num(long n);
lval* lval_err(char* e);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_fun(lbuiltin func);

void lval_del(lval* v);

void lval_print(lval* v);
void lval_expr_print(lval* v, char open, char closed);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
lval* lval_add(lval* v, lval* x);
lval* lval_copy(lval* v);



lenv* lenv_new(void);
void lenv_del(lenv* e);

lval* lenv_get(lenv* e, lval* k);
void lenv_put(lenv* e, lval* k, lval* v);

