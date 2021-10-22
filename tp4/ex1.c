#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Cel Cel;
typedef struct Liste Liste;
void insertion(Liste *liste, Cel *c);
void suppression(Liste *liste);

int main(int argc, char** argv){
    Liste *arr = initialisation();

}
typedef struct Cel Cel;
struct Cel {
    int valeur;
    Cel* suivant;
};

typedef struct Liste Liste;
struct Liste {
    Cel *premier;
};

Liste *initialisation(){
    Liste *liste = malloc(sizeof(*liste));
    Cel *cel = malloc(sizeof(*cel));
    
    if (liste == NULL || cel == NULL){
        exit(EXIT_FAILURE);
     }
     
     cel->valeur = 0;
     cel->suivant = NULL;
     liste->premier = cel;
     return liste;
}

Cel * allouerCellule(int val){
    Cel *nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }
    nouveau->valeur = val;
    return nouveau;
}

void insertion(Liste *liste, Cel *c){

    if (liste == NULL || c== NULL)
    {
        exit(EXIT_FAILURE);
    }
    c->suivant = liste->premier;
    liste->premier = c;
}

