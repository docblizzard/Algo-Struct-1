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
    int num;
} Salle;

typedef struct knight{
    int pos[LAB_SIZE];
    int key;
} Knight;

void labcreation(Salle *lab, FILE * plan);


int main(void){
    Salle lab[6];
    FILE *file = fopen("plan.pln", "r");
    //printf("%d ", lab[3].num);
    labcreation(lab, file);
    fclose(file);
    printf("%d", lab[4].num);

}
// Initialization of the labyrinth
void labcreation(Salle *lab, FILE * plan){
    char string[9];
    int num; char name [2]; char direction1; char direction2;
    int room1; int room2;
    if (fscanf(plan,"%s",string)  && (strcmp(string,"debutPlan")==0)) {
        while ( fscanf(plan, "%s %d.%c-%d.%c;",name, &room1, &direction1, &room2, &direction2) == 5){
            lab[room1].num = room1;
            lab[room2].num = room2;
            lab[room1].N = &lab[room2];
            lab[room2].S = &lab[room1];
            }
        }
            
    else printf("False");
}