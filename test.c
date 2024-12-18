#include <stdio.h>
#include <stdlib.h>


struct test {
    char linija[100];
    int rbrUlaznice;
    int rbrUtakmice;
    char datPocetka[16];
    char imeTimaGosti[30];
    char tipUlaznice;
    char datIVremeUlaska[16];
};

int main() {


    struct test ulaznica;

    char t1[] = "51 15/10/2024_18:30 Hertha_BSC O 15/10/2024_17:45";
    char t2[] = "51 15/10/2024_18:30 Hertha_BSC O 15/10/2024_17:45";
    if(sscanf(t2, "%d %16s %30s %c %16s",
            &ulaznica.rbrUtakmice,
            ulaznica.datPocetka,
            ulaznica.imeTimaGosti,
            &ulaznica.tipUlaznice,
            ulaznica.datIVremeUlaska) == 5)
    ulaznica.rbrUlaznice = 1;
    printf("%d %d %s %s %c %s\n",
        ulaznica.rbrUlaznice,
        ulaznica.rbrUtakmice,
        ulaznica.datPocetka,
        ulaznica.imeTimaGosti,
        ulaznica.tipUlaznice,
        ulaznica.datIVremeUlaska);

    return 0;
}