#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

//{{{ déclarations 
//{{{ macros
#define Debug(s) s
#define Drapeau fprintf(stderr,"executions ligne %d\n",__LINE__);

#define erreur(a) erreurT(a,__LINE__)
//}}}

//{{{ structure et constantes

#define MAX_NOEUD 40
typedef struct gra
{
   int graphe[MAX_NOEUD][MAX_NOEUD];
   int nbNoeud;
} Graphe;

#define TDepart 100
typedef struct file
{
   int queue;
   int tete;
   int* tab;
   int tMax;
} File;

//}}}

//{{{ entete fonctions usuelles
FILE* ouvrir(char* nom,char* mode);
void fermer(FILE*);
void erreurT(char*  a,int n);
//}}}

// entete fonctions demandées
//{{{
//}}}

// entete fonction non demandées
// {{{
void afficheGraphe(FILE* f,Graphe* g);
File* initialiserF(void);
void enfiler(File* f,int a);
int Dfiler(File* f);
int estVideF(File* f);
void detruireF(File* f);
// }}}

//}}}

//{{{ fonction usuelles


void erreurT(char* a,int n)
{
   fprintf(stderr,"erreur ligne %d\n",n);
   fprintf(stderr,"%s",a);
   fprintf(stderr,"terminaison de l'exécution\n");
   exit(EXIT_FAILURE);
}

int nb_appels_malloc=0;
int nb_fichiers_ouverts=0;


void* myMalloc(size_t a)
   // pour vérifier qu'il n'y a pas de fuite de mémoire
{
   void* r=malloc(a);
   if(r==NULL)
      erreur("impossible d'allouer de la mémoire supplémentaire\n");
   nb_appels_malloc++;
   return r;
}
#define malloc MaChinQuINEXISTE_PAS_29NFODLE018FB
void* myRealloc(void* t,size_t a)
   // redefinition de realloc
   // qui vérifie que l'allocation a reussie 
{
   void* r=realloc(t,a);
   if(r==NULL)
      erreur("impossible d'allouer de la mémoire supplémentaire\n");
   return r;
}
#define realloc MaChinQuINEXISTE_PAS_048FBDJ284JDB

void myFree(void* a)
   // pour vérifier qu'il n'y a pas de fuite de mémoire
{
   free(a);
   nb_appels_malloc--;
   assert(nb_appels_malloc>=0);
}
#define free   MaChinQuINEXISTE_PAS_08NVBZI48GH498

FILE* ouvrir(char* nom,char* mode)
   // pour ouvrir flux (souvent un fichier)
   // et compter le nombre de flux ouverts
{
   FILE* f=fopen(nom,mode);
   if(f==NULL)
   {
     fprintf(stderr,"impossible d'ouvrir le fichier %s en mode %s\n",nom,mode);
     erreur("erreur d'entree sortie\n");
   }
   nb_fichiers_ouverts++;
   return f;
}

void fermer(FILE* f)
   // pour fermer un fichier
{
   fclose(f);
   nb_fichiers_ouverts--;
   assert(nb_fichiers_ouverts>=0);
}

//}}}

//{{{ Fonctions demandées
//{{{ Exercice 1 tp9 creerGraphe
void creerGraphe(Graphe* g,FILE* grDesc)
{
   int i,j,de,ar;

   fscanf(grDesc,"%d",&g->nbNoeud);
   if(g->nbNoeud>=MAX_NOEUD)
      erreur("la description du graphe contient trop de noeuds\n");

   for(i=0;i<g->nbNoeud+1;i++)
      for(j=0;j<g->nbNoeud+1;j++)
         g->graphe[i][j]=0;

   while(fscanf(grDesc,"%d->%d",&de,&ar)==2)
   {
      if(de>g->nbNoeud || ar>g->nbNoeud || de<1 || ar<1 )
         erreur("le fichier de description du graphe est incorrect\n");
      printf("[%d][%d]\n");
      g->graphe[de][ar]=1;
   }
   if(!feof(grDesc))
         erreur("le fichier de description du graphe est incorrect\n");
}
//}}}
//{{{ Exo 2 tp9 accessible
void accessibleR(Graphe* g,int s,int* acess)
   // non demandée
   // utile dans acessible
{
   int i;
   if(acess[s]==1)
      return;
   acess[s]=1;
   for(i=1;i<=g->nbNoeud;i++)
      if(g->graphe[s][i]==1)
         accessibleR(g,i,acess);
}
void accessible(Graphe* g,int s,int* acess)
{
   int i;
   for(i=1;i<=g->nbNoeud;i++)
      acess[i]=0;
   accessibleR(g,s,acess);
}
//}}}
//{{{ Exo3 tp9 sansCircuit

