#include <stdio.h>
#include<stdlib.h>

typedef struct nAVL{
    int val;
    int h;
    struct nAVL *g;
    struct nAVL *d;
} NAVL;

typedef NAVL *AVL;
void MAJHauteur(NAVL *no);
void ajouter(AVL *ar, int x);




int main(int argc, char** argv){
    AVL a = NULL;
    ajouter(&a,25);
    ajouter(&a,20);
    ajouter(&a,19);
    MAJHauteur(a);
    printf("Taille de AVL est %d", a->g->h);
}


// EX1

void MAJHauteur(NAVL *no){
    if (!(no)) return;
    if (no->d != NULL || no->g !=NULL ){
        no->h ++;
        MAJHauteur(no->d);
        MAJHauteur(no->g);
    }
}

void rotationG(AVL *ar){
    NAVL * temp = *ar;
    if ((*ar)->g){
        (*ar)->g = temp;
        *ar = temp->g; 
    }
}

void ajouter(AVL *ar, int x){
    if(*ar==NULL){
        *ar=(NAVL*)malloc(sizeof(NAVL));
        (*ar)->val=x;
        (*ar)->g=NULL;
        (*ar)->d=NULL;
    }
    if ((*ar)->val == x)
        return;
    if((*ar)->val < x)
        ajouter(&(*ar)->d,x);
    else
        ajouter(&(*ar)->g,x);
    
}
