//Ejercicio 36 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            long int clave;
            struct lista *ant,*sig;
            };

typedef struct
    {
    struct lista *p,*u;
    }tipopuntero;

void vacia ();
void guardaylista (tipopuntero gral);
tipopuntero funcion(tipopuntero gral);

int main()
    {
    tipopuntero gral;
    gral.p=NULL;
    gral.u=NULL;
    guardaylista(funcion(gral));
    return 0;
    }

tipopuntero funcion (tipopuntero gral)
    {
    vacia();
    //Ciclo principal
    FILE *viejo,*nuevo;
    struct lista *r,*aux;
    tipopuntero local;
    local=gral;

    //Inicializo punteros
    r=aux=NULL;

    viejo=fopen("Contactos.dat","rb");
    while(!feof(viejo))
        {
        //Asigno memoria
        aux=(struct lista *)malloc(sizeof(struct lista));

        //Si aux es NULL es porque el malloc fallo
        if(aux)
            {
            //Extraigo datos del archivo
            fread(aux,100,1,viejo);

            //Si la lista está vacía
            if(local.p==NULL)
                {
                local.p=aux;
                local.u=aux;
                aux->sig=NULL;
                aux->ant=NULL;
                }

            //Si la lista contiene algún elemento
            else
                {
                r=local.p;

                //El dato a ubicar está antes del primero
                if(strcmp(aux->nombre,(local.p)->nombre)<=0)
                    {
                    aux->sig=local.p;
                    aux->ant=NULL;
                    (local.p)->ant=aux;
                    local.p=aux;
                    }

                //El dato a ubicar está en otro lugar
                else
                    {
                    while(r->sig)
                        {
                        if(strcmp(aux->nombre,r->sig->nombre)>=0)
                            r=r->sig;
                        else
                            break;
                        }

                    //El dato se posicionó último
                    if(r==local.u)
                        {
                        (local.u)->sig=aux;
                        aux->ant=local.u;
                        local.u=aux;
                        aux->sig=NULL;
                        }

                    //El dato se posicionó en otro lugar
                    else
                        {
                        aux->sig=r->sig;
                        aux->ant=r;
                        r->sig=aux;
                        }
                    }
                }
            }
        }
    free(aux);
    fclose(viejo);
    return local;
    }

void guardaylista (tipopuntero gral)
    {
    long i=0;
    struct lista *aux;
    FILE *nuevo;

    //Asigno p a aux para recorrer desde el principio
    aux=gral.p;

    //Si aux no es el último elemento realiza las tareas, asigna la clave y avanza aux
    while(aux)
        {
        i++;
        aux->clave=i;//Agigna clave
        //Agrega al nuevo archivo
        nuevo=fopen("Contactos_ordenados.dat","ab");
        fwrite(aux,104,1,nuevo);//104 es el sizeof de la struct hasta la clave, sin sus punteros ant y sig
        fclose(nuevo);

        //Impresion
        printf("--------------------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n--------------------\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);

        //Avanza aux al siguiente elemento
        aux=aux->sig;
        }
    free(aux);
    }

void vacia (void)
    {
    FILE *fp;
    fp=fopen("Contactos_ordenados.dat","w");
    fclose(fp);
    }
