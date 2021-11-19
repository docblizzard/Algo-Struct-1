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
Noeud *Recherche(Arbre a, int x);
Noeud *extraireMax(Arbre *a);



int main(int argc, char** argv){
    Arbre narbre =NULL;
    ajouter(&narbre, 42);
    ajouter(&narbre, 52);
    ajouter(&narbre,21);
    ajouter(&narbre, 95);
    printf("%d\n", narbre->d->d->val);
    printf("Le pointeur de l'arbre est %p", Recherche(narbre,95));
    extraireMax(&narbre);

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
if (a == NULL)
    return 1;
    int d;
    return 
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
Noeud *Recherche(Arbre a, int x){
    if (a == NULL) 
        return NULL;    
    
    if (a->val == x)
        return a;   
    
    if (a->val < x){
        return Recherche(a->d,x);
    }
    else return Recherche(a->g,x);
    
}

Noeud *extraireMax(Arbre *a){
    int max = (*a)->val;
    Noeud temp = a;
    while (temp != NULL){
        if (temp->d->val > max){
            max = temp->d->val;
            temp = temp->d;
        }
        if (temp->g->val > max){
            max = temp->g->val;
            temp = temp->g;
        }
    }
    printf("%d",max);
    return temp;
}