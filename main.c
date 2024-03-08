/* MINEA TEODORA-MARIA, 311CB */
#include <string.h>
#include "structs.h"
#define ONE_HUNDRED 100
#define culoare 255



int main(int argc, char const *argv[]) {
    /* se verifica daca primul parametru din linia de comanda este "-c1",
    pentru a rezolva prima cerinta */
    if (strncmp(argv[1], "-c1\n", 3) == 0) {
        /* se deschide fisierul de input (in format binar) care este reprezentat
        de al treilea parametru in linia de comanda  */
        FILE *inp = fopen(argv[3], "rb");
        /* se deschide fisierul de input (in format text) care este reprezentat
        de al patrulea parametru in linia de comanda  */
        FILE *out = fopen(argv[4], "wt");
        /* daca fisierul de input nu s-a putut deschide, iesim din functie */
        if (!inp)
            return -1;
        /* daca fisierul de output nu s-a putut deschide, iesim din functie */
        if (!out)
            return -1;
        unsigned int colour = 0;
        char type[ONE_HUNDRED];
        unsigned int width = 0, height = 0;
        char final = 0;
        /* se citeste tipul fisierului care se afla pe prima linie in sirul de caractere "type" */
        fscanf(inp, "%s\n", type);
        /* se citesc dimensiunile imaginii, respectiv "width" si "height", aflate pe a doua linie
        a fisierului */
        fscanf(inp, "%u %u\n", &width, &height);
        /* se citeste valoarea maxima pe care o poate lua o culoare, aflata pe linia a treia
        a fisierului */
        fscanf(inp, "%u", &colour);
        /* se citeste caracterul care marcheaza finalul informatiilor despre fisier si inceputul
        imaginii propriu-zise */
        fscanf(inp, "%c", &final);

        /* se aloca dinamic matricea de pixeli in care vor fi retinute informatiile despre fiecare
        componenta de culoare */
        int i = 0, j = 0;
        RGB **pixeli = (RGB **)malloc(sizeof(RGB *) * height);
        for (i = 0; i < height; i++) {
            pixeli[i] = malloc(sizeof(RGB) * width);
            for (j = 0; j < width; j++) {
                /* se citesc din fisier informatiile despre fiecare componenta de culoare */
                fread(&pixeli[i][j].red, sizeof(unsigned char), 1, inp);
                fread(&pixeli[i][j].green, sizeof(unsigned char), 1, inp);
                fread(&pixeli[i][j].blue, sizeof(unsigned char), 1, inp);
            }
        }
        int x = 0, y = 0;
        /* se converteste factorul, primit ca al doilea parametru in linia de comanda, in int */
        int factor = atoi(argv[2]);
        int frunza = 0;
        /* se apeleaza functia de constructie a arborelui */
        TArbore imag = Constr_arbore(pixeli, x, y, (int)height, factor);
        /* se apeleaza functia pentru determinarea nivelului maxim din arbore */
        int nr = niv_max(imag);
        /* se afiseaza in fisierul de output informatia obtinuta */
        fprintf(out, "%d\n", nr);
        /* se apeleaza functia pentru determinarea numarului de frunze din arbore */
        int frunze = nr_frunze(imag);
        /* se afiseaza in fisierul de output informatia obtinuta */
        fprintf(out, "%d\n", frunze);
        unsigned int size = 0;
        /* am initializat coada "c" pe care o vom folosi pentru parcurgerea arborelui pe nivel */
        TCoada *c = InitQ();
        initializare(imag, c);
        /* folosind parcurgerea pe nivel, se va determina dimensiunea laturii
        cu cea mai mare zona nedivizata */
        max_size(imag, &size, c);
        /* se afiseaza in fisierul de output informatia obtinuta */
        fprintf(out, "%d\n", size);
        /* se va dezaloca memoria pentru coada, arbore si matricea de pixeli */
        DistrQ(&c);
        distr_arb(&imag);
        dezaloca_mat(pixeli, (int)width);
        /* se vor inchide fisierele de input si de output */
        fclose(inp);
        fclose(out);
    }
    /* se verifica daca primul argument din linia de comanda este "-c2",
    pentru a rezolva a doua cerinta */
    if (strncmp(argv[1], "-c2\n", 3) == 0) {
        /* se deschide fisierul de input (in format binar) care este reprezentat
        de al treilea parametru in linia de comanda  */
        FILE *inp = fopen(argv[3], "rb");
        /* se deschide fisierul de input (in format binar) care este reprezentat
        de al patrulea parametru in linia de comanda  */
        FILE *out = fopen(argv[4], "wb");
        /* daca fisierul de input nu s-a putut deschide, iesim din functie */
        if (!inp)
            return -1;
        /* daca fisierul de output nu s-a putut deschide, iesim din functie */
        if (!out)
            return -1;
        unsigned int colour = 0;
        char type[ONE_HUNDRED];
        unsigned int width = 0, height = 0;
        char final = 0;
        /* se citeste tipul fisierului care se afla pe prima linie in sirul de caractere "type" */
        fscanf(inp, "%s\n", type);
        /* se citesc dimensiunile imaginii, respectiv "width" si "height", aflate pe a doua linie
        a fisierului */
        fscanf(inp, "%u %u\n", &width, &height);
        /* se citeste valoarea maxima pe care o poate lua o culoare, aflata pe linia a treia
        a fisierului */
        fscanf(inp, "%u", &colour);
        /* se citeste caracterul care marcheaza finalul informatiilor despre fisier si inceputul
        imaginii propriu-zise */
        fscanf(inp, "%c", &final);

        /* se aloca dinamic matricea de pixeli in care vor fi retinute informatiile despre fiecare
        componenta de culoare */
        int i = 0, j = 0;
        RGB **pixeli = (RGB **)malloc(sizeof(RGB *) * height);
        for (i = 0; i < height; i++) {
            pixeli[i] = malloc(sizeof(RGB) * width);
            for (j = 0; j < width; j++) {
                /* se citesc din fisier informatiile despre fiecare componenta de culoare */
                fread(&pixeli[i][j].red, sizeof(unsigned char), 1, inp);
                fread(&pixeli[i][j].green, sizeof(unsigned char), 1, inp);
                fread(&pixeli[i][j].blue, sizeof(unsigned char), 1, inp);
            }
        }
        int x = 0, y = 0;
        /* se converteste factorul, primit ca al doilea parametru in linia de comanda, in int */
        int factor = atoi(argv[2]);
        int frunza = 0;
        /* se apeleaza functia de constructie a arborelui */
        TArbore imag = Constr_arbore(pixeli, x, y, (int)height, factor);
        /* am initializat coada "c" pe care o vom folosi pentru parcurgerea pe nivel a arborelui */
        TCoada *c = InitQ();
        initializare(imag, c);
        /* se apeleaza functia de parcurgere care va scrie in fisier informatiile dorite */
        parcurgere_nivel(c, out);
        /* se elibereaza memoria pentru coada, arbore si matricea de pixeli */
        DistrQ(&c);
        distr_arb(&imag);
        dezaloca_mat(pixeli, (int)width);
        /* se inchid fisierele de input si de output */
        fclose(inp);
        fclose(out);
    }
    /* se verifica daca primul parametru din linia de comanda este "-d",
    pentru a rezolva a treia cerinta */
    if (strncmp(argv[1], "-d\n", 2) == 0) {
        /* se deschide fisierul de input (in format binar), care este reprezentat
        de al doilea argument din linia de comanda */
        FILE *inp = fopen(argv[2], "rb");
        /* se deschide fisierul de output (in format binar), care este reprezentat
        de al treilea argument din linia de comanda */
        FILE *out = fopen(argv[3], "wb");
        /* daca fisierul de input nu s-a putut deschide, iesim din functie */
        if (!inp)
            return -1;
        /* daca fisierul de output nu s-a putut deschide, iesim din functie */
        if (!out)
            return -1;
        /* am determinat dimensiunea fisierului binar folosind functiile fseek (pentru a ajunge la finalul fisierului)
        si ftell (pentru a determina dimensiunea propriu-zisa) */
        fseek(inp, 0, SEEK_END);
        long dim = ftell(inp);
        /* dupa ce am determinat dimensiunea, ne vom intoarce la inceputul fisierului */
        fseek(inp, 0, SEEK_SET);
        /* se afiseaza in fisierul de output tipul fisierului, respectiv "P6" */
        fprintf(out, "P6\n");
        unsigned int size = 0;
        /* se citeste din fisierul de input prima informatie, respectiv dimensiunea imaginii */
        fread(&size, sizeof(unsigned int), 1, inp);
        /* se afiseaza in fisierul de output dimensiunea imaginii,
        de 2 ori (atat pentru lungime, cat si pentru latime)  */
        fprintf(out, "%d %d\n", size, size);
        unsigned int colour = culoare;
        /* se afiseaza in fisierul de output valoarea maxima pe care o poate lua o culoare */
        fprintf(out, "%d\n", colour);
        /* se initializeaza coada "c" in care vor fi retinute informatiile despre
        arbore (conform parcurgerii pe nivel) */
        TCoada *c = NULL;
        /* se apeleaza functia de citire din fisier care va returna coada cu informatiile dorite */
        c = citire(inp);
        TArbore arbore = make_arb(c, size);
        /* se elibereaza coada folosita anterior, intrucat nu vom mai avea nevoie de ea */
        DistrQ(&c);
        /* se initializeaza matricea de pixeli in care vor fi retinute informatiile despre 
        culorile din imaginea care va fi reconstruita */
        RGB **pixeli = (RGB **)malloc(sizeof(RGB *) * size);
        int i = 0;
        for (i = 0; i < size; i++) {
            pixeli[i] = malloc(sizeof(RGB) * size);
        }
        int x = 0, y = 0;
        /* se apeleaza functia de decontructie a arborelui, care va returna matricea
        de pixeli initializata anterior */
        pixeli = deconstr_arb(arbore, pixeli, x, y, (int)size);

        /* se vor afisa in fisierul de output informatiile retinute in fiecare pixel
        pentru fiecare componenta de culoare */
        int j = 0;
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fwrite(&pixeli[i][j].red, sizeof(unsigned char), 1, out);
                fwrite(&pixeli[i][j].green, sizeof(unsigned char), 1, out);
                fwrite(&pixeli[i][j].blue, sizeof(unsigned char), 1, out);
            }
        }

        /* se va elibera memoria pentru arbore si matricea de pixeli */
        distr_arb(&arbore);
        dezaloca_mat(pixeli, (int)size);
        /* se vor inchide fisierele de input si output */
        fclose(inp);
        fclose(out);
    }

    return 0;
}

