#include <stdio.h>
#include<stdlib.h>

typedef struct noeud {
    int val;
    int haut;
    struct noeud *g;
    struct noeud *d;
} Noeud;
typedef Noeud *Arbre;

void ajouter(Arbre *a, int x);
int estABR(Arbre a);
Noeud *Recherche(Arbre a, int x);
Noeud *extraireMax(Arbre *a);
Noeud *extraireMin(Arbre *a);
Noeud *extraire(Arbre *a, int x);
int hauteur(Arbre a);
int estABR(Arbre a);



int main(int argc, char** argv){
    Arbre narbre = NULL;
    ajouter(&narbre,10);
    ajouter(&narbre,5);
    ajouter(&narbre,2);
    ajouter(&narbre,7);
    ajouter(&narbre,4);
    ajouter(&narbre,6);
    ajouter(&narbre,12);

    //printf("%d", narbre->d->d->val);
    //printf("\nLe pointeur de l'arbre est %p", Recherche(narbre,2)); 
    //printf("\nla valeur maximale est %d",extraireMax(&narbre)->val);
    //printf("\nLe pointeur de la valeur minimale est %d",extraireMin(&narbre)->val);
    //printf("\nLe pointeur de la valeur max a été enlevé, son pointeur est %p", Recherche(narbre,95)); 
   /* extraire(&narbre, 5);
    printf("\nLe pointeur de l'arbre est %p", Recherche(narbre,5)); 
    printf("%d", narbre->val);
    printf("%d", narbre->g->val);
    printf("%d", narbre->g->g->val);
    printf("%d", narbre->g->g->g->val);
    printf("%d", narbre->g->g->g->d->val);
    printf("%d",hauteur(narbre)); */
    printf("\n%d\n",estABR(narbre));
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
    if ((*a)->val == x)
        return;
    if((*a)->val < x)
        ajouter(&(*a)->d,x);
    else
        ajouter(&(*a)->g,x);
    
}

// EX2

int estABR(Arbre a){
    if (a == NULL){
        return 1;
    }
    Noeud *temp = a;
    Noeud *MaxG = extraireMax(&(temp->g));

    Noeud *MaxD = extraireMin(&(temp->d));
    if (MaxG->val > temp->val || MaxD->val < temp->val){
        return 0;
    }
    else return 1;
} 

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

// EX4
Noeud *extraireMax(Arbre *a){
    if (*a == NULL){
        return NULL;
    }
    if ((*a)->d == NULL){
        Noeud *c = *a;
        *a= c->d;
        c->d = NULL;
        return c;
    }
    else return extraireMax(&((*a)->d));
}

//EX5
Noeud *extraireMin(Arbre *a){
    if (*a == NULL){
        return NULL;
    }
    if ((*a)->g == NULL){
        Noeud *c = *a;
        *a= c->g;
        c->g = NULL;
        return c;
    }
    else return extraireMin(&((*a)->g));
}

//EX6 

Noeud *extraire(Arbre *a, int x){ 
    if (*a == NULL) {
        return NULL;    
    }
    if ((*a)->val == x){
        Noeud *c = *a;
        if ((*a)->g != NULL && (*a)->d == NULL){
            *a = c->d;
        }
        if ((*a)->g == NULL && (*a)->d != NULL){
            *a = c->g;
        }
        else {
            Noeud *max = extraireMax(&(*a));

            if (max->g != NULL){
                max->g->g = c->g;
                *a = max;
                (*a)->d=c->d;
            }
            else{
                *a = max;
                (*a)->g=c->g;
                (*a)->d=c->d;
            }
            return c; 
        }
    }  
    
    if ((*a)->val < x){
        return extraire(&(*a)->d,x);
    }
    else return extraire(&(*a)->g,x);
    
}

//EX7
int hauteur(Arbre a){
    if (a == NULL){
        return 0;
    }
    else {
        int hauteurG = hauteur(a->g);
        int hauteurD = hauteur(a->d);
    
    if (hauteurG > hauteurD){
        return (hauteurG + 1);
    }
    else return (hauteurD + 1);
    }
}
