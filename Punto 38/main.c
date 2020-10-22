//Ejercicio 38 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define pi 3.14159265358979323846

struct base
    {
    signed char valor;
    struct base *ant,*sig;
    };

int main()
    {
    float a,x;
    struct base *p,*u,*aux;
    p=u=aux=NULL;

    //x va aumentando de a 5 grados hasta llegar a los 90 que son el cuarto de se�al
    for(x=0;x<=(pi/2);x=x+(pi/36))
        {
        aux=(struct base *) malloc(sizeof(struct base));
        a=sin(x)*127;
        aux->valor=a;

        //Primer elemento
        if(p==NULL)
            {
            aux->ant=NULL;
            aux->sig=NULL;
            p=u=aux;
            }

        //Otro elemento
        else
            {
            u->sig=aux;
            aux->ant=u;
            aux->sig=NULL;
            u=aux;
            }
        }

    //Primer ciclo
    aux=p;
    while(aux)
        {
        printf("%hhi / ",aux->valor);
        aux=aux->sig;
        }

    //Segundo ciclo
    aux=u->ant;
    while(aux)
        {
        printf("%hhi / ",aux->valor);
        aux=aux->ant;
        }

    //Tercer ciclo
    aux=p->sig;
    while(aux)
        {
        printf("%hhi / ",~(aux->valor)+1);
        aux=aux->sig;
        }

    //Cuarto ciclo
    aux=u->ant;
    while(aux)
        {
        printf("%hhi / ",~(aux->valor)+1);
        aux=aux->ant;
        }

    free(aux);
    return 0;
    }
