#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

struct ulazak {
    int redni_broj;
    char vreme_pocetka[20];
    char gostujuci_tim[30];
    char ulaznica;
    char vreme_ulaska[20];
};




int main() {
    FILE* fp;

    if((fp = fopen("data/rbl.csv", "r")) == NULL) {
        printf("Nije uspesno otvorena datoteka\n");
        exit(1);
    }

    int n=1;
    char ch;
    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
            n++;
    }

    struct ulazak* ulasci = (struct ulazak*)malloc(n * sizeof(struct ulazak));

    if (ulasci == NULL) {
        printf("Neuspešna alokacija memorije.\n");
        fclose(fp);
        exit(1);
    }

    int i = 0;
    rewind(fp);
    while(fscanf(fp, "%d %s %s %c %s", 
                    &ulasci[i].redni_broj,
                    ulasci[i].vreme_pocetka,
                    ulasci[i].gostujuci_tim,
                    &ulasci[i].ulaznica,
                    ulasci[i].vreme_ulaska) == 5) {
        
        i++;
    }
    if(fp!=NULL) fclose(fp);


    if((fp = fopen("data/izvestaj.txt", "w+")) == NULL) {
        printf("Fajl za izvestaj nije dobro otvoren\n");
        exit(1);
    }

    int O = 0, S = 0, P = 0;
    for(i = 0; i < n; i++) {
        if(ulasci[i].ulaznica == 'O')
            O++;
        else if(ulasci[i].ulaznica == 'S')
            S++;
        else if(ulasci[i].ulaznica == 'P')
            P++;
    }

    int O_zarada = 50*O;
    int S_zarada = 30*S;
    int P_zarada = 25*P;

    fprintf(fp, "Obicne karte: %d, zarada: %d\n", O, O_zarada);
    fprintf(fp, "Sezonske karte: %d, zarada: %d\n", S, S_zarada);
    fprintf(fp, "Penzionerske karte: %d, zarada: %d\n", P, P_zarada);

    
    struct ulazak pom;
    int j;
    bool zamenjeno = false;
    for(i = 0; i < n - 1; i++) {
        zamenjeno = false;
        for(j = 0; j < n - 1 - i; j++) {
            if(strcmp(ulasci[j].gostujuci_tim, ulasci[j+1].gostujuci_tim) > 0) {
                pom = ulasci[j];
                ulasci[j] = ulasci[j+1];
                ulasci[j+1] = pom;
                zamenjeno = true;
            }
        }
        if(!zamenjeno)
            break;
    }


    fprintf(fp,"\nUlasci sa obicnim kartama:\n");
    for(i = 0; i < n; i++) {
        if(ulasci[i].ulaznica == 'O') {
            fprintf(fp, "%d %s %s %c %s\n",
                ulasci[i].redni_broj,
                ulasci[i].vreme_pocetka,
                ulasci[i].gostujuci_tim,
                ulasci[i].ulaznica,
                ulasci[i].vreme_ulaska
            );
        }
    }

    fprintf(fp,"\nUlasci sa sezonskim kartama:\n");
    for(i = 0; i < n; i++) {
        if(ulasci[i].ulaznica == 'S') {
            fprintf(fp, "%d %s %s %c %s\n",
                ulasci[i].redni_broj,
                ulasci[i].vreme_pocetka,
                ulasci[i].gostujuci_tim,
                ulasci[i].ulaznica,
                ulasci[i].vreme_ulaska
            );
        }
    }

    fprintf(fp,"\nUlasci sa penzionerskim kartama:\n");
    for(i = 0; i < n; i++) {
        if(ulasci[i].ulaznica == 'P') {
            fprintf(fp, "%d %s %s %c %s\n",
                ulasci[i].redni_broj,
                ulasci[i].vreme_pocetka,
                ulasci[i].gostujuci_tim,
                ulasci[i].ulaznica,
                ulasci[i].vreme_ulaska
            );
        }
    }

    free(ulasci);

    return 0;
}