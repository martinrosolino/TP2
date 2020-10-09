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

    //Vacio fichero
    nuevo=fopen("Contactos_ordenados.dat","w");
    fclose(nuevo);

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
            fread(&bf,sizeof(struct contactos),1,viejo);
            strcpy(aux->nombre,bf.nombre);
            strcpy(aux->apellido,bf.apellido);
            strcpy(aux->telefono,bf.telefono);
            strcpy(aux->mail,bf.mail);
            aux->edad=bf.edad;

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
                    if(strcmp(aux->nombre,p->nombre)<=0)
                        {
                        aux->sig=p;
                        p->ant=aux;
                        p=aux;
                        break;
                        }

                    //El dato a ubicar está en otro lugar
                    while(r->sig)
                        if(strcmp(aux->nombre,r->sig->nombre)>=0)
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
        //Agrego al nuevo archivo
        nuevo=fopen("Contactos_ordenados.dat","ab");
        fwrite(&bf,sizeof(struct contactos),1,nuevo);
        fclose(nuevo);

        fread(&bf,sizeof(struct contactos),1,viejo);
        }

    //Asigno p a aux para recorrer desde el principio
    aux=p;

    //Si aux no es el último elemento lo imprime y avanza aux
    while(aux)
        {
        printf("\n--------------------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n--------------------\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);
        aux=aux->sig;
        }

    //Buenas practicas
    free(aux);
    fclose(viejo);

    return 0;
    }
