#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void insertion(Liste *liste, int nvNombre);

int main(int argc, char** argv){

}
typedef struct Element Element;
struct Element{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste{
    Element *premier;
};
Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

void insertion(Liste *liste, int nvNombre);
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}
