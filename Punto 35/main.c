//Ejercicio 35 TP2 - Martin Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listar ();
void vacia ();
void agregar(p);

struct pila{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            struct pila *lazo;
            };

int main()
    {
    int op=1;
    struct pila *p=NULL;
    vacia();
    while(op!=0)
        {
        printf("0. Salir\n1. Agregar\n2. Listar\nIngrese: ");
        scanf("%d",&op);
        switch(op)
            {
            case 0:
                break;
            case 1:
                agregar(p);
            case 2:
                listar();
            }
        }
    return 0;
    }


void agregar (struct pila *p)
        {
        char quince[15],cincuenta[50];
        int age;
        FILE *fp;
        struct pila *aux;

        //Pongo la pila en cero
        aux=NULL;

        //Obtengo los datos
        printf("----------\nNombre: ");
        scanf("%s",quince);
        strcpy(aux->nombre,quince);
        fflush(stdin);

        printf("Apellido: ");
        scanf("%s",quince);
        strcpy(aux->apellido,quince);
        fflush(stdin);

        printf("Telefono: ");
        scanf("%s",quince);
        strcpy(aux->telefono,quince);
        fflush(stdin);

        printf("Mail: ");
        scanf("%s",cincuenta);
        strcpy(aux->mail,cincuenta);
        fflush(stdin);

        printf("Edad: ");
        scanf("%d",&age);
        aux->edad=age;
        fflush(stdin);

        //Reservo lugar
        aux=(struct pila *) malloc(sizeof(struct pila));

        //Asigno punteros
        aux->lazo=p;
        p=aux;

        //Agrego al archivo
        if(aux->edad>21)
            {
            fp=fopen("Contactos.dat","ab");
            fwrite(aux,100,1,fp);
            fclose(fp);
            }
        free(aux);
        return p;
        }


void listar (void)
    {
    FILE *fp;
    struct pila *aux=NULL;
    fp=fopen("Contactos.dat","rb");
        while(!feof(fp))
            {
            fread(aux,100,1,fp);
            fprintf(stdout,"----------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);
            fread(aux,100,1,fp);
            }
    fclose(fp);
    free(aux);
    }


void vacia (void)
    {
    FILE *fp;
    fp=fopen("Contactos.dat","w");
    fclose(fp);
    }
