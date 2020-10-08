//Ejercicio 36 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            struct lista *ant,*sig;
            };

int main()
    {
    FILE *viejo,*nuevo;
    struct lista *p,*r,*aux,*u;

    //Para copiar y escribir en el archivo los datos de la struct original pero sin los punteros
    struct contactos{
        char nombre[15],apellido[15],telefono[15],mail[50];
        int edad;
        }bf;

    //Inicializo punteros
    p=r=aux=u=NULL;

    //Ciclo principal
    viejo=fopen("Contactos.dat","rb");
    while(!feof(viejo))
        {
        //Asigno memoria
        aux=(struct lista *)malloc(sizeof(struct lista));

        if(aux)
            {
            //Extraigo datos del archivo

            fscanf("%s",aux->nombre);
            strcpy(bf.nombre,aux->nombre);
            fscanf("%s",aux->apellido);
            strcpy(bf.apellido,aux->apellido);
            fscanf("%s",aux->telefono);
            strcpy(bf.telefono,aux->telefono);
            fscanf("%s",aux->mail);
            strcpy(bf.mail,aux->mail);
            fscanf("%d",aux->edad);
            strcpy(bf.edad,aux->edad);


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
                while(1)
                    {

                    //El dato a ubicar está antes del primero
                    if(aux->edad<p->edad)
                        {
                        aux->sig=p;
                        p->ant=aux;
                        p=aux;
                        break;
                        }

                    //El dato a ubicar está en otro lugar
                    while(r->sig)
                        if(r->sig->edad<aux->edad)
                            r=r->sig;
                        else
                            break;

                    //El dato se posicionó último
                    if(r==u)
                        {
                        u->sig=aux;
                        aux->ant=u;
                        u=aux;
                        aux->sig=NULL;
                        break;
                        }

                    //El dato se posicionó en otro lugar
                    aux->sig=r->sig;
                    aux->ant=r->sig;
                    r->sig=aux;
                    }
                }
            }

        //Asigno p a aux para recorrer desde el principio
        aux=p;

        //Mientras aux no sea el último elemento lo imprime y avanza aux
        while(aux)
            {
            printf("----------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);
            aux=aux->sig;
            }

        //Libero memoria
        free(aux);

        //Agrego al nuevo archivo
        nuevo=fopen("Contactos_ordenados.dat","ab");
        fwrite(&bf,sizeof(struct contactos),1,nuevo);
        fclose(nuevo);
        }
    fclose(viejo);
    return 0;
    }
