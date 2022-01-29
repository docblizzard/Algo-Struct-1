#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define erreur(a) erreurT(a,__LINE__)


// Struct pour les salles
typedef struct salle{
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

int nb_fichiers_ouverts=0;

void erreurT(char*  a,int n);
FILE* ouvrir(char* nom,char* mode);
void fermer(FILE* f);
void viderBuffer();
void creerGrapheC(Salle *lab,char const * descr);
void restart(int *loop);
void narratepath(Salle *lab, Knight player);
void narratepathupgrade(Salle *lab, Knight player);
void labcreation(Salle *lab, FILE * plan);
void mainloop(Salle *lab, int sizelab);



int main(void){
    Salle lab[35] = {0};
    int l = 0;
    int sizelab = sizeof(lab)/sizeof(lab[0]);
    //FILE *file = fopen("plan.pln", "r");
    creerGrapheC(lab,
    "debutPlan "
"A1 0.N-1.S; "
"A2 1.O-2.E; "
"A3 2.N-3.S; " 
"B1 3.E-4.O; "
"B2 4.N-5.S; "
"B3 5.O-6.E; "
"A4 6.N-7.S; " 
"A4 7.O-8.E; "
"A4 8.S-9.N; "
"A4 9.S-10.N; "
"A4 10.S-11.N; "
"A4 11.S-12.N; "
"A4 7.N-13.S; "
"A4 13.O-14.E; "
"A4 14.N-15.S; "
"A4 15.O-16.E; "
"A4 16.O-17.E; "
"A4 17.N-18.S; "
"A4 18.O-19.E; "
"A4 19.N-20.S; "
"A4 20.E-21.O; "
"A4 21.E-22.O; "
"A4 22.S-23.N; "
"A4 23.E-24.O; "
"A4 24.E-25.O; "
"A4 25.N-26.S; "
"A4 26.E-27.O; "
"A4 27.S-28.N; "
"A4 27.E-29.O; " 
"A4 27.N-34.S; "
"A4 29.E-30.O; "
"A4 30.E-31.O; "
"A4 30.S-32.N; "
"A4 30.N-33.S; "
"A4 34.O-35.E; "
"finPlan "
);
    //printf("%s", lab[0]);
    //labcreation(lab, file);
    //fclose(file);
    mainloop(lab, sizelab);
    assert(nb_fichiers_ouverts==0);
    
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
            char dir[1];
            narratepathupgrade(lab, player);
            printf("Dans quelle direction aller? :");
            //lire(dir, 1);
            scanf("%[n-s-e-o-N-S-E-O]%c",&dir);
            dir[0] = toupper(dir[0]);
            printf("%c", dir[0]);
            // Après avoir tapé un charactère, celui ci est comparé avec un switch, si il est faux ou le chemin n'existe pas il est redemandé
            switch(dir[0]){
                case 'N':
                    // Verifie que la salle demandé existe
                    if (lab[player.pos].N){
                        player.pos = lab[player.pos].N->num;
                        printf("Tu prends la porte Nord et tu te retrouves dans la salle numéro %d.\n", player.pos);
                        // Si le joueur a atteind la fin du labyrinthe il gagne.
                        if (player.pos == sizelab){
                            printf("Tu viens de trouver la dernière salle ou se trouve Azatoth !");
                            found = 1;
                            restart(&loop);
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
                            restart(&loop);
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
                            restart(&loop);
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
                            restart(&loop);
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
// Visualition graphique des salles
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

// Lorsque le joueur a trouvé la dernière salle il a la possibilité de recommencer.
void restart(int *loop){
    viderBuffer();
    char decision;
    printf("\nTu as gagné ! Veux-tu recommencer? Y/N : ");
    scanf("%[y-Y-n-N]%c", &decision);
    decision = toupper(decision);
    while(decision != 'Y' && decision != 'N'){
        printf("\nC'est soit Y ou N, réessaye : ");
        viderBuffer();
        scanf("%[y-Y-n-N]%c", &decision);
    }
    if (decision == 'Y') *loop = 0;

    if (decision == 'N') *loop = 1;
}

void creerGrapheC(Salle *lab,char const * descr){
   int i = 0;
   FILE* f=ouvrir("tp9grapheTest.txt","w");

   while(descr[i]!='\0')
         putc(descr[i++],f);
   fermer(f);

   f=ouvrir("tp9grapheTest.txt","r");
   labcreation(lab,f);
   fermer(f);
}
void fermer(FILE* f){
   // pour fermer un fichier
   fclose(f);
   nb_fichiers_ouverts--;
   assert(nb_fichiers_ouverts>=0);
}

FILE* ouvrir(char* nom,char* mode){
   // pour ouvrir flux (souvent un fichier)
   // et compter le nombre de flux ouverts
   FILE* f=fopen(nom,mode);
   if(f==NULL)
   {
     fprintf(stderr,"impossible d'ouvrir le fichier %s en mode %s\n",nom,mode);
     erreur("erreur d'entree sortie\n");
   }
   nb_fichiers_ouverts++;
   return f;
}

void erreurT(char* a,int n)
{
   fprintf(stderr,"erreur ligne %d\n",n);
   fprintf(stderr,"%s",a);
   fprintf(stderr,"terminaison de l'exécution\n");
   exit(EXIT_FAILURE);
}
