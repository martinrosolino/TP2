//Ejercicio 44 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cambio el nombre de la struct ya que es el mismo que la otra struct y ocasionaria confusiones
typedef struct
    {
    long numeroDeOrden;
    char cliente[40];
    char descripciondeFalla[200];
    char modelo[65];
    char fecha[10];
    char hora[10];
    }ordenestrabajo_t;

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

typedef struct
    {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[100];
    }repuestos_t;

//Saco el typedef para poder definir los punteros
struct extraccionRepuestos_t
    {
    repuestos_t repuesto;
    int cantidad;
    struct extraccionRepuestos_t *prev,*next;
    };

//Prototipos
long datetoint (ordenestrabajo_t);
fila listbydate ();
struct stack * stackinorder (fila);
void extraction(struct stack *);

int main()
{
    //Guarda el punero de la pila
    struct stack *first;

    extraction(stackinorder(listbydate()));

    return 0;
}

//Convierte fecha en int
long datetoint (ordenestrabajo_t data)
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
    ordenestrabajo_t data;
    struct list *aux,*r;
    fila locallist;
    FILE *file;
    //strcpy(data.fecha,"22/07/1978");

    aux=r=NULL;
    locallist.first=locallist.last=NULL;

    //Abre archivo ordenes de trabajo
    file=fopen("CosmeFulanito_ordenes.dat","rb");

    //Lee registro
    fread(&data,sizeof(ordenestrabajo_t),1,file);

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
        fread(&data,sizeof(ordenestrabajo_t),1,file);
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

void extraction(struct stack *first_stack)
    {
    struct stack *first_list;
    first_list=first_stack;
    struct extraccionRepuestos_t *aux,*first,*last,*r;
    long partno,serialno;
    char desc[40],loc[100];
    int quan,flag=0;

    //Inicializa punetors
    aux=first=last=r=NULL;

    //Ciclo de desapilado y carga
    while(first_list)
        {
        //Reserva memoria
        aux=(struct extraccionRepuestos_t *)malloc(sizeof(struct extraccionRepuestos_t));

        //Carga datos del repuesto necesario
        printf("Ingrese Part Number: ");
        scanf("%ld",&partno);
        aux->repuesto.partNumber=partno;
        fflush(stdin);

        printf("Ingrese Serial Number: ");
        scanf("%ld",&serialno);
        aux->repuesto.serialNumber=serialno;
        fflush(stdin);

        printf("Ingrese descripcion: ");
        scanf("%s",desc);
        strcpy(aux->repuesto.descripcion,desc);
        fflush(stdin);

        printf("Ingrese ubicacion: ");
        scanf("%s",loc);
        strcpy(aux->repuesto.ubicacion,loc);
        fflush(stdin);

        printf("Ingrese cantidad: ");
        scanf("%d",&quan);
        aux->cantidad=quan;
        fflush(stdin);

        //Si la lista esta vacia
        if(first==NULL)
            {
            first=last=aux;
            aux->next=aux->prev=NULL;
            }

        //Si coontiene algun elemento
        else
            {
            r=first;

            //Recorre la lista para ver si ese repuesto ya fue pedido
            while(r)
                {
                //Si ya fue pedido aumenta la cantidad y mueve flag a 1
                if(aux==r)
                    {
                    r->cantidad=r->cantidad+quan;
                    flag=1;
                    break;
                    }
                else
                    r=r->next;
                }
            //Si no fue pedido antes lo carga a la lista como elemento nuevo
            if(flag!=1)
                {
                aux->next=first;
                aux->prev=NULL;
                first->prev=aux;
                first=aux;
                }
            }

        //Desapila un elemento
        first_list=first_list->tie;
        }
    printf("Pila de ordenes vacia\n");
    }
