#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cel {
    int valeur;
    struct cel* suivant;
}Cellule;

typedef Cellule* Liste;

Cellule * allouerCellule(int val);
void ajouterEnQueue(Liste *liste, Cellule *c);
void ajouterEnTete(Liste *liste, Cellule *c);
int estVide(Liste l);
void afficherListe(Liste liste);
void viderListe(Liste * l);
void inserer(Liste *l,Cellule *c,int i);
void extraire(Liste *l,int i);


int main(int argc, char** argv){
    Liste list = NULL;
    printf("%d\n",estVide(list));
    ajouterEnTete(&list,allouerCellule(40));
    ajouterEnTete(&list,allouerCellule(68));
    printf("%d\n",estVide(list));
    ajouterEnQueue(list, allouerCellule(70));
    inserer(list, allouerCellule(52),1);
    //extraire(list,1);

    //viderListe(list);
    afficherListe(list);


}

Cellule * allouerCellule(int val){
    Cellule *nouveau = malloc(sizeof(Cellule));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);
    }
    nouveau->valeur = val;
    nouveau->suivant = NULL;
    return nouveau;
}

void ajouterEnTete(Liste *liste, Cellule *c){
    c->suivant = *liste;
    *liste = c;
} 

void afficherListe(Liste liste){
    Cellule *tmp = liste;
    while( tmp != NULL){
        printf("%d\n", tmp->valeur);
        tmp = tmp->suivant;
    } 
}
int estVide(Liste l){
    if (l == NULL){
        return 1;
    }
    else return 0;
}

void viderListe(Liste *l){
    if (l == NULL){
        return;
    }
    Cellule *tmp = l;
    Cellule *suivant;
    while (tmp !=NULL){
        suivant = tmp->suivant;
        free(tmp);
        tmp = suivant;
    }
}

//EX2
void ajouterEnQueue(Liste *liste, Cellule *c){
    if (liste == NULL){
        c->suivant = liste;
        liste = c;
    }
    else {
        Cellule *dernier = liste;
        while (dernier->suivant != NULL){
        dernier = dernier->suivant;
        }
        dernier->suivant = c;

    }
}

//EX3

void inserer(Liste *l,Cellule *c,int i){
    int count = 0;
    Cellule *next = l;
    Cellule *tmp;
    while (count != i ){
        next = next->suivant;
        count +=1;
    }
    next->valeur = c->valeur;
    
}

void extraire(Liste *l,int i){
    int count = 0;
    Cellule *delete = l;
    Cellule *temp;
    while (count != i ){
        delete = delete->suivant;
        count +=1;
    }
    temp = delete->suivant;
    Cellule *print = temp;
    delete->suivant= delete->suivant->suivant;
    free(temp);
    return print;
}