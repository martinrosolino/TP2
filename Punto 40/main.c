//Ejercicio 40 TP2 - Martin Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    int clave;
    };

struct pila
    {
    unsigned char potencia;
    struct pila *lazo;
    };

char* extraeycambia (char desc[60])
    {
    int i;
    char primera[60];

    //Pasa letra por letra
    for(i=0;i<strlen(desc);i++)
        {
        //Si es un espacio sale del ciclo
        if (desc[i]==' ')
            break;

        //Mientras no sea un espacio va agregando letras
        strcat(primera,desc[i]);
        }

    //Retorna la palabra invertida
    return strrev(primera);
    }


void funcion (long int clave,struct pila *p)
    {
    struct pila *aux;
    struct datos bf;
    FILE *punter;

    //Lee clave
    printf("Clave: ");
    scanf("%ld",&clave);

    //Abre archivo
    punter=fopen("potencia.dat","rb+");

    //Mueve el cursor a la posicion indicada
    fseek(punter,(long)sizeof(struct datos)*(clave-1),0);
    fread(&bf,sizeof(struct datos),1,punter);

    //Si coinciden las claves hace las tareas
    if(bf.clave==clave)
        {
        //Imprime la primer palabra de la desc al reves
        printf("%s",extraeycambia(bf.desc));

        //Permuta el estado del bit 3 de estado
        bf.estado=bf.estado^(0000000000001000);

        //Mueve el cursor a la posicion adecuada
        fseek(punter,(long)sizeof(struct datos)*(clave-1),0);

        //Reescribe el archivo
        fwrite(&bf,sizeof(struct datos),1,punter);

        //Si los bits 0 y 2 estan prendidos hace las tareas
        if(bf.estado&(1<<0000000000000101))
            {
            //Reserva lugar
            aux=(struct pila *) malloc(sizeof(struct pila));

            //Carga dato
            strcpy(aux->potencia,bf.potencia);

            //Asigna punteros
            aux->lazo=p;
            p=aux;
            }
        else
            {
            //Abre archivo salida
            punter=fopen("salida.dat","ab");

            //Escribe el archivo
            fwrite(&bf,sizeof(struct datos),1,punter);
            }
        }
    //Retorna p para poder ubicarse en el proximo ciclo
    return p;
    }

