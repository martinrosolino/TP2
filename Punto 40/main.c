//Ejercicio 40 TP2 - Mart�n Rosolino

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
    int c;
    char palabra[60],aux[10],*s,*i;


    //Pasa letra por letra
    for(c=0;c<strlen(desc);c++)
        {
        //Si es un espacio sale del ciclo
        if (desc[c]==' ')
            break;

        //Mientras no sea un espacio va agregando letras
        strcat(palabra,desc[c]);
        }
    s=&palabra[0];
    i=aux;
    while(*s)
        s++;
    s--;
    while(s!=&palabra[0])
        {
        *i=*s;
        i++;
        *i=0;
        }

    //Retorna la palabra invertida
    return aux;
    }


struct pila * funcion (long int clave,struct pila *p)
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

        //Permuta el bit 3 de estado
        bf.estado=bf.estado^(0000000000001000);

        //Mueve el cursor a la posicion adecuada
        fseek(punter,(long)sizeof(struct datos)*(clave-1),0);

        //Reescribe el archivo
        fwrite(&bf,sizeof(struct datos),1,punter);

        //Si los bits 0 y 2 estan prendidos hace las tareas
        if(bf.estado&(0000000000000101))
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
            //Escribe el archivo de salida
            punter=fopen("salida.dat","ab");
            fwrite(&bf,sizeof(struct datos),1,punter);
            fclose(punter);
            }
        }
    //Retorna p para poder ubicarse en el proximo ciclo
    return p;
    }
