#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PrenosPodataka(char*);
void IspisPodataka(char*, int);
void IspisPoRbr(char*,int);

// z5
void UnosNoveUlaznice(char*, int*);
void IzmeniTipUlaznice(char*, int);
void UkloniUlaznicuLog(char*, int);

// z6
void UkloniUlaznicuFiz(char*, int, int*);


struct ulaznica {
    int rbrUlaznice;
    int rbrUtakmice;
    char datPocetka[17];
    char imeTimaGosti[31];
    char tipUlaznice;
    char datIVremeUlaska[17];
    int podatakAktivan;
};


int main() {
    char izlaz[] = "data/ulasci.bin";
    int broj_podataka = PrenosPodataka(izlaz);


    
    //IspisPodataka(izlaz, broj_podataka);
    IspisPoRbr(izlaz, 29);
    UnosNoveUlaznice(izlaz, &broj_podataka);
    IspisPodataka(izlaz, broj_podataka);
    //IspisPoRbr(izlaz, 45);
    //IzmeniTipUlaznice(izlaz, 29);
    UkloniUlaznicuLog(izlaz, 44);   
    IspisPodataka(izlaz, broj_podataka);
    UkloniUlaznicuFiz(izlaz, 45, &broj_podataka);
    printf("\nstigao sam do ovde\n");
    IspisPodataka(izlaz, broj_podataka); 

    return 0;
}


int PrenosPodataka(char* izlaz) {
    char ulaz[] = "./data/BP1_03_Uvod_u_C_Z3_RBL_UlasciNaStadion.csv";
    FILE* ulaznaDat;
    if((ulaznaDat = fopen(ulaz, "r")) == NULL) {
        printf("Ulazni fajl nije ucitan\n");
        exit(1);
    }

    FILE* izlaznaDat;
    if((izlaznaDat = fopen(izlaz, "wb+")) == NULL) {
        printf("Izlazni fajl nije ucitan\n");
        exit(1);
    }

    char linija[100];
    struct ulaznica ulaznica;
    int rbrUlaznice = 0;

    while(fgets(linija, sizeof(linija), ulaznaDat) != NULL) {
        if(sscanf(linija, "%d %16s %30s %c %16s",
            &ulaznica.rbrUtakmice,
            ulaznica.datPocetka,
            ulaznica.imeTimaGosti,
            &ulaznica.tipUlaznice,
            ulaznica.datIVremeUlaska) != 5)
            continue;
        ulaznica.rbrUlaznice = rbrUlaznice;
        ulaznica.podatakAktivan = 1;
        fwrite(&ulaznica, sizeof(struct ulaznica), 1, izlaznaDat);
        rbrUlaznice++;        
    }    
    fclose(izlaznaDat);
    fclose(ulaznaDat);
    
    // zbog 5.
    return rbrUlaznice;
}

void IspisPodataka(char* imeDat, int broj_podataka) {
    FILE* fp;
    if((fp = fopen(imeDat, "rb")) == NULL) {
        printf("Ispis podataka nije otvorio\n");
        exit(1);
    }
   
    struct ulaznica ulaznica;
    while(fread(&ulaznica, sizeof(struct ulaznica), 1, fp)) {        
        printf("%d %d %s %s %c %s %d\n",
            ulaznica.rbrUlaznice,
            ulaznica.rbrUtakmice,
            ulaznica.datPocetka,
            ulaznica.imeTimaGosti,
            ulaznica.tipUlaznice,
            ulaznica.datIVremeUlaska,
            ulaznica.podatakAktivan);
    }
    fclose(fp);
}


void IspisPoRbr(char* imeDat,int rbrUlaznice) {
    FILE* fp;
    if((fp = fopen(imeDat, "rb")) == NULL) {
        printf("Ispis podataka nije otvorio\n");
        exit(1);
    }

    struct ulaznica ulaznica;
    while(fread(&ulaznica, sizeof(struct ulaznica), 1, fp)) {
        if(ulaznica.rbrUlaznice == rbrUlaznice) {   
            printf("%d %d %s %s %c %s %d\n",
                ulaznica.rbrUlaznice,
                ulaznica.rbrUtakmice,
                ulaznica.datPocetka,
                ulaznica.imeTimaGosti,
                ulaznica.tipUlaznice,
                ulaznica.datIVremeUlaska,
                ulaznica.podatakAktivan);
            break;
        }
    }
    fclose(fp);
}

