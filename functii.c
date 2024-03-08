/* MINEA TEODORA-MARIA, 311CB */
#include "structs.h"

TCoada *InitQ() {
    /* creeaza coada vida cu elemente de dimensiune d;*/
    TCoada *c = NULL; /* spatiu pentru descriptor coada */
    c = (TCoada *)malloc(sizeof(TCoada));
    if (!c)
        return NULL; /* nu exista spatiu -> "esec" */

    c->inc = c->sf = NULL;
    return c; /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, TArbore nod) {
    /* adauga element la sfarsitul cozii */
    TLista aux = NULL;
    aux = (TLista)malloc(sizeof(TCelula)); /* aloca o noua celula */
    if (!aux)
        return 0; /* functia returneaza 0 daca celula nu s-a putut aloca */

    aux->info = nod;
    aux->urm = NULL;

    if (c->sf != NULL)    /* coada nevida */
        c->sf->urm = aux; /* -> leaga celula dupa ultima din coada */
    else                  /* coada vida */
        c->inc = aux;
    c->sf = aux;
    return 1; /* functia returneaza 1 daca s-a introdus celula cu succes */
}

int ExtrQ(TCoada *c, TArbore *x) {
    /* extrage primul element din coada la adresa spcificata */
    TLista aux = NULL;
    if (c->inc == NULL) {
        return 0;
    } else {
        if (c->inc == c->sf) {
            *x = c->inc->info;
            aux = c->inc;
            c->inc = NULL;
            c->sf = NULL;
            free(aux);
        } else {
            *x = c->inc->info;
            aux = c->inc;
            c->inc = c->inc->urm;
            free(aux);
        }
    }
    return 1;
}

void DistrQ(TCoada **c) { /* distruge coada */
    TLista p = NULL, aux = NULL;
    p = (*c)->inc;
    while (p) {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*c);
    *c = NULL;
}


TArbore Constr_frunza() {
    /* aloca un nou nod de tip arbore */
    TArbore aux = (TArbore) malloc (sizeof(TNod));
    /* daca alocarea nu a reusit, functia va returna NULL */
    if (!aux) return NULL;
    /* tipul nodului va fi 1, deoarece este frunza */
    aux->tip = 1;
    /* toate informatiile referitoare la culoare vor fi setate cu 0 */
    aux->info.red = 0;
    aux->info.green = 0;
    aux->info.blue = 0;
    /* toti cei 4 fii vor fi NULL */
    aux->fiu1 = aux->fiu2 = aux->fiu3 = aux->fiu4 = NULL;
    return aux;
}

/* functie pentru eliberarea memoriei dintr-un arbore */
void dezaloca_arb(TArbore a) {
    /* daca arborele nu mai exista, ne oprim */
    if (!a) return;
    /* se apeleaza recursiv functia pentru cei 4 fii,
    parcurgand arborele in adancime */
    dezaloca_arb(a->fiu1);
    dezaloca_arb(a->fiu2);
    dezaloca_arb(a->fiu3);
    dezaloca_arb(a->fiu4);
    /* se elibereaza memoria pentru nodul curent */
    free(a);
}

/* functie pentru eliberarea memoriei arborelui si setarea radacinii
pe NULL */
void distr_arb(TArbore *a) {
    /* daca arborele este deja NULL, iesim din functie */
    if (!(*a)) return;
    /* apelam functia dezaloca_arb pentru a elibera memoria din toti subarborii */
    dezaloca_arb(*a);
    /* setam radacina pe NULL */
    *a = NULL;
}

