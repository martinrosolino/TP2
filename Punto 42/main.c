//Ejercicio 42 TP2 - Mart�n Rosolino

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

//Prototipos de funciones
tipopuntero colafallados();
void reemplaza();
void creafallados (tipopuntero localobtinene);
void creaok (repuestos_t temp);
void vacia();

int main()
    {
    vacia();
    creafallados(colafallados());
    reemplaza();
    return 0;
    }

tipopuntero colafallados(void)
    {
    struct lista *aux;
    tipopuntero localobtinene;
    FILE *punter;

    //Inicializa punteros
    localobtinene.p=NULL;
    localobtinene.u=NULL;
    aux=NULL;

    //Struct temporal para leer datos
    repuestos_t temp;

    //Abre archivo
    punter=fopen("CosmeFulanito_stock.dat","rb");
    fread(&temp,sizeof(repuestos_t),1,punter);

    //Si no es eof sigue buscando
    while(!feof(punter))
        {
        //Verifica las condiciones para saber si estan fallados
        if(temp.partNumber==1234)
            if(temp.serialNumber&0x28)
                {
                //Reserva memoria
                aux=(struct lista *)malloc(sizeof(struct lista));

                //Copia datos
                aux->partNumber=temp.partNumber;
                aux->serialNumber=temp.serialNumber;
                strcpy(aux->descripcion,temp.descripcion);
                strcpy(aux->ubicacion,temp.ubicacion);

                //Si la cola est� vac�a
                if(localobtinene.p==NULL)
                    {
                    localobtinene.p=aux;
                    localobtinene.u=aux;
                    aux->sig=NULL;
                    aux->ant=NULL;
                    }

                //Si la cola ya tiene algun elemento lo agrega al final
                else
                    {
                    aux->sig=localobtinene.u;
                    aux->ant=NULL;
                    (localobtinene.u)->ant=aux;
                    localobtinene.u=aux;
                    }
                }
        else
            creaok(temp);

        //Lee para el proximo ciclo
        fread(&temp,sizeof(repuestos_t),1,punter);
        }
    return localobtinene;
    }

void creafallados (tipopuntero localobtinene)
    {
    struct lista *aux;
    tipopuntero localcrea;
    FILE *punter;

    //Inicializa punteros
    localcrea=localobtinene;
    aux=NULL;

    //Asigna u a aux para recorrer desde el final
    aux=localcrea.u;

    //Si aux no es el �ltimo elemento lo imprime, asigna la clave y avanza aux
    while(aux)
        {
        //Agrega los datos al nuevo archivo
        punter=fopen("CosmeFulanito_fallados.dat","ab");
        fwrite(aux,sizeof(repuestos_t),1,punter);
        fclose(punter);

        //Avanza aux al ant para recorrer en orden inverso
        aux=aux->ant;
        }
    free(aux);
    }

void creaok (repuestos_t temp)
    {
    FILE *punter;
    punter=fopen("CosmeFulanito_ok.dat","ab");
    fwrite(&temp,sizeof(repuestos_t),1,punter);
    fclose(punter);
    }

void reemplaza(void)
    {
    remove("CosmeFulanito_stock.dat");
    rename("CosmeFulanito_ok.dat","CosmeFulanito_stock.dat");
    }

void vacia(void)
    {
    FILE *punter;
    punter=fopen("CosmeFulanito_ok.dat","wb");
    fclose(punter);
    punter=fopen("CosmeFulanito_fallados.dat","wb");
    fclose(punter);
    }
