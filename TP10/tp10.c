#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<assert.h>

# define MAX_NOEUD 40 
typedef struct gra{
int graphe[MAX_NOEUD][MAX_NOEUD];
int nbNoeud;
} Graphe;

void creerGraphe(Graphe* g,FILE* grDesc);

int main(int argc, char** argv){
    FILE *file;
    file = fopen("grDesc2", "r");

    Graphe gr;
    creerGraphe(&gr, file);    
    fclose(file);
    printf("%d", gr.graphe[7][4]);
}
//EX1
void creerGraphe(Graphe* g,FILE* grDesc){
    int i,j,d,a,e;

    fscanf(grDesc,"%d",&g->nbNoeud);
    if(g->nbNoeud>=MAX_NOEUD)
        exit(EXIT_FAILURE);

    for(i=0;i<g->nbNoeud+1;i++)
        for(j=0;j<g->nbNoeud+1;j++)
        g->graphe[i][j]=-1;

    while(fscanf(grDesc,"%d->%d:%d",&d,&a,&e)==3){
        if(d>g->nbNoeud || a>g->nbNoeud || d<1 || a<1)
            exit(EXIT_FAILURE);

        g->graphe[d][a]=e;
    }
    if(!feof(grDesc)) 
        exit(EXIT_FAILURE);
}

//EX2

void cheminOpti(Graphe *g, int s, int a){
    int cost[g->nbNoeud][g->nbNoeud];
    int distance[g->nbNoeud], preced[g->nbNoeud], count, nextnode, midistance;
    int visited[g->nbNoeud];
    for (int i = 0; i<g->nbNoeud; i++){
        for (int j = 0; j<g->nbNoeud; j++){
            if (g->graphe[i][j]== -1){
                cost[i][j] = INFINITY;
            }
            else cost[i][j] = g->graphe[i][j];
        }
    }
    for (int i = 0; i<g->nbNoeud; i++){
        distance[i] = cost[s][i];
        visited[i] = 0;
    }
    distance[s] = 0;
    visited[s] = -1;
    count = 1;
    while(count<g->nbNoeud - 1){
        midistance = INFINITY;
    
        for (int i = 0; i <g->nbNoeud; i++){
            if (distance[i]< midistance && !visited[i]){
                midistance = distance[i];
                nextnode = i;
            }
        }
    
        visited[nextnode] = 1;
        for (int i = 0; i<g->nbNoeud; i++){
            if (!visited[i]){
                if (midistance+cost[nextnode][i]< distance[i]){
                    distance[i] = midistance + cost[nextnode][i];
                    preced[i] = nextnode;
                }
            }
            
        }
        count++;
    }
    for (int i = 0; i<g->nbNoeud; i++){
        int ze;
        if (i != s){
            printf("\n Distance of node %d=%d", i, distance[i]);
            printf("\nPath=%d",i);
            ze = i;
        }
        do {
            ze = preced[ze];
            printf("<-%d,ze");
        }
        while(ze != s);
    }
}