/* functie pentru eliberarea memoriei din matricea de pixeli */
void dezaloca_mat(RGB** mat, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        /* eliberam memoria pentru fiecare linie din matrice */
        free(mat[i]);
    }
    /* eliberam matricea */
    free(mat);
}
/* functie pentru calculul mediei aritmetice din submatricea de pixeli
pentru blocul de culoare rosie */
unsigned long long sum_red(RGB **mat, int size, int x, int y) {
    unsigned long long sum_r = 0;
    /* folosind formula descrisa in enuntul temei, am calculat suma tuturor
    pixelilor de culoare rosie din submatricea care incepe de la indicii x si y */
    int i = 0, j = 0;
    for (i = x; i < x + size; i++) {
        for (j = y; j< y + size; j++) {
            sum_r = sum_r + (unsigned long long)(mat[i][j].red);
        }
    }
    /* am impartit suma rezultata la aria blocului de culoare verificat */
    sum_r = sum_r / (size * size);
    return sum_r;
}
/* functie pentru calculul mediei aritmetice din submatricea de pixeli
pentru blocul de culoare verde */
unsigned long long sum_green(RGB **mat, int size, int x, int y) {
    unsigned long long sum_g = 0;
    /* folosind formula descrisa in enuntul temei, am calculat suma tuturor
    pixelilor de culoare rosie din submatricea care incepe de la indicii x si y */
    int i = 0, j = 0;
    for (i = x; i < x + size; i++) {
        for (j = y; j< y + size; j++) {
            sum_g = sum_g + (unsigned long long)mat[i][j].green;
        }
    }
    /* am impartit suma rezultata la aria blocului de culoare verificat */
    sum_g = sum_g / (size * size);
    return sum_g;
}
/* functie pentru calculul mediei aritmetice din submatricea de pixeli
pentru blocul de culoare albastra */
unsigned long long sum_blue(RGB **mat, int size, int x, int y) {
    unsigned long long sum_b = 0;
    /* folosind formula descrisa in enuntul temei, am calculat suma tuturor
    pixelilor de culoare rosie din submatricea care incepe de la indicii x si y */
    int i = 0, j = 0;
    for (i = x; i < x + size; i++) {
        for (j = y; j< y + size; j++) {
            sum_b = sum_b + (unsigned long long)mat[i][j].blue;
        }
    }
    /* am impartit suma rezultata la aria blocului de culoare verificat */
    sum_b = sum_b / (size * size);
    return sum_b;
}

/* functie pentru calculul scorul similaritatii dintr-o submatrice
de pixeli */
unsigned long long calc_mean(RGB **mat, unsigned long long sum_r,
unsigned long long sum_g, unsigned long long sum_b, int size, int x, int y) {
    unsigned long long mean = 0;
    /* folosind formula descrisa in enuntul temei am calculat scorul similaritatii 
    pentru blocul care incepe de la indicii x si y*/
    int i = 0, j = 0;
    for (i = x; i < x + size; i++) {
        for (j = y; j< y + size; j++) {
            mean = mean + (sum_r - (unsigned long long)mat[i][j].red)*(sum_r - (unsigned long long)mat[i][j].red);
            mean = mean + (sum_g - (unsigned long long)mat[i][j].green)*(sum_g - (unsigned long long)mat[i][j].green);
            mean = mean + (sum_b - (unsigned long long)mat[i][j].blue)*(sum_b - (unsigned long long)mat[i][j].blue);
        }
    }

    mean = mean / (unsigned long long)(size * size * 3);
    return mean;
}

