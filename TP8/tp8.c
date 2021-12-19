#include <stdio.h>
#include <stdlib.h>

typedef struct nAVL{
    int val;
    int h;
    struct nAVL *g;
    struct nAVL *d;
} NAVL;

typedef NAVL *AVL;
void MAJHauteur(NAVL *no);
void ajouter(AVL *ar, int x);
void rotationD(AVL *ar);
void rotationG(AVL *ar);


int max(int a, int b){
    if (a >= b) return a;
    else return b;
}


int main(int argc, char** argv){
    AVL a = NULL;
    ajouter(&a,25);
    ajouter(&a,20);
    ajouter(&a,15);
    ajouter(&a,30);    
    ajouter(&a,22);
    ajouter(&a,21);

    //rotationG(&a->g);
    rotationD(&a);
    rotationD(&a);
    //MAJHauteur((a->g));
    //MAJHauteur(a);

    printf("Taille de AVL est %d", a->h);

    //printf("\nvaleur est %d", a->g->g->val);
}


// EX1

void MAJHauteur(NAVL *no){
    if (!(no)) return;
    if (no->g && no->d){
        no->h = max(no->g->h, no->d->h) + 1;
        //printf("\nFor val %d height is %d ", no->val, no->h);
        MAJHauteur(no->g);
        MAJHauteur(no->d);
    }
    else if (no->g || no->d){
        if (no->g){
            no->h = no->g->h + 1;
            MAJHauteur(no->g);
        }
        if (no->d){
            no->h = no->d->h +1;
            MAJHauteur(no->d);
        }
    }
    else no->h = 0;

}
void rotationD(AVL *ar){
    if (!(*ar)) return;
    NAVL *pivot = (*ar)->g;
    (*ar)->g = pivot->d;
    pivot->d = *ar;
    MAJHauteur(pivot->d);
    *ar = pivot;
    MAJHauteur(*ar);
}

void rotationG(AVL *ar){
    if (!(*ar)) return;
    NAVL *pivot = (*ar)->d;
    (*ar)->d = pivot->g;
    pivot->g = *ar;
    MAJHauteur(pivot->d);
    *ar = pivot;
    MAJHauteur(*ar);
}

void ajouter(AVL *ar, int x){
    if(*ar==NULL){
        *ar=(NAVL*)malloc(sizeof(NAVL));
        (*ar)->val=x;
        (*ar)->h=0;
        (*ar)->g=NULL;
        (*ar)->d=NULL;
        //MAJHauteur(*ar);
    }
    if ((*ar)->val == x){
        return;
    }
    if((*ar)->val < x){
        ajouter(&(*ar)->d,x);
        MAJHauteur((*ar));
    }
    else
        ajouter(&(*ar)->g,x);    
        MAJHauteur((*ar));

}
