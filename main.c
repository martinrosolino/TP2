//Ejercicio 35 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pila{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            struct pila *lazo;
            };

int main()
{
    int op=1,a;
    FILE *fp;
    struct pila *p,*r,*aux;
    struct contactos{
            char nombre[15],apellido[15],telefono[15],mail[50];
            int edad;
            }bf;

    //Vacio fichero
    fp=fopen("Contactos.dat","w");
    fclose(fp);

    //Pongo la pila en cero
    p=r=aux=NULL;

    while(op!=0)
        {
        //Obtengo los datos
        printf("----------\nNombre: ");
        scanf("%s",&bf.nombre);
        printf("Apellido: ");
        scanf("%s",&bf.apellido);
        printf("Telefono: ");
        scanf("%s",&bf.telefono);
        printf("Mail: ");
        scanf("%s",&bf.mail);
        printf("Edad: ");
        scanf("%d",&bf.edad);

        //Reservo lugar
        aux=(struct pila *) malloc(sizeof(struct pila));

        //Cargo datos
        strcpy(aux->nombre,bf.nombre);
        strcpy(aux->apellido,bf.apellido);
        strcpy(aux->telefono,bf.telefono);
        strcpy(aux->mail,bf.mail);
        aux->edad=bf.edad;

        //Asigno punteros
        aux->lazo=p;
        p=aux;

        //Agrego al archivo
        if(bf.edad>21)
            {
            fp=fopen("Contactos.dat","ab");
            fwrite(&bf,sizeof(struct contactos),1,fp);
            fclose(fp);
            }

        //Salida y listado
        printf("----------\nPulse 0 para salir, 1 para listar, otro para continuar: ");
        scanf("%d",&op);
        fp=fopen("Contactos.dat","rb");
        if(op==1)
            while(!feof(fp))
                {
                fread(&bf,sizeof(struct contactos),1,fp);
                fprintf(stdout,"----------\nNombre: %s\nApellido: %s\nTelefono: %s\nMail: %s\nEdad: %d\n",bf.nombre,bf.apellido,bf.telefono,bf.mail,bf.edad);
                fread(&bf,sizeof(struct contactos),1,fp);
                }
        fclose(fp);
        }
    return 0;
}
