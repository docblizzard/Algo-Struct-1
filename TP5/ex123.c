#include <stdio.h>
#include<stdlib.h>

typedef struct noeud{
    int val;
    struct noeud* g;
    struct noeud* d;

}Noeud;
typedef Noeud *Arbre;
Arbre anul();
Arbre ass(Arbre gauche, Arbre droit, int etiquette);
void liberer(Arbre a);
void parcours_postfixe(Arbre a);
void parcours_infixe(Arbre a);
void parcours_prefixe(Arbre a);



int main(int argc, char** argv){
    Arbre Narbre = ass(ass(ass(anul(),anul(),4),anul(),3),
                    ass(ass(anul(),anul(),7),ass(anul(),anul(),5),2),1);
    if ( Narbre == NULL){
        printf("yes");
    }
    //else printf("%d", Narbre->d->g->val);
    parcours_postfixe(Narbre);
    printf("\n");
    parcours_infixe(Narbre);
    printf("\n");
    parcours_prefixe(Narbre);

    
}
//EX1
Arbre anul(){
    Arbre new = NULL;
    return new;
}

Arbre ass(Arbre gauche, Arbre droit, int etiquette){
    Arbre new = malloc(sizeof(Arbre));
    new->val = etiquette;
    new->g = gauche;
    new->d = droit;
    return new;
}

void liberer(Arbre a){
    if (a ==NULL) return;

    liberer(a->g);
    liberer(a->d);
    free(a);
}

// EX2
void parcours_postfixe(Arbre a){
    if (a == NULL) return;

    parcours_postfixe(a->g);
    parcours_postfixe(a->d);

    printf("%d ", a->val);
}

void parcours_infixe(Arbre a){
    if (a == NULL) return;

    parcours_infixe(a->g);
    printf("%d ", a->val);
    parcours_infixe(a->d);

}
void parcours_prefixe(Arbre a){
    if (a == NULL) return;
    printf("%d ", a->val);
    parcours_prefixe(a->g);
    parcours_prefixe(a->d);

}

//EX3
int construire_arbre(Arbre *a){
    Arbre *temp = malloc(sizeof(Arbre));
    int numb;
    do{
        scanf(%d, &numb);
    }while(num != NULL){
        if num == -1{
            anul();
        }
        else{
            temp = ass(anul(),anul(),numb);
            temp = temp->gauche;
        }
    }
}

//EX4

int nb_noeud(Arbre a){
    int count= 0;
    Arbre * temp = a;
}