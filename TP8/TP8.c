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

int main(int argc, char** argv){
    AVL a = NULL;
    
}


// EX1

void MAJHauteur(NAVL *no){
    if (no->d ){
        no->h += no->d->h;
    }
    if (no->g ){
        no->h += no->d->h;
    }

}