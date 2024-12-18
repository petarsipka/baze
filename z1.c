#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct tacka_st {
    double x;
    double y;
};

struct tacka_st najbliza_t(struct tacka_st* niz, int n) {
    if(n != 0) {
        double minimum = -1, distanca = sqrt(pow(niz[0].x,2) + pow(niz[0].y, 2));
        int i, min_ind = 0;

        for(i = 1; i < n; i++) {
            distanca = sqrt(pow(niz[i].x,2) + pow(niz[i].y, 2));
            if(distanca < minimum || minimum == -1) {
                minimum = distanca;
                min_ind = i;    
            }
        }

        return niz[min_ind];
    } else {
        struct tacka_st koord_poc;
        koord_poc.x = 0;
        koord_poc.y = 0;
        return koord_poc;
    }
}

int main() {
    int n;

    scanf("%d", &n);
    printf("%d\n", n);  

    int i;
    struct tacka_st tacke[n];
    printf("Unos tacaka\n\n");  
    for(i = 0; i < n; i++) {
        printf("Tacka %d\n", i+1);
        printf("x: ");  
        tacke[i].x = scanf("%lf", &tacke[i].x);
        printf("y: ");  
        tacke[i].y = scanf("%lf", &tacke[i].y);
    }

    struct tacka_st najbliza = najbliza_t(tacke, n);
    printf("A(%lf, %lf)", najbliza.x, najbliza.y);
    


    return 0;
}