void UnosNoveUlaznice(char* imeDat, int* rbrUl) {
    FILE* fp;
    if((fp = fopen(imeDat, "ab+")) == NULL) {
        printf("Unos nove ulaznice nije otvorio\n");
        exit(1);
    }

    struct ulaznica ulaznica;

    printf("\nUnesite podatke ulaznice:\n");
    ulaznica.rbrUlaznice = *rbrUl;
    printf("Unesite redni broj utakmice: ");
    scanf("%d", &ulaznica.rbrUtakmice);
    printf("Unesite datum i vreme pocetka: ");
    scanf("%s", ulaznica.datPocetka);
    printf("Unesite ime tima gostiju: ");
    scanf("%s", ulaznica.imeTimaGosti);
    printf("Unesite tip ulaznice: ");
    getchar();
    scanf("%c", &ulaznica.tipUlaznice);
    printf("Unesite datum i vreme ulaska: ");
    scanf("%s", ulaznica.datIVremeUlaska);
    ulaznica.podatakAktivan = 1;

    fwrite(&ulaznica, sizeof(struct ulaznica), 1, fp);
    (*rbrUl)++;


    fclose(fp);
}

void IzmeniTipUlaznice(char* imeDat, int rbrUl) {
    FILE* fp;
    if((fp = fopen(imeDat, "rb+")) == NULL) {
        printf("Ispis podataka nije otvorio\n");
        exit(1);
    }

    struct ulaznica ulaznica;
    while(fread(&ulaznica, sizeof(struct ulaznica), 1, fp)) {
        if(ulaznica.rbrUlaznice == rbrUl) {   
            printf("\nUnesite tip ulaznice: ");
            scanf("%c", &ulaznica.tipUlaznice);

            fseek(fp, -sizeof(struct ulaznica), SEEK_CUR);

            fwrite(&ulaznica, sizeof(struct ulaznica), 1, fp);
            break;
        }
    }
    fclose(fp);
}

void UkloniUlaznicuLog(char* imeDat, int rbrUl) {
    FILE* fp;
    if((fp = fopen(imeDat, "rb+")) == NULL) {
        printf("Ispis podataka nije otvorio\n");
        exit(1);
    }

    struct ulaznica ulaznica;
    while(fread(&ulaznica, sizeof(struct ulaznica), 1, fp)) {
        if(ulaznica.rbrUlaznice == rbrUl) {   
            ulaznica.podatakAktivan = 0;

            fseek(fp, -sizeof(struct ulaznica), SEEK_CUR);

            fwrite(&ulaznica, sizeof(struct ulaznica), 1, fp);
            break;
        }
    }
    fclose(fp);
}

// zad 6
void UkloniUlaznicuFiz(char* imeDat, int rbrUl, int* broj_podataka) {
    FILE* fp;
    FILE* temp;
    
    // Otvorite originalni fajl u binarnom režimu za čitanje
    if ((fp = fopen(imeDat, "rb")) == NULL) {
        printf("Nije moguće otvoriti fajl za čitanje\n");
        exit(1);
    }

    // Otvorite privremeni fajl u binarnom režimu za pisanje
    if ((temp = fopen("temp.bin", "wb+")) == NULL) {
        printf("Nije moguće otvoriti privremeni fajl\n");
        exit(1);
    }

    struct ulaznica ulaznica;
    int i = 0;

    // Čitajte sve slogove iz originalnog fajla
    while (fread(&ulaznica, sizeof(struct ulaznica), 1, fp)) {
        // Ako redni broj ulaznice nije onaj koji treba da obrišemo, upisujemo je u privremeni fajl
        if (ulaznica.rbrUlaznice != rbrUl) {
            fwrite(&ulaznica, sizeof(struct ulaznica), 1, temp);
        } else {
            // Ako je ovo ulaznica koju brišemo, samo je preskočimo
            printf("Brisem ulaznicu sa rbrUlaznice: %d\n", ulaznica.rbrUlaznice);
        }
    }

    // Zatvorite oba fajla
    fclose(fp);
    fclose(temp);

    // Sada obrišite originalni fajl
    remove(imeDat);

    // Preimenujte privremeni fajl u originalni
    rename("temp.bin", imeDat);

    // Ažurirajte broj podataka (smanjite za 1)
    (*broj_podataka)--;
}