TArbore Constr_arbore(RGB **mat, int x, int y, int size, int factor) {
    /* alocam arborele initial care va fi de tip frunza */
    TArbore arb = Constr_frunza();
    /* daca alocarea nu a avut succes, iesim din functie */
    if (!arb) return NULL;
    /* folosind functia descrisa anterior, calculam media artmetica pentru blocul de
    culoare rosie din matricea de pixeli, avand ca parametri indicii de pozitie
    pentru blocul actual si dimensiunea lungimii acestuia */
    unsigned long long red = sum_red(mat, size, x, y);
    /* folosind functia descrisa anterior, calculam media artmetica pentru blocul de
    culoare verde din matricea de pixeli, avand ca parametri indicii de pozitie
    pentru blocul actual si dimensiunea lungimii acestuia */
    unsigned long long green = sum_green(mat, size, x, y);
    /* folosind functia descrisa anterior, calculam media artmetica pentru blocul de
    culoare albastra din matricea de pixeli, avand ca parametri indicii de pozitie
    pentru blocul actual si dimensiunea lungimii acestuia */
    unsigned long long blue = sum_blue(mat, size, x, y);
    /* folosind functia descrisa anterior, calculam scorul similaritatii pentru blocul
    delimitat de x si y de lungime "size", utilizand mediile aritmetice calculate anterior*/
    unsigned long long mean = calc_mean(mat, red, green, blue, size, x, y);
    /* daca scorul calculat este mai mic sau egal decat factorul primit ca parametru,
    atunci nu este nevoie ca nodul sa se mai ramifice, deci va ramane frunza */
    if (mean <= factor) {
        /* tipul arborelui va fi 1 */
        arb->tip = 1;
        /* retinem in arb->info informatiile despre fiecare bloc de culoare calculat folosind
        media aritmetica */
        arb->info.red = (unsigned char)red;
        arb->info.green = (unsigned char)green;
        arb->info.blue = (unsigned char)blue;
        /* retinem in arb->size lungimea actuala a blocului de culoare */
        arb->size = (unsigned int)size;
    } else {
        /* daca scorul este mai mare arborele se va ramifica */
        /* tipul arborelui va fi 0 */
       arb->tip = 0;
       /* retinem in arb->size lungimea actuala a blocului de culoare */
       arb->size = (unsigned int) size;
       /* apelam recursiv functia pentru primul fiu al arborelui, plecand de la aceleasi coordonate pentru
       linie si coloana si dimensiunea injumatatita (adica primul sfert al patratului) */
       arb->fiu1 = Constr_arbore(mat, x, y, size/2, factor);
       /* apelam recursiv functia pentru al doilea fiu al arborelui, plecand de la aceeasi coordonata pentru
       linie, iar pentru coloana se va deplasa cu size/2 coordonata si dimensiunea va fi injumatatita
       (adica al doilea sfert al patratului) */
       arb->fiu2 = Constr_arbore(mat, x, y + size/2, size/2, factor);
       /* apelam recursiv functia pentru al treilea fiu al arborelui, pentru linie si
       pentru coloana se va deplasa cu size/2 coordonata, iar dimensiunea va fi injumatatita
       (adica al treilea sfert al patratului) */
       arb->fiu3 = Constr_arbore(mat, x + size/2, y + size/2, size/2, factor);
       /* apelam recursiv functia pentru al patrulea fiu al arborelui, plecand de la aceeasi coordonata pentru
       coloana, iar pentru linie se va deplasa cu size/2 coordonata si dimensiunea va fi injumatatita
       (adica al patrulea sfert al patratului) */
       arb->fiu4 = Constr_arbore(mat, x + size/2, y, size/2, factor);
    }
    /* returneaza arborele */
    return arb;
}


/* functie pentru calculul numarului de frunze */
int nr_frunze(TArbore r) {
/* daca nodul este NULL functia returneaza 0 */
if (r == NULL) return 0;
/* daca toti fii nodului cercetat sunt NULL, inseamna ca nodul este frunza,
deci functia va returna 1 */
if (r->fiu1 == NULL && r->fiu2 == NULL && r->fiu3 == NULL && r->fiu4 == NULL) {
return 1;
}
/* initializam un contor in care vom retine numarul total de frunze */
int contor = 0;
/* apelam recursiv functia pentru toti cei 4 fii ai nodului, adaugand rezultatul
la contor */
contor += nr_frunze(r->fiu1);
contor += nr_frunze(r->fiu2);
contor += nr_frunze(r->fiu3);
contor += nr_frunze(r->fiu4);

return contor;
}