/*
 * Pour savoir si un graphe est sans circuit 
 * on peut utiliser la propriété suivante
 * <<lors d'un parcours en profondeur qui passe 
 * par un circuit, un sommet visité sera 
 * re-visité avant d'être post-visité.>> 
 * La fonction sansCircuit effectue un parcours
 * en profondeur sur chaque sommet du graphe non
 * visité vérifie qu'aucune revisité n'a lieu 
 * avant une post-visite.
 */
int sansCircuitR(Graphe* g,int s,int* visite,int* predeces)
   // non demandée 
   // utile dans sansCircuit, arbre et foret
   // recherche un circuit lors d'un parcours en profondeur
   // convention: visite[i]==0 (sommet i non visité)
   // convention: visite[i]==1 (sommet prévisité mais non postvis.)
   // convention: visite[i]==2 (sommet i post-visité)
   // precesseur compte pour chaque sommet le nombre de ses prédécesseurs
{
   int i;
   if(visite[s]==1) // revisite d'un sommet non-post visité ...
      return 0; // ... donc il y a un circuit
   if(visite[s]==2)
      return 1; 
   visite[s]=1;
   for(i=1;i<=g->nbNoeud;i++)
      if(g->graphe[s][i]==1)
      {
         predeces[i]++;
         if(sansCircuitR(g,i,visite,predeces)==0)
            return 0;
      }
   visite[s]=2; // post-visite du sommet s
   return 1;
}
int sansCircuit(Graphe* g)
{
   int i;
   int visite[g->nbNoeud+1];
   int temp[g->nbNoeud+1];
   for(i=1;i<=g->nbNoeud;i++)
     visite[i]=0; 

   for(i=1;i<=g->nbNoeud;i++)
      if(sansCircuitR(g,i,visite,temp)==0)
         return 0;
   return 1;
}
//}}}
//{{{ Exo 4 tp9 forêt
/*
 * Pour vérifier qu'un graphe est une forêt
 * il faut simplement vérifier qu'il n'a aucun
 * circuit  et que tout sommet n'a au plus 
 * qu'un prédécesseur
 */
int estForet(Graphe* g)
{
   int visite[g->nbNoeud+1];
   int pred[g->nbNoeud+1];
   int i;
   for(i=1;i<=g->nbNoeud;i++)
      visite[i]=pred[i]=0;

   for(i=1;i<=g->nbNoeud;i++)
      if(sansCircuitR(g,i,visite,pred)==0)
         return 0;
   for(i=1;i<=g->nbNoeud;i++)
      if(pred[i]>1)
         return 0;
   return 1;
}
//}}}
//{{{ Exo 5 tp9 estarbre
/*
 * Pour vérifier qu'un graphe est un arbre
 * il faut simplement vérifier : 
 * - qu'il n'a aucun circuit
 * - que tout sommet a au plus 1 prédécesseur
 * - que seul un sommet n'a aucun prédécesseur
 */
