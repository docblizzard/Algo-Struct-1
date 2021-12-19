#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LAB_SIZE 10

typedef struct salle{
    int pos [LAB_SIZE];
    struct salle* N;
    struct salle* S;
    struct salle* E;
    struct salle* O;
} Salle;

typedef struct knight{
    int pos[LAB_SIZE];
    int key;
} Knight;

void labcreation(Salle lab, FILE * plan);


int main(void){
    Salle lab[LAB_SIZE];
    FILE *file = fopen("plan.pln", "r");
    labcreation(*lab, file);
    
    fclose(file);

}
// Initialization of the labyrinth
void labcreation(Salle lab, FILE * plan){
    char string[9];
    int num, N, S, E, O;
    if (fscanf(plan,"%s",string)){
        if (strcmp(string,"debutPlan")==0) printf("True");
    }
    else printf("False");
}