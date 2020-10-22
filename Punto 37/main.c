//Ejercicio 37 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>

//Estructura archivo dado
struct d
    {
    long clave;
    char d[30];
    unsigned char tipo;
    char b;
    };

//Estructura base de la pila
struct pila
    {
    long clave,posicion;
    struct pila *lazo;
    };

//Prototipo de la funcion
struct pila * funcion (long clave,struct pila *p);

//Descripcion de la funcion
struct pila * funcion (long clave,struct pila *p)
        {
        int b=0;
        long i=0;
        struct pila *aux=NULL;
        struct d estructura;
        FILE *puntero;
        puntero=fopen("datos.dat","rb");
        fread(&estructura,sizeof(struct d),1,puntero);
        while(!feof(puntero))
            {
            i++;
            if(estructura.clave==clave)
                {
                if((estructura.tipo)&(00010000))
                    {
                    aux=(struct pila *) malloc(sizeof(struct pila));
                    aux->clave=estructura.clave;
                    aux->posicion=i;
                    aux->lazo=p;
                    p=aux;
                    }
                b=1;
                break;
                }
            fread(&estructura,sizeof(struct d),1,puntero);
            }
        if(b==0)
            printf("Registro no encontrado\n");
        return p;
        }

//Ciclo principal
int main()
    {
    long id;
    int op=1;
    FILE *puntero;
    struct pila *punter=NULL,*aux;
    struct d estructura;

    //Ciclo apilado
    while(op==1)
        {
        printf("Clave: ");
        scanf("%ld",&id);
        punter=funcion(id,punter);
        printf("1 para seguir, otro para salir: ");
        scanf("%d",&op);
        }

    //Impresion
    puntero=fopen("datos.dat","rb");
    fread(&estructura,sizeof(struct d),1,puntero);

    //Asigno aux al primer elemento para recorrer desde el principio
    aux=punter;

    while(!feof(puntero))
        {
        //Si la clave del registro coincide con la primera de la pila imprime y avanza aux
        if(estructura.clave==aux->clave)
            {
            printf("ACA ESTOY");
            printf("%s\n",estructura.d);
            aux=aux->lazo;
            }
        fread(&estructura,sizeof(struct d),1,puntero);
        }
    return 0;
    }