int estArbre(Graphe* g)
{
   int visite[g->nbNoeud+1];
   int pred[g->nbNoeud+1];
   int compteur;
   int i;
   for(i=1;i<=g->nbNoeud;i++)
      visite[i]=pred[i]=0;
   for(i=1;i<=g->nbNoeud;i++)
      if(sansCircuitR(g,i,visite,pred)==0)
         return 0;
   for(i=1,compteur=0;i<=g->nbNoeud;i++)
      if(pred[i]>1)
         return 0;
      else if (pred[i]==0)
      {
         compteur++;
      }
   return compteur==1;
}
//}}}
//{{{ Exo 6 tp9 distance
/*
 * En effectuant un parcours en largeur 
 * d'un graphe à partir d'un sommet s  
 * grâce à une file,
 * un sommet atteint est soit ...
 * ... à la même distance
 * ... à une distance -1
 * que le prochain sommet atteint . 
 */

//{{{ fonction distance
//
void distance(Graphe* g,int s,int* dist)
{
   File* f=initialiserF();
   int i;
   int distanceActuelle;
   for(i=0;i<=g->nbNoeud;i++)
      dist[i]=-1;
   enfiler(f,s);
   enfiler(f,-1);// marque la fin du niveau 0
   distanceActuelle=0;
   while(1)
   {
      s=Dfiler(f);
      if(s==-1)
      {
         distanceActuelle++;
         if(estVideF(f))
            break;
         enfiler(f,-1);
         continue;
      }
      if(dist[s]!=-1)
         continue;
      dist[s]=distanceActuelle;
      for(i=1;i<=g->nbNoeud;i++)
         if(g->graphe[s][i]==1)
            enfiler(f,i);
   }
   detruireF(f);
}
//}}}
//
//{{{ fonctions non demandées manipulation d'une file d'entiers

void vider(File* f)
{
   f->tete=f->queue;
}
int tete(File* f)
{
   if(f->tete==f->queue)
      erreur("pile vide, impossible de renvoyer sa tete\n");
   return f->tab[f->tete];
}
File* initialiserF(void)
{
   File* f=(File*)myMalloc(sizeof(*f));
   f->queue=0;
   f->tete=0;
   f->tab=(int*)myMalloc((sizeof*f->tab)*TDepart);
   f->tMax=TDepart;
   return f;
}

void enfiler(File* f,int a)
{
   f->tab[f->queue]=a;
   f->queue=(f->queue+1)%f->tMax;
   if(f->queue==f->tete)
   {
      int i,j;
      int* temp=(int*)myMalloc((f->tMax+TDepart)*sizeof(int));
      for(i=0,j=f->tete;i<f->tMax;i++)
      {
         temp[i]=f->tab[j];
         j=(j+1)%f->tMax;
      }
      f->tMax+=TDepart;
      myFree(f->tab);
      f->tab=temp;
      f->tete=0;
      f->queue=i;
   }
}

int Dfiler(File* f)
{
   int a;
   if(f->tete==f->queue)
      erreur("file vide, impossible de retirer un élément\n");
   a=f->tab[f->tete];
   f->tete=(f->tete+1)%(f->tMax);
   return a;
}
int estVideF(File* f)
{
   return f->tete==f->queue;
}
void detruireF(File* f)
{
   myFree(f->tab);
   myFree(f);
}
//}}}

//}}}
//}}}


//{{{ fonctions non demandées utile pour pour test
//{{{ affiche graphe
void afficheGraphe(FILE* osr,Graphe* g)
{
   int i,j;
   fprintf(osr,"|-> ");
   for(j=0;j<g->nbNoeud+1;j++)
      fprintf(osr,"%3d",j);
   fprintf(osr,"\n");
   for(j=0;j<g->nbNoeud+2;j++)
      fprintf(osr,"___");
   fprintf(osr,"\n");
   for(i=0;i<g->nbNoeud+1;i++)
   {
      fprintf(osr,"%3d|",i);
      for(j=0;j<g->nbNoeud+1;j++)
         fprintf(osr,"%3d",g->graphe[i][j]);
      fprintf(osr,"\n");
   }
}
//}}}

