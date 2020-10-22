//Ejercicio 39 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
    {
    struct lista *p,*u;
    }tipopunteros;

//Estructura dada
struct datos
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    };

//Estructura base de la lista
struct lista
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    struct lista *sig,*ant;
    };

unsigned int obtenerestado(hola);
void vacia();
void imprimeyguarda(pu);
tipopunteros funcion(pu);

int main()
    {
    int op=1;
    tipopunteros pu;
    pu.p=pu.u=NULL;
    vacia();

    while(op!=0)
        {
        pu=funcion(pu);
        //Salida
        printf("0 para salir, otro para seguir: ");
        scanf("%d",&op);
        fflush(stdin);
        }
        imprimeyguarda(pu);
    return 0;
    }

    //Funciones:

tipopunteros funcion(tipopunteros pu)
    {
    struct datos hola;
    struct lista *r,*aux;

    //Inicializo punteros
    r=aux=NULL;

    //Carga datos
    printf("Descripcion: ");
    scanf("%s",hola.desc);
    fflush(stdin);
    printf("Potencia: ");
    scanf("%hhi",&hola.potencia);
    fflush(stdin);

    //Reservo memoria
    aux=(struct lista *)malloc(sizeof(struct lista));

    //Copio datos
    strcpy(aux->desc,hola.desc);
    aux->potencia=hola.potencia;
    aux->estado=obtenerestado(hola);

    //Si la lista est� vac�a
    if((pu.p)==NULL)
        {
        (pu.p)=aux;
        (pu.u)=aux;
        aux->sig=NULL;
        aux->ant=NULL;
        }

    //Si la lista contiene alg�n elemento
    else
        {
        r=(pu.p);

        //El dato a ubicar est� antes del primero
        if(aux->potencia>=(pu.p)->potencia)
            {
            aux->sig=(pu.p);
            (pu.p)->ant=aux;
            aux->ant=NULL;
            (pu.p)=aux;
            }

        //El dato a ubicar est� en otro lugar
        else
            {
            while(r->sig)
                {
                if(aux->potencia<r->potencia)
                    r=r->sig;
                else
                    break;
                }

            //El dato se posicion� �ltimo
            if(r==(pu.u))
                {
                (pu.u)->sig=aux;
                aux->ant=(pu.u);
                (pu.u)=aux;
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
    return pu;
    }

unsigned int obtenerestado(struct datos hola)
    {
    unsigned int ascii;
    int i=0;

    //Obtengo el ascii de la primer letra de la desc
    ascii=hola.desc[0];

    //Retorna el valor correspondiente de estado
    return ascii*hola.potencia;
    }

void imprimeyguarda (tipopunteros pu)
    {
    struct lista *aux;
    int j=0;
    FILE *punter;

    //Asigna p a aux para recorrer desde el principio
    aux=(pu.p);

    //Si aux no es el �ltimo elemento lo imprime, asigna la clave y avanza aux
    while(aux)
        {
        j++;

        //Agrega los datos al nuevo archivo
        punter=fopen("potencia.dat","ab");
        fwrite(aux,sizeof(struct datos),1,punter);
        fclose(punter);

        //Agrega la clave al nuevo archivo
        punter=fopen("potencia.dat","ab");
        fwrite(&j,sizeof(int),1,punter);
        fclose(punter);

        //Impresion
        printf("\n--------------------\nDescripcion: %s\nPotencia: %hhi\nEstado: %d\n--------------------\n",aux->desc,aux->potencia,aux->estado);

        //Avanza aux
        aux=aux->sig;
        }
    free(aux);
    }

void vacia (void)
    {
    FILE *punter;
    punter=fopen("potencia.dat","wb");
    fclose(punter);
    }
