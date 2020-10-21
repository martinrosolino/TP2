//Ejercicio 36 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vacia ();
void guardaylista (p);
void funcion(p);

struct lista{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            long int clave;
            struct lista *ant,*sig;
            };

int main()
    {
    struct lista *p=NULL;
    vacia();
    funcion(p);
    guardaylista(p);
    return 0;
    }

void funcion (struct lista *p)
    {
    //Ciclo principal
    FILE *viejo,*nuevo;
    struct lista *r,*aux,*u;

    //Inicializo punteros
    r=aux=u=NULL;

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
            if(p==NULL)
                {
                p=u=aux;
                aux->sig=NULL;
                aux->ant=NULL;
                }

            //Si la lista contiene algún elemento
            else
                {
                r=p;
                int op=1;
                while(op!=0)
                    {
                    //El dato a ubicar está antes del primero
                    if(strcmp(aux->nombre,p->nombre)<=0)
                        {
                        aux->sig=p;
                        p->ant=aux;
                        p=aux;
                        op=0;
                        break;
                        }

                    //El dato a ubicar está en otro lugar
                    while(r->sig)
                        if(strcmp(aux->nombre,r->sig->nombre)>=0)
                            r=r->sig;
                        else
                            {
                            op=0;
                            break;
                            }

                    //El dato se posicionó último
                    if(r==u)
                        {
                        u->sig=aux;
                        aux->ant=u;
                        u=aux;
                        aux->sig=NULL;
                        op=0;
                        break;
                        }

                    //El dato se posicionó en otro lugar
                    else
                        {
                        aux->sig=r->sig;
                        aux->ant=r->sig;
                        r->sig=aux;
                        }
                    }
                }
            }
        }
    free(aux);
    fclose(viejo);
    }

void guardaylista (struct lista *p)
    {
    long i=0;
    struct lista *aux;
    FILE *nuevo;

    //Asigno p a aux para recorrer desde el principio
    aux=p;

    //Si aux no es el último elemento realiza las tareas, asigna la clave y avanza aux
    while(aux)
        {
        i++;

        //Agrega al nuevo archivo
        nuevo=fopen("Contactos_ordenados.dat","ab");
        aux->clave=i;//Agigna clave
        fwrite(aux,104,1,nuevo);//104 es el sizeof de la struct hasta la clave, sin sus punteros ant y sig
        fclose(nuevo);

        //Impresion
        printf("\n--------------------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n--------------------\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);

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
