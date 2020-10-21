//Ejercicio 39 TP2 - Martin Rosolino

#include <stdio.h>
#include <stdlib.h>

struct datos
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    };

struct lista
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    struct lista *sig,*ant;
    };

int main()
    {
    FILE *punter;
    int i,op=1,j=0;
    unsigned int ascii,pot;
    struct datos hola;
    struct lista *p,*r,*aux,*u;

    //Vacio fichero
    punter=fopen("potencia.dat","wb");
    fclose(punter);

    //Inicializo punteros
    p=r=aux=u=NULL;

    while(op!=0)
        {
        //Carga de datos
        printf("Descripcion: ");
        scanf("%[^\n]",&hola.desc);
        fflush(stdin);
        printf("Potencia: ");
        scanf("%c",&hola.potencia);
        fflush(stdin);

        //Obtengo el ascii de la primer letra de la desc
        ascii=hola.desc[0];

        //Obtengo el ascii de la potencia
        pot=hola.potencia;

        //Segun el ascii de la potencia le asigno su valor int
        for(i=0;i<10;i++)
            if(pot==48+i)
                {
                pot=i;
                break;
                }

        //Asigno el valor correspondiente a hola.estado
        hola.estado=ascii*pot;

        //Reservo memoria
        aux=(struct lista *)malloc(sizeof(struct lista));

        //Si la lista esta vacia
        if(p==NULL)
            {
            p=u=aux;
            aux->sig=NULL;
            aux->ant=NULL;
            }

        //Si la lista contiene algun elemento
        else
            {
            r=p;
            while(1)
                {
                //El dato a ubicar esta antes del primero
                if(pot>p->potencia)
                    {
                    aux->sig=p;
                    p->ant=aux;
                    aux->ant=NULL;
                    p=aux;
                    break;
                    }

                //El dato a ubicar esta en otro lugar
                while(r->sig)
                    if(pot<r->potencia)
                        r=r->sig;
                    else
                        break;

                //El dato se posiciono ultimo
                if(r==u)
                    {
                    u->sig=aux;
                    aux->ant=u;
                    u=aux;
                    aux->sig=NULL;
                    break;
                    }

                //El dato se posiciono en otro lugar
                aux->sig=r->sig;
                aux->ant=r;
                r->sig=aux;
                }
            }
        //Salida
        printf("0 para salir, otro para seguir: ");
        scanf("%d",&op);
        fflush(stdin);
        }

    //Asigna p a aux para recorrer desde el principio
    aux=p;

    //Si aux no es el ultimo elemento lo imprime, asigna la clave y avanza aux
    while(aux)
        {
        j++;

        //Agrega al nuevo archivo
        punter=fopen("potencia.dat","ab");
        fwrite(aux,sizeof(struct datos),1,punter);
        fwrite(j,sizeof(int),1,punter);
        fclose(punter);

        //Impresion
        printf("\n--------------------\nDescripcion: %s\nPotencia: %c\nEstado: %d\n--------------------\n",aux->desc,aux->potencia,aux->estado);

        //Avanza aux
        aux=aux->sig;
        }

    free(aux);
    return 0;
    }