/* functie pentru determinarea numarului macim de nivele dintr-un arbore */
int niv_max(TArbore r) {
/* daca nodul este NULL functia va returna 0 */
if (r == NULL) {
return 0;
}
/* in f1 vom retine nivelul returnat pentru subarborele din fiul 1
in f2 vom retine nivelul returnat pentru subarborele din fiul 2
in f3 vom retine nivelul returnat pentru subarborele din fiul 3
in f4 vom retine nivelul returnat pentru subarborele din fiul 4
 */
/* apelam recursiv functia pentru toti cei 4 fii */
int f1 = niv_max(r->fiu1);
int f2 = niv_max(r->fiu2);
int f3 = niv_max(r->fiu3);
int f4 = niv_max(r->fiu4);
/* daca valoarea returnata pentru subarborele din fiul 1 este mai mare 
decat celelalte functia va returna valoarea lui f1+1
(pentru a include si nodul parinte) */
if(f1 >= f2 && f1 >= f3 && f1 >= f4) return f1+1;
/* daca valoarea returnata pentru subarborele din fiul 1 este mai mare 
decat celelalte functia va returna valoarea lui f2+1
(pentru a include si nodul parinte) */
if(f2 >= f1 && f2 >= f3 && f2 >= f4) return f2+1;
/* daca valoarea returnata pentru subarborele din fiul 1 este mai mare 
decat celelalte functia va returna valoarea lui f3+1
(pentru a include si nodul parinte) */
if(f3 >= f2 && f3 >= f2 && f3 >= f4) return f3+1;
/* daca valoarea returnata pentru subarborele din fiul 1 este mai mare 
decat celelalte functia va returna valoarea lui f4+1
(pentru a include si nodul parinte) */
if(f4 >= f2 && f4 >= f3 && f4 >= f1) return f4+1;
}

/* functie pentru initializarea cozii */
void initializare(TArbore arb, TCoada *c) {
    /* daca arborele este NULL, vom iesi din functie */
    if (arb == NULL) return;
    /* daca nu este NULL, vom introduce arborele in coada */
    if (arb != NULL) {
        IntrQ(c, arb);
    }
}

/* functie pentru parcurgerea arborelui pe nivel si afisarea elementelor in
fisierul de output */
void parcurgere_nivel(TCoada *c, FILE *out) {
    /* am initializat variabila ok pentru a retine daca am scris dimensiunea initiala
    a imaginii */
    int ok = 0;
    TArbore aux = NULL;
    /* cat timp coada nu este vida, vom efectua urmatoarele operatii */
    while (c->inc != NULL) {
        /* extragem un nod din coada */
        ExtrQ(c, &aux);
        if (ok == 0) {
        /* cum primul element este radacina, iar aceasta retine in arb->size
        dimensiunea imaginii, vom afisa in fisier dimensiunea imaginii */
            unsigned int size = aux->size;

            fwrite (&size, sizeof(unsigned int), 1, out);
            /* ok va deveni 1, pentru a nu mai intra in acest if in viitor */
            ok = 1;
        }
        /* daca nodul extras este intern, introduce toti fii sai in coada si scriem in
        fisier tipul acestuia */
        if (aux->tip == 0) {
            fwrite (&aux->tip, sizeof(unsigned char), 1, out);
            IntrQ(c, aux->fiu1);
            IntrQ(c, aux->fiu2);
            IntrQ(c, aux->fiu3);
            IntrQ(c, aux->fiu4);
        }
        /* daca nodul este frunza, vom scrie in fisier tipul nodului si informatiile de culoare
        in ordinea red, green, blue */
        if (aux->tip == 1) {
            fwrite (&aux->tip, sizeof(unsigned char), 1, out);
            fwrite (&aux->info.red, sizeof(unsigned char), 1, out);
            fwrite (&aux->info.green, sizeof(unsigned char), 1, out);
            fwrite (&aux->info.blue, sizeof(unsigned char), 1, out);
        }
    }
}