//{{{ comparer Tableau
int comparerTableaux(int* tab,int* tab2,int taille)
   // non demandée utile pour test
   // renvoie 1 si les tableau tab et tab2 sont identique 0 sinon
{
   int i;
   for(i=0;i<taille;i++)
      if(tab[i]!=tab2[i]) 
         return 0;
   return 1;
}
//}}}

//{{{ lire tableau
void lireTableau(int* tab,char const* const chaine)
   // non demandé
   // remplis le tableau par les nombre écrit dans chaine
{
   int ncar=0;
   int ncarl;
   int i=0;
   while(sscanf(chaine+ncar,"%d%n",tab+(i++),&ncarl)==1)
   {
      ncar+=ncarl;
      sscanf(chaine+ncar," ,%n",&ncarl);
      ncar+=ncarl;
   }
}
//}}}

//{{{ afficher tableau
void afficherTableau(FILE* f,int* tab,int taille)
   // non demandée utile pour test
   // affiche un tableau
{
   if(taille==0)
   {
      fprintf(f,"fin_tableau\n");
      return;
   }
   fprintf(f,"%d ",tab[0]);
   afficherTableau(f,tab+1,taille-1);
}
//}}}

//{{{  crerGrapheC
void creerGrapheC(Graphe* g,char const * descr)
      // non demandée , utile pour test
      // construit le graphe à partir d'une chaine 
      // de caractère (se terminant par 0)
      // la fonction construit le fichier tp9grapheTest.txt
{
   int i;
   FILE* f=ouvrir("tp9grapheTest.txt","w");

   i=0;
   while(descr[i]!='\0')
         putc(descr[i++],f);
   fermer(f);

   f=ouvrir("tp9grapheTest.txt","r");
   creerGraphe(g,f);
   fermer(f);
}
//}}}

//{{{ testGraphe

