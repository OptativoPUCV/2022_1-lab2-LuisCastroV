#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct{
    int year;
    char title[30];
    char director[30];
}Pelicula;


int main( int argc, char *argv[] ){

    List* movies= createList();
    Pelicula* p= (Pelicula*) malloc (sizeof(Pelicula));
    p->year=2004;
    strcpy(p->title,"2046");
    strcpy(p->director,"Wong Kar Wai");
    pushBack(movies,p);

    p= (Pelicula*) malloc (sizeof(Pelicula));
    p->year=2016;
    strcpy(p->title,"Arrival");
    strcpy(p->director,"Denis Villeneuve ");
    pushBack(movies,p);


    Pelicula* aux = firstList(movies);
    while(aux!=NULL){
        printf("%s (%d)\n",aux->title,aux->year);
        aux=nextList(movies);
    }

    

    return 0;
}