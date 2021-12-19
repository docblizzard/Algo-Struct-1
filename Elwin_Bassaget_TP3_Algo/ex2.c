#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void tri_fusionr(int* tab, int taille);
void fusion(int * T1, int t1, int * T2 , int t2, int * T);
int recherche(int* tab, int taille, int valeur);
int rechercheR(int *tab, int taille, int valeur);

int main(int argc, char** argv){
    int tab[10] = {24,58,30,10,87,25,16,62,42,90};
    printf("\n");
    tri_fusionr(tab,10);
    for(int i=0;i<10;i++) printf("%d ",tab[i]);
    //int found = recherche(tab, 10, 62);
    int foundr = rechercheR(tab, 10, 10);
    printf("\nLe numéro 87 se trouve en position %d",foundr);


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

int recherche(int *tab, int taille, int valeur){
    if (taille < 0 || taille > 10) return -1;
    
    int mid = (taille/2);
  
    if (tab[mid-1] == valeur){
    printf("\nLe numéro tab[%d] se trouve en position %d",tab[mid-1], taille);
        
    } 
    printf("\n %d ",mid);

    if (valeur > tab[mid-1]){
        //printf("%d+%d/2 = %d ",mid,mid, mid+mid/2);
        recherche(tab+mid, mid+mid/2, valeur);
    }
    if (valeur < tab[mid-1]){
        recherche(tab, mid+mid/2, valeur);

    }
    return 0;
}

int rechercheR(int *tab, int taille, int valeur){
    int found = 0;
    int first = 0;
    int last = taille - 1;
    int mid;
    while (!found && first <= last){
        mid = (first + last)/2;
        if (valeur == tab[mid]){
            found = 1;
        }
        else if ( valeur > tab[mid]){
            first = mid+1;
        }
        else last = mid-1;
        
    }
    return mid;
}