/* functie pentru determinarea blocului de culoare cu dimensiunea maxima */
void max_size(TArbore r, unsigned int *size, TCoada *c) {
    TArbore aux = NULL;
    /* cat timp coada este nevida vom efectua urmatoarele operatii */
    while (c->inc != NULL) {
        /* extragem un nod din coada */
        ExtrQ(c, &aux);
        /* daca este nod intern, adaugam fii sai in coada */
        if (aux->tip == 0) {
            IntrQ(c, aux->fiu1);
            IntrQ(c, aux->fiu2);
            IntrQ(c, aux->fiu3);
            IntrQ(c, aux->fiu4);
        }
        /* daca este nod intern, vom retine dimensiunea in "size" si vom iesi din
        functie, intrucat ne intereseaza sa gasim prima frunza pentru a afla
        dimensiunea maxima a blocului de culoare */
        if (aux->tip == 1) {
            *size = aux->size;
            return;
        }
    }
}
/* functie pentru citirea informatiilor din fisierul de input */
TCoada *citire(FILE *inp) {
    /* calculam dimensiunea fisierului folosind functiile fseek si ftell */
    fseek(inp, 0, SEEK_END);
    long dim = ftell(inp);
    fseek(inp, 0, SEEK_SET);
    unsigned int size = 0;
    /* citim dimensiunea imaginii din fisier */
    fread(&size, sizeof(unsigned int), 1, inp);
    /* initializam coada in care vor fi retinute informatiile despre noduri */
    TCoada * c = InitQ();
    /* in vectorul v alocat dinamic vom citi informatiile folosind functia fread */
    unsigned char *v = (unsigned char*) malloc (sizeof (unsigned char)*(dim));
    /* dimensiunea vectorului care va contine unsigned char-urile citie din fisier va fi
    dim - sizeof(unsigned int) deoarece am scazut dimensiunea lui size, citit anterior */
    int i = 0;
    for (i = 0; i < dim-sizeof(unsigned int); i++) {
        fread(&v[i], sizeof(unsigned char), 1, inp);
    }
    /* parcurgem vectorul in care am retinut informatiile */
    for (i = 0; i< dim-sizeof(unsigned int); i++) {
        /* daca v[i] este 0, inseamna ca nodul este intern */
        if (v[i] == 0) {
            TArbore arb = NULL;
            /* initializam nodul (cu tipul 0) si il introducem in coada */
            arb = Constr_frunza();
            arb->tip = 0;
            IntrQ(c, arb);
        /* daca v[i] este 1, inseamna ca nodul este frunza */
        } else if (v[i] ==  1) {
            TArbore arb = NULL;
            arb = Constr_frunza();
            /* initializam nodul (cu tipul 1), iar in arb->info retinem informatiile pentru
            culori, care vor fi date de  v[i+1], v[i+2] si v[i+3]  */
            arb->tip = 1;
            arb->info.red = v[i+1];
            arb->info.green = v[i+2];
            arb->info.blue = v[i+3];
            /* introducem nodul in coada */
            IntrQ(c, arb);
            /* il crestem pe i cu 3 pozitii pentru a sari peste cele 3 valori de red, green si
            blue folosite */
            i = i+3;
        }
    }
    /* eliberam memoria pentru v, iar la final functia returneaza coada */
    free(v);
    return c;
}

