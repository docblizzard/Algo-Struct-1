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
void narratepath(Salle *lab, Knight player);
void narratepathupgrade(Salle *lab, Knight player);
void openpaths(Salle *lab, Knight player, Salle *path);
void labcreation(Salle *lab, FILE * plan);
void mainloop(Salle *lab, int sizelab);



int main(void){
    Salle lab[30] = {0};
    int sizelab = sizeof(lab)/sizeof(lab[0]);
    FILE *file = fopen("plan.pln", "r");
    labcreation(lab, file);
    fclose(file);
    mainloop(lab, sizelab);
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
                    break;
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
        printf("Tu te retrouves à l'entrée du chateau labyrinthe.\n\n");
        while(!found){
            char dir = 0;
            narratepathupgrade(lab, player);
            printf("Dans quelle direction aller? :");
            scanf("%[n-s-e-o-N-S-E-O]%c",&dir);
            dir = toupper(dir);
            switch(dir){
                case 'N':
                    if (lab[player.pos].N){
                        player.pos = lab[player.pos].N->num;
                        printf("Tu prends la porte Nord et tu te retrouves dans la salle numéro %d.\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'S':
                    if (lab[player.pos].S){
                        player.pos = lab[player.pos].S->num;
                        printf("Tu prends la porte Sud et tu te retrouves dans la salle numéro %d.\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'E':
                    if (lab[player.pos].E){
                        player.pos = lab[player.pos].E->num;
                        printf("Tu prends la porte Est et tu te retrouves dans la salle numéro %d.\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais ce chemin n'existe pas.\n");
                        break;
                    
                    
                case 'O':
                    if (lab[player.pos].O){
                        player.pos = lab[player.pos].O->num;
                        printf("Tu prends la porte Ouest et tu te retrouves dans la salle numéro %d.\n", player.pos);
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !\n");
                            found = 1;
                            loop = 1;
                        }
                        break;
                    }
                    else printf("Désolé mais ce chemin n'existe pas.\n");
                        break;
                    

                default:
                    printf("Désolé mais ce que tu as tapé est incorrect \n");
                    break;
            } 
            viderBuffer();
        }
    }
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}
/*
void narratepath(Salle *lab, Knight player){
    printf("Il y'a une porte");
    if (lab[player.pos].N){
        printf(" vers le Nord,");
    }
    if (lab[player.pos].S){
        printf(" vers le Sud,");
    }
    if (lab[player.pos].E){
        printf(" vers l'Est,");
    }
    if (lab[player.pos].O){
        printf(" vers l'Ouest");
    }
    else printf(", il n'y aucune porte enfaite..");

    printf(".\n");
} */

void narratepathupgrade(Salle *lab, Knight player){
    printf("\n");
    if (lab[player.pos].N){
        printf("                      [ N ]\n"
        "                        |\n");
    }
    if (lab[player.pos].O){
        printf("            [ O ]-----");
        printf("[ P ]");
    }
    else printf("                      [ P ]");

    if (lab[player.pos].E){
        printf("-----[ E ]");
    }
    if (lab[player.pos].S){
        printf("\n                        |"
        "\n                      [ S ]");
    } 
    printf("\n\n");
}


void pathsolution(Salle *lab, Knight player, Salle *path){
    


void openpaths(Salle *lab, Knight player, Salle *path){
    if (lab[player.pos].N){
        openpaths(lab[player.pos].N, player, path);

    }
    if (lab[player.pos].E){
       neighb[1] = *lab[player.pos].E;
    }
    if (lab[player.pos].O){
        neighb[2] = *lab[player.pos].O;
    }
    if (lab[player.pos].S){
        neighb[3] = *lab[player.pos].S;
    }
} 