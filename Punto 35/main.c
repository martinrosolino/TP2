//Ejercicio 35 TP2 - Mart�n Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct pila{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            struct pila *lazo;
            };

typedef struct pila tipopuntero;

void listar (tipopuntero *p_gral);
void vacia ();
tipopuntero * agregar(tipopuntero *p_gral);

int main()
    {
    int op=1;
    tipopuntero *p_gral=NULL;
    vacia();
    while(op!=0)
        {
        printf("----------\n0. Salir\n1. Agregar\n2. Listar\nIngrese: ");
        scanf("%d",&op);
        fflush(stdin);
        switch(op)
            {
            case 0:
                break;
            case 1:
                p_gral=agregar(p_gral);
                break;
            case 2:
                listar(p_gral);
                break;
            }
        }
    return 0;
    }

tipopuntero * agregar (tipopuntero *p_gral)
        {
        tipopuntero *p_local=NULL,*aux=NULL;
        p_local=p_gral;
        char quince[15],cincuenta[50];
        int age=0;
        FILE *fp=NULL;

        //Reservo lugar
        aux=(tipopuntero *) malloc(sizeof(tipopuntero));

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

        //Asigno punteros
        aux->lazo=p_local;
        p_local=aux;

        return (p_local);
        }


void listar (tipopuntero *p_gral)
    {
    tipopuntero *aux=NULL;
    aux=p_gral;
    FILE *fp;
    while(aux)
        {

        //Agrego al archivo
        if((aux->edad)>21)
            {
            printf("\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n",aux->nombre,aux->apellido,aux->telefono,aux->mail,aux->edad);
            fp=fopen("Contactos.dat","ab");
            fwrite(aux,100,1,fp);
            fclose(fp);
            }
        aux=aux->lazo;
        }
    free(aux);
    }

void vacia (void)
    {
    FILE *fp=NULL;
    fp=fopen("Contactos.dat","w");
    fclose(fp);
    }