void testGraphe(void)
   // non demandée utile pour test
{
   Graphe g;
   int etalon[MAX_NOEUD];
   int retour[MAX_NOEUD];

   //{{{ test sur arbre
   creerGrapheC(&g,
         //{{{
   "15 "
   "01->15 "
   "07->06 "
   "07->01 "
   "08->11 "
   "08->03 "
   "08->14 "
   "08->09 "
   "10->07 "
   "10->08 "
   "10->12 "
   "12->05 "
   "12->13 "
   "12->04 "
   "15->02 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon," 0, 1, 1, 0, 0, 0, 1, 1, 0, 0,  0,  0,  0,  0,  0,  1 ");
   accessible(&g,7,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 2, 4, 2, 2, 2, 2, 1, 1, 2,  0,  2,  1,  2,  2,  3");
   distance(&g,10,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(sansCircuit(&g));
   assert(estForet(&g));
   assert(estArbre(&g));
   //}}}

   //{{{ test sur foret non arbre
   creerGrapheC(&g,
         //{{{
   "15 "
   "01->15 "
   "07->06 "
   "07->01 "
   "08->11 "
   "08->03 "
   "08->14 "
   "08->09 "
   //"10->07 " // et 10 sont 7 des  racines
   "10->08 "
   "10->12 "
   "12->05 "
   "12->13 "
   "12->04 "
   "15->02 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon," 0, 1, 1, 0, 0, 0, 1, 1, 0, 0,  0,  0,  0,  0,  0,  1 ");
   accessible(&g,7,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0,-1,-1, 2, 2, 2,-1,-1, 1, 2,  0,  2,  1,  2,  2, -1");
   distance(&g,10,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(sansCircuit(&g));
   assert(estForet(&g));
   assert(!estArbre(&g));
   //}}}
   //
   //{{{ test sur graphe acyclique non forêt
   creerGrapheC(&g,
         //{{{
   "15 "
   "01->15 "
   "07->06 "
   "07->01 "
   "08->11 "
   "08->12 "// 12 a deux prédecesseurs
   "08->03 "
   "08->14 "
   "08->09 "
   "10->07 "
   "10->08 "
   "10->12 "
   "12->05 "
   "12->13 "
   "12->04 "
   "15->02 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon," 0, 1, 1, 0, 0, 0, 1, 1, 0, 0,  0,  0,  0,  0,  0,  1 ");
   accessible(&g,7,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 2, 4, 2, 2, 2, 2, 1, 1, 2,  0,  2,  1,  2,  2,  3");
   distance(&g,10,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(sansCircuit(&g));
   assert(!estForet(&g));
   assert(!estArbre(&g));
   //}}}
   
   //{{{ test sur arbre
   creerGrapheC(&g,
         //{{{
   "5 "
   "1->2 "
   "1->3 "
   "4->5 "
   "4->1 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon," 0, 1, 1, 1, 0, 0");
   accessible(&g,1,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 0, 1, 1,-1,-1, 2, 1, 1, 2,  0,  2,  1,  2,  2,  3");
   distance(&g,1,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(sansCircuit(&g));
   assert(estForet(&g));
   assert(estArbre(&g));
   //}}}

   //{{{ test sur graphe acyclique non forêt
   creerGrapheC(&g,
         //{{{
   "8 "
   "1->8 "
   "1->7 "
   "2->1 "
   "3->2 "
   "3->1 "
   "4->1 "
   "4->2 "
   "4->5 "
   "6->4 "
   "6->2 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon," 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,  0,  0,  0,  0,  0,  1 ");
   accessible(&g,4,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 1, 1, 0,-1,-1,-1, 2, 2, 0,  0,  0,  0,  0,  0,  3");
   distance(&g,3,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(sansCircuit(&g));
   assert(!estForet(&g));
   assert(!estArbre(&g));
   //}}}

   //{{{ test sur graphe avec Cycle
   creerGrapheC(&g,
         //{{{
   "10 "
   "10->04 "
   "10->02 "
   "01->05 "
   "01->06 "
   "01->09 "
   "02->04 "
   "02->03 "
   "03->01 "
   "03->07 "
   "03->05 "
   "04->03 "
   "04->07 "
   "05->02 "
   "07->08 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon, "0, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0,  0,  0,  0,  0,  3");
   accessible(&g,4,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 1, 2, 0, 3, 1, 2, 1, 2, 2, -1,  0,  0,  0,  0,  3");
   distance(&g,3,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(!sansCircuit(&g));
   assert(!estForet(&g));
   assert(!estArbre(&g));
   //}}}

   //{{{ test sur graphe avec Cycle
   creerGrapheC(&g,
         //{{{
   "3 "
   "1->3 "
   "1->1 "
   "3->3 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   //lireTableau(etalon, "0, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0,  0,  0,  0,  0,  3");
   //accessible(&g,4,retour);
   //assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 0,-1, 1, 3, 1, 2, 1, 2, 2, -1,  0,  0,  0,  0,  3");
   distance(&g,1,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(!sansCircuit(&g));
   assert(!estForet(&g));
   assert(!estArbre(&g));
   //}}}
   
   //{{{ test sur graphe avec Cycle
   creerGrapheC(&g,
         //{{{
   "7 "
   "1->2 "
   "2->3 "
   "3->4 "
   "4->5 "
   "5->6 "
   "6->7 "
   "7->1 "
   //}}}
   );
                     // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon, "0, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0,  0,  0,  0,  0,  3");
   accessible(&g,4,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
             
                    // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
   lireTableau(etalon,"0, 3, 4, 5, 6, 0, 1, 2, 2, 2, -1,  0,  0,  0,  0,  3");
   distance(&g,5,retour);
   assert(comparerTableaux(retour+1,etalon+1,g.nbNoeud));
   assert(!sansCircuit(&g));
   assert(!estForet(&g));
   assert(!estArbre(&g));
   //}}}
}


//}}}
//}}}


int main(void)
{
   testGraphe();
   assert(nb_appels_malloc==0);
   assert(nb_fichiers_ouverts==0);
   Drapeau
   return EXIT_SUCCESS;
}






