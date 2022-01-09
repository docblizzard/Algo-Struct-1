#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define LAB_SIZE 10

// Struct pour les salles
typedef struct salle{
    int pos [LAB_SIZE];
    struct salle* N;
    struct salle* S;
    struct salle* E;
    struct salle* O;
    int num;
} Salle;

// Struct pour le personnage
typedef struct knight{
    int pos;
    int key;
} Knight;

void viderBuffer();
int lire(char *chaine, int longueur);

void labcreation(Salle *lab, FILE * plan);
void mainloop(Salle *lab, int sizelab);





int main(void){
    Salle lab[6];
    int sizelab = sizeof(lab)/sizeof(lab[0]);
    FILE *file = fopen("plan.pln", "r");
    //printf("%d ", lab[3].num);
    labcreation(lab, file);
    fclose(file);
    mainloop(lab, sizelab);

    //printf("%d ", lab[0].num);
    //printf("%d ", lab[1].num);
    //printf("%d ", lab[3].O->num);

}
// Lecture du fichier texte et convertir en salles du labyrinthe
void labcreation(Salle *lab, FILE * plan){
    char string[9];
    int num; char name [2]; char direction1; char direction2;
    int room1; int room2;
    // Lis chaque ligne pour créer les salles et leur connections
    if (fscanf(plan,"%s",string)  && (strcmp(string,"debutPlan")==0)) {
        while ( fscanf(plan, "%s %d.%c-%d.%c;",name, &room1, &direction1, &room2, &direction2) == 5){
            lab[room1].num = room1;
            lab[room2].num = room2;
            switch(direction1){
                case 'N':
                    lab[room1].N = &lab[room2];
                    break;
                case 'S':
                    lab[room1].S = &lab[room2];
                    break;
                case 'E':
                    lab[room1].E = &lab[room2];
                    break;
                case 'O':
                    lab[room1].O = &lab[room2];
                    break;

                default:
                    printf("No position");
            }
            switch(direction2){
                case 'N':
                    lab[room2].N = &lab[room1];
                    break;
                case 'S':
                    lab[room2].S = &lab[room1];
                    break;
                case 'E':
                    lab[room2].E = &lab[room1];
                    break;
                case 'O':
                    lab[room2].O = &lab[room1];
                    break;

                default:
                    printf("No position");
                    break;

            }
        }
    } 
    else printf("False");
}

void mainloop(Salle *lab, int sizelab){
    int loop = 0;
    while (!loop){
        Knight player;
        player.pos = 0;
        int found = 0;
        printf("Tu te retrouve à l'entrée du chateau labyrinthe.\n");
        while(!found){
            char dir;
            printf("Dans quelle direction aller? Soit N, S, E, O ! ");
            scanf("%[n-s-e-o-N-S-E-O]%c",&dir);
            dir = toupper(dir);           
            switch(dir){
                case 'N':
                    if (lab[player.pos].N){
                        player.pos = lab[player.pos].N->num;
                        printf("Tu prends la porte Nord et tu te retrouves dans la salle numéro %d\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        found = 1;
                        loop = 1;
                        break;
                    }
                    else printf("Désolé mais soit ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'S':
                    if (lab[player.pos].S){
                        player.pos = lab[player.pos].S->num;
                        printf("Tu prends la porte Sud et tu te retrouves dans la salle numéro %d\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        found = 1;
                        loop = 1;
                        break;
                    }
                    else printf("Désolé mais soit ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'E':
                    if (lab[player.pos].E){
                        player.pos = lab[player.pos].E->num;
                        printf("Tu prends la porte Est et tu te retrouves dans la salle numéro %d\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais soit ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'O':
                    if (lab[player.pos].O){
                        player.pos = lab[player.pos].O->num;
                        printf("Tu prends la porte Ouest et tu te retrouves dans la salle numéro %d\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !\n");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais soit ce chemin n'existe pas.\n");
                        break;
                    

                default:
                    printf("Désolé mais ce que tu as tapé est incorrect \n");
                    found = 1;
                    loop = 1;
                    break;
            } 
            viderBuffer();
        }
    }
}

int lire(char *chaine, int longueur){
    char *positionEntree = NULL;
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL){

        positionEntree = strchr(chaine, '\n'); 
        if (positionEntree != NULL){ 
            *positionEntree = '\0';
        }
        else viderBuffer(); return 1; 
    }
    else viderBuffer(); return 0; 
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}