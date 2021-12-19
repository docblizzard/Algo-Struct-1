#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void fusion(int * T1, int t1, int * T2 , int t2, int * T);
void tri_fusionr(int* tab, int taille);
void tri_fusionb(int * tab, int taille);

int main(int argc, char** argv){
    int tab[10] = {24,58,30,10,87,25,16,62,42,90};
    for(int i=0;i<10;i++) printf("%d ",tab[i]);
    printf("\n");
    tri_fusionr(tab,10);
    //tri_fusionb(tab,10);
    for(int i=0;i<10;i++) printf("%d ",tab[i]);
}   

void fusion(int *T1, int t1, int *T2 , int t2, int *T){
    int i1 = 0;
    int i2 = 0;
    int k = 0;
    while (i1 < t1 && i2 < t2){
        if ( T1[i1] < T2[i2]){
            T[k] = T1[i1];
            i1 = 1+i1;
        }
        else{
            T[k] = T2[i2];
            i2 +=1;
        }
        k++;
    }
    while(i1<t1) T[k++] = T1[i1++];
    while(i2<t2) T[k++] = T2[i2++];
}   

void tri_fusionr(int * tab, int taille){
    if(taille<= 1 ) return;
    tri_fusionr(tab,taille/2);
    tri_fusionr(tab+taille/2,taille-taille/2);
    int T[taille];
    fusion(tab,taille/2,tab+taille/2,taille-taille/2,T);
    for(int i=0;i<taille;i++) tab[i]=T[i];
}

void tri_fusionb(int * tab, int taille){
    for (int y = taille ; y >=1; y = y/2){
        int T[y];
        for (int x = taille; x >= 1; x = x/2){
            int T[x];
            fusion(tab,x/2,tab+x/2,x-x/2,T);
                for(int i=0;i<x;i++) tab[i]=T[i];
        } 
    }
}