/* functie care reface arborele plecand de la parcurgerea pe nivel */
TArbore make_arb(TCoada *c, unsigned int size) {
    /* am initializat coada auxiliara c2, pentru a ma ajuta in constructia arborelui */
    TCoada *c2 = InitQ();
    TArbore arb = NULL;
    TArbore tree = NULL;
    /* extragem primul nod din coada initiala */
    ExtrQ(c, &tree);
    /* dimensiunea radacinii va fi dimensiunea citita din fisier */
    tree->size = size;
    /* introducem nodul in cauza auxiliara */
    IntrQ(c2, tree);
    /* cat timp coada initiala este nevida efectuam urmatoarele operatii */
    while (c->inc != NULL) {
    /* cat timp coada initiala este nevida efectuam urmatoarele operatii */
    while (c2->inc != NULL) {
        /* extragem un nod din coada auxiliara */
        ExtrQ(c2, &arb);
        /* daca nodul este intern vom extrage din coada initiala fii acestuia */
        if (arb->tip == 0) {
            /* dimensiunea lungimii blocului de imagine al fiilor va fi jumatate
            din dimensiunea blocului de imagine a parintelui */
            size = size/2;
            /* extragem fiul 1 din coada initiala */
            ExtrQ(c, &arb->fiu1);
            /* actualizam dimensiunea fiului 1 */
            arb->fiu1->size = size;
            /* introducem fiul 1 in coada auxiliara */
            IntrQ(c2, arb->fiu1);
            /* extragem fiul 2 din coada initiala */
            ExtrQ(c, &arb->fiu2);
            /* actualizam dimensiunea fiului 2 */
            arb->fiu2->size = size;
            /* introducem fiul 2 in coada auxiliara */
            IntrQ(c2, arb->fiu2);
            /* extragem fiul 3 din coada initiala */
            ExtrQ(c, &arb->fiu3);
            /* actualizam dimensiunea fiului 3 */
            arb->fiu3->size = size;
            /* introducem fiul 3 in coada auxiliara */
            IntrQ(c2, arb->fiu3);
            /* extragem fiul 4 din coada initiala */
            ExtrQ(c, &arb->fiu4);
            /* actualizam dimensiunea fiului 4 */
            arb->fiu4->size = size;
            /* introducem fiul 4 in coada auxiliara */
            IntrQ(c2, arb->fiu4);
        }
        /* daca nodul este frunza, setam toti fii pe NULL */
        if (arb->tip == 1) {
            arb->fiu1 = arb->fiu2 = arb->fiu3 = arb->fiu4 = NULL;
        }
    }
    }
    /* distrugem coada auxiliara */
    DistrQ(&c2);
    return tree;
}

/* functie care returneaza matricea de pixeli plecand de la un arbore cuaternar */
RGB **deconstr_arb(TArbore arb, RGB **mat, int x, int y, int size) {
    /* daca arborele este NULL, va returna matricea */
    if (arb == NULL) return mat;
    /* daca nodul actual este intern, se va apela recursiv functia pentru cei 4 fii ai sai */
    if (arb->tip == 0) {
        /* adaugam in matrice informatiile din subarborele reprezentat de fiul 1,
        avand aceleasi coordonate x si y si dimensiunea injumatatita (cautam in primul
        sfert al patratului) */
        mat = deconstr_arb(arb->fiu1, mat, x, y, size/2);
        /* adaugam in matrice informatiile din subarborele reprezentat de fiul 2,
        avand aceeasi coordonata x, y devine y + size/2, iar dimensiunea se injumatateste 
        (cautam in al doilea sfert al patratului) */
        mat = deconstr_arb(arb->fiu2, mat, x , y + size/2, size/2);
        /* adaugam in matrice informatiile din subarborele reprezentat de fiul 3,
        x devine x + size/2, y devine y+size/2, iar dimensiunea se injumatateste (cautam
        in al treilea sfert al patratului) */
        mat = deconstr_arb(arb->fiu3, mat, x + size/2, y + size/2, size/2);
        /* adaugam in matrice informatiile din subarborele reprezentat de fiul 4,
        avand aceeasi coordonata y, x devine x + size/2, iar dimensiunea se injumatateste  */
        mat = deconstr_arb(arb->fiu4, mat, x + size/2, y, size/2);
    }
    /* daca nodul este frunza se vor retine in matricea de pixeli informatiile de tip red, green si blue
    din zona imaginii de dimensiune size*size si coordonate x si y */
    if (arb->tip == 1) {
        int i = 0, j = 0;
        for (i = x; i < x + size; i++) {
            for (j = y; j < y + size; j++) {
                mat[i][j].red = arb->info.red;
                mat[i][j].green = arb->info.green;
                mat[i][j].blue = arb->info.blue;
            }
        }
    }
    /* returneaza matricea */
return mat;
}
