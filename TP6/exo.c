#include <stdio.h>
#include<stdlib.h>

typedef struct noeud{
    int val;
    struct noeud *g;
    struct noeud *d
}Noeud;
typedef Noeud *Arbre;

typedef struct file{
    int queue;
    int tete;
    Arbre *tab;
    int tMax;
}File;

typedef struct pile{
    int sommet;
    Arbre *tab;
    int tMax;
}Pile;


int main(int argc, char** argv){

}

File *initialiserF(void){
    File *new = malloc(sizeof(*nouveau);
    return new;
}

void enfiler(File *f, Arbre a){
    File *newfile = malloc(sizeof(File));

}