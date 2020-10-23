//Ejercicio 41 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
    {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    }repuestos_t;

struct lista
    {
    long partNumber;
    long serialNumber;
    char descripcion[40];
    char ubicacion[40];
    struct lista *ant,*sig;
    };

typedef struct
    {
    struct lista *p,*u;
    }tipopuntero;

tipopuntero carga (tipopuntero gral);
void imrpime (tipopuntero gral);
void guarda (tipopuntero gral);
void vacia ();

int main()
{
    int op=1;
    tipopuntero gral;
    gral.p=NULL;
    gral.u=NULL;
    vacia();

    while (op!=0)
        {
        gral=carga(gral);
        imprime(gral);
        printf("\nIngrese 0 para salir, otro para seguir: ");
        scanf("%d",&op);
        }
    guarda(gral);
    printf("\n");

    return 0;
}

//Funcion para la carga de la lista
tipopuntero carga (tipopuntero gral)
    {
    repuestos_t hola;

    //Punteros primero y ultimo locales
    tipopuntero local;
    local.p=gral.p;
    local.u=gral.u;

    //Punteros auxiliares para ordenar la lista
    struct lista *aux,*r;
    r=aux=NULL;

    //Reserva memoria
    aux=(struct lista *)malloc(sizeof(struct lista));

    //Lee datos
    printf("\nIngrese Part Number: ");
    scanf("%ld",&hola.partNumber);
    aux->partNumber=hola.partNumber;
    fflush(stdin);

    printf("Ingrese Serial Number: ");
    scanf("%ld",&hola.serialNumber);
    aux->serialNumber=hola.serialNumber;
    fflush(stdin);

    printf("Ingrese Descripcion: ");
    scanf("%s",hola.descripcion);
    strcpy(aux->descripcion,hola.descripcion);
    fflush(stdin);

    printf("Ingrese Ubicacion: ");
    scanf("%s",hola.ubicacion);
    strcpy(aux->ubicacion,hola.ubicacion);
    fflush(stdin);


    //Si la lista est� vac�a
    if(local.p==NULL)
        {
        local.p=aux;
        local.u=aux;
        aux->sig=NULL;
        aux->ant=NULL;
        }

    //Si la lista contiene alg�n elemento
    else
        {
        r=local.p;

        //El dato a ubicar est� antes del primero
        if(strcmp(aux->descripcion,(local.p)->descripcion)<=0)
            {
            aux->sig=local.p;
            aux->ant=NULL;
            (local.p)->ant=aux;
            local.p=aux;
            }

        //El dato a ubicar est� en otro lugar
        else
            {
            while(r->sig)
                {
                if(strcmp(aux->descripcion,r->sig->descripcion)>=0)
                    r=r->sig;
                else
                    break;
                }

            //El dato se posicion� �ltimo
            if(r==local.u)
                {
                (local.u)->sig=aux;
                aux->ant=local.u;
                local.u=aux;
                aux->sig=NULL;
                }

            //El dato se posicion� en otro lugar
            else
                {
                aux->sig=r->sig;
                aux->ant=r;
                r->sig=aux;
                }
            }
        }
    return local;
    }

void imprime (tipopuntero gral)
    {
    struct lista *aux;
    int i=0;
    //Asigno p a aux para recorrer desde el principio
    aux=gral.p;

    //Si aux no es el �ltimo elemento imprime y avanza aux
    while(aux)
        {
        i++;
        printf("\n----------%d----------\nPart Number: %ld\nSerial Number: %ld\nDescripcion: %s\nUbicacion: %s\n---------------------\n",i,aux->partNumber,aux->serialNumber,aux->descripcion,aux->ubicacion);

        //Avanza aux al siguiente elemento
        aux=aux->sig;
        }
    free(aux);
    }

void guarda (tipopuntero gral)
    {
    long i=0;
    struct lista *aux;
    FILE *punter;

    //Asigno p a aux para recorrer desde el principio
    aux=gral.p;

    //Si aux no es el �ltimo elemento escribe y avanza aux
    while(aux)
        {
        i++;
        int size;
        punter=fopen("CosmeFulanito_stock.dat","ab");
        size=fwrite(aux,sizeof(struct lista),1,punter);
        if(size)
            printf("\nRegistro %ld guardado con exito",i);
        fclose(punter);

        //Avanza aux al siguiente elemento
        aux=aux->sig;
        }
    free(aux);
    }

void vacia (void)
    {
    FILE *punter;
    punter=fopen("CosmeFulanito_stock.dat","w");
    fclose(punter);
    }
