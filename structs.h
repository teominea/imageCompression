/* MINEA TEODORA-MARIA, 311CB */
#include <stdio.h>
#include <stdlib.h>

typedef struct rgb {
    unsigned char red, green, blue;
} RGB;

typedef struct nod {
    RGB info;
    unsigned char tip;
    unsigned int size;
    struct nod *fiu1, *fiu2, *fiu3, *fiu4;
}TNod, *TArbore;

typedef struct celula {
  TArbore info;
  struct celula *urm;
} TCelula, *TLista;


typedef struct coada {
  TLista inc, sf; /* adresa primei si ultimei celule */
} TCoada;

TCoada *InitQ();
int ExtrQ(TCoada *c, TArbore *x);
int IntrQ(TCoada *c, TArbore x);
void DistrQ(TCoada **c);
void AfisareQ(TCoada *c);

TArbore Constr_frunza();
TArbore Constr_nod(RGB x, TArbore f1, TArbore f2, TArbore f3, TArbore f4);
unsigned long long sum_red(RGB **mat, int size, int x, int y);
unsigned long long sum_green(RGB **mat, int size, int x, int y);
unsigned long long sum_blue(RGB **mat, int size, int x, int y);
unsigned long long calc_mean(RGB **mat, unsigned long long sum_r,
unsigned long long sum_g, unsigned long long sum_b, int size, int x, int y);
TArbore Constr_arbore(RGB **mat, int x, int y, int size, int factor);
int nr_frunze(TArbore r);
int niv_max(TArbore r);
void max_size(TArbore r, unsigned int *size, TCoada *c);
void parcurgere_nivel(TCoada *c, FILE *out);
void initializare(TArbore arb, TCoada *c);
unsigned int file_size(TArbore arb);
TCoada *citire(FILE *inp);
TArbore make_arb(TCoada *c, unsigned int size);
RGB ** deconstr_arb(TArbore arb, RGB **mat, int x, int y, int size);
void dezaloca_arb(TArbore a);
void distr_arb(TArbore *a);
void dezaloca_mat(RGB** mat, int size);
