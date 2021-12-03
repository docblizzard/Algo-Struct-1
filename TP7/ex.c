#include <stdio.h>
#include<stdlib.h>

typedef struct nAVL{
    int val;
    int h ;
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
    ajouter(&a,18);
    ajouter(&a,17);

    MAJHauteur(a);
    printf("%d", a->g->h);
}


// EX1

void MAJHauteur(NAVL *no){
    int hauteurg = 0; int hauteurd = 0;

    if (!no) {
        return;
    }
    if (!(no->g && no->d)){
        no->h = 0;
    }
    if (no->g){
        hauteurg = no->g->h;
    }
    if (no->d){
        hauteurd = no->d->h;
    }
    if (hauteurd < hauteurg){
        no->h = no->h + (hauteurg + 1);
        MAJHauteur(no->g);
    }
    else{
        no->h = no->h + (hauteurd + 1);
        MAJHauteur(no->d);
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
