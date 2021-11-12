#include <stdio.h>
#include<stdlib.h>

typedef struct noeud {
    int val;
    struct noeud *g;
    struct noeud *d;
} Noeud;
typedef Noeud *Arbre;

void ajouter(Arbre *a, int x);
int estABR(Arbre a);
Arbre anul();
Arbre ass(Arbre gauche, Arbre droit, int etiquette);



int main(int argc, char** argv){
    Arbre narbre =NULL; 
    ajouter(&narbre, 42);
    printf("%d", narbre->val);
}



// EX 1
void ajouter(Arbre *a, int x){
    if(*a==NULL)
    {
        *a=(Noeud*)malloc(sizeof(Noeud));
        (*a)->val=x;
        (*a)->g=NULL;
        (*a)->d=NULL;
    }
    if ((*a)->val ==x)
        return;
    if((*a)->val<x)
        ajouter(&(*a)->d,x);
    else
        ajouter(&(*a)->g,x);
    
}

// EX2

/*int estABR(Arbre a){
    Arbre *temp = malloc(sizeof(*Arbre));
    if (temp->val != NULL){
        if (temp->val > temp->g->val && temp->val < temp->d->val){
            estABR(temp->g);
            stABR(temp->d);
        }
        else return 0;
    }
} */

// EX3
Noeud * Recherche(Arbre a, int x){
    Arbre temp = a; 
    if (temp->val == x){
        printf("trouvé");
        return temp->val;   
    }
    else if (temp->val > x){
        return Recherche(temp->)
    }

}
/*
Arbre anul(){
    Arbre new = NULL;
    return new;
}*/

/*Arbre ass(Arbre gauche, Arbre droit, int etiquette){
    Arbre new = malloc(sizeof(Arbre));
    new->val = etiquette;
    new->g = gauche;
    new->d = droit;
    return new;
} */