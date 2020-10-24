//Ejercicio 43 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
    {
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    }repuestos_t;

struct list
    {
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    struct list *prev,*next;
    long maindate;
    };

struct stack
    {
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    struct stack *tie;
    };

typedef struct
    {
    struct list *first,*last;
    }fila;

//Prototipos
long datetoint (repuestos_t);
fila listbydate ();
struct stack * stackinorder (fila);

int main()
{
    //Guarda el punero de la pila
    struct stack *first;

    first=stackinorder(listbydate());

    return 0;
}

//Convierte fecha en 3 int
long datetoint (repuestos_t data)
    {
    //Variables auxiliares
    int day1,day2,month1,month2,year1,year2,year3,year4,finalday,finalmonth,finalyear;
    long finaldate;

    //Calculo correspondiente segun ASCII
    //0 decimal es 48 ASCII, por lo que restando 48 se obtiene el numero decimal
    day1=data.fecha[0]-48;
    day2=data.fecha[1]-48;
    finalday=(day1*10)+day2;

    month1=data.fecha[3]-48;
    month2=data.fecha[4]-48;
    finalmonth=month1*10+month2;

    year1=data.fecha[6]-48;
    year2=data.fecha[7]-48;
    year3=data.fecha[8]-48;
    year4=data.fecha[9]-48;
    finalyear=year1*1000+year2*100+year3*10+year4;

    finaldate=(finalyear)*10000+(finalmonth)*100+(finalday);

    return finaldate;
    }

//Crea una lista ordenada por fecha
fila listbydate(void)
    {
    repuestos_t data;
    struct list *aux,*r;
    fila locallist;
    FILE *file;
    //strcpy(data.fecha,"22/07/1978");

    aux=r=NULL;
    locallist.first=locallist.last=NULL;

    //Abre archivo ordenes de trabajo
    file=fopen("CosmeFulanito_ordenes.dat","rb");

    //Lee registro
    fread(&data,sizeof(repuestos_t),1,file);

    while(!feof(file))
        {
        //Reservo memoria
        aux=(struct list *)malloc(sizeof(struct list));

        //Simplifica fecha
        aux->maindate=datetoint(data);

        //Si la lista est� vac�a
        if(locallist.first==NULL)
            {
            locallist.first=aux;
            locallist.last=aux;
            aux->next=NULL;
            aux->prev=NULL;
            }

        //Si la lista contiene alg�n elemento
        else
            {
            r=locallist.first;

            //El dato a ubicar est� antes del primero
            if((aux->maindate)<(locallist.first)->maindate)
                {
                aux->next=locallist.first;
                aux->prev=NULL;
                (locallist.first)->prev=aux;
                locallist.first=aux;
                }

            //El dato a ubicar est� en otro lugar
            else
                {
                while(r->next)
                    {
                    if((aux->maindate)>=(r->maindate))
                        r=r->next;
                    else
                        break;
                    }

                //El dato se posicion� �ltimo
                if(r==locallist.last)
                    {
                    (locallist.last)->next=aux;
                    aux->prev=locallist.last;
                    locallist.last=aux;
                    aux->next=NULL;
                    }

                //El dato se posicion� en otro lugar
                else
                    {
                    aux->next=r->next;
                    aux->prev=r;
                    r->next=aux;
                    }
                }
            }
        //Lee registro para proximo ciclo
        fread(&data,sizeof(repuestos_t),1,file);
        }

    fclose(file);
    free(aux);

    //Retorna locallist con la info de los punteros primero y ultimo para apilar en orden
    return locallist;
    }

//Crea la pila pedida
struct stack * stackinorder(fila locallist)
    {
    fila localstack;
    localstack=locallist;
    struct list *auxlist;
    struct stack *auxstack,*first;

    auxlist=NULL;
    auxstack=NULL;
    first=NULL;

    //Asigna localstack.last a auxlist para recorrer la lista desde el principio
    auxlist=localstack.last;

    //Mientras auxllist sea distinto de NULL apila
    while(auxlist)
        {
        //Reservo memoria
        auxstack=(struct stack *)malloc(sizeof(struct stack));

        //Traspasa datos de la struct de la lista a la de la pila
        auxstack->numeroDeOrden=auxlist->numeroDeOrden;
        strcpy(auxstack->cliente,auxlist->cliente);
        strcpy(auxstack->descripciondeFalla,auxlist->descripciondeFalla);
        strcpy(auxstack->modelo,auxlist->modelo);
        strcpy(auxstack->fecha,auxlist->fecha);
        strcpy(auxstack->hora,auxlist->hora);

        //Asigna punteros
        auxstack->tie=first;
        first=auxstack;

        //Avanza auxlist
        auxlist=auxlist->prev;
        }

    //Retorna el puntero de la pila
    return first;
    }


