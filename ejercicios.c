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


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            
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


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

     
//Ejercicio 37 TP2 - Martín Rosolino

#include <stdio.h>
#include <stdlib.h>

//Estructura archivo dado
struct d
    {
    long clave;
    char d[30];
    unsigned char tipo;
    char b;
    }estructura;

//Estructura base de la pila
struct pila
    {
    long clave,posicion;
    struct pila *lazo;
    };

//Prototipo de la funcion
struct pila * funcion (long clave,struct pila *);

//Descripcion de la funcion
struct pila * funcion (long clave,struct pila *p)
        {
        int b=0,op=1;
        long i=0;
        struct pila *aux=NULL;
        FILE *puntero;
        puntero=fopen("datos.dat","rb");
        fread(&estructura,sizeof(struct d),1,puntero);
        while(!feof(puntero))
            {
            i++;
            if(estructura.clave==clave)
                {
                if((estructura.tipo)&(1<<00010000))
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
    struct pila *punter,*aux;
    while(op==1)
        {
        printf("Clave: ");
        scanf("%ld",&id);
        punter=funcion(id,NULL);
        printf("1 para seguir, otro para salir: ");
        scanf("%d",&op);
        }
    puntero=fopen("datos.dat","rb");
    fread(&estructura,sizeof(struct d),1,puntero);
    while(!feof(puntero))
        {
        if(estructura.clave==punter->clave)
            {
            printf("%s\n",estructura.d);
            aux=punter;
            punter=punter->lazo;
            }
        fread(&estructura,sizeof(struct d),1,puntero);
        }
    return 0;
    }


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            
//Ejercicio 39 TP2 - Martín Rosolino
 

#include <stdio.h>
#include <stdlib.h>

struct datos
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    int clave;
    };

struct lista
    {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    struct lista *sig,*ant;
    };

int main()
    {
    FILE *punter;
    int i,op=1;
    unsigned int ascii,pot;
    char potencia;
    struct datos hola;
    struct lista *p,*r,*aux,*u;
    hola.clave=0;

    //Vacio fichero
    punter=fopen("potencia.dat","wb");
    fclose(punter);

    //Inicializo punteros
    p=r=aux=u=NULL;

    while(op!=0)
        {
        //Carga de datos
        printf("Descripcion: ");
        scanf("%[^\n]",&hola.desc);
        fflush(stdin);
        printf("Potencia: ");
        scanf("%c",&hola.potencia);
        fflush(stdin);

        //Obtengo el ascii de la primer letra de la desc
        ascii=hola.desc[0];

        //Asigno el id
        hola.clave++;

        //Obtengo el ascii de la potencia
        pot=hola.potencia;

        //Segun el ascii de la potencia le asigno su valor int
        for(i=0;i<10;i++)
            if(pot==48+i)
                {
                pot=i;
                break;
                }

        //Asigno el valor correspondiente a hola.estado
        hola.estado=ascii*pot;

        //Reservo memoria
        aux=(struct lista *)malloc(sizeof(struct lista));

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
                if(pot>p->potencia)
                    {
                    aux->sig=p;
                    p->ant=aux;
                    p=aux;
                    break;
                    }

                //El dato a ubicar está en otro lugar
                while(r->sig)
                    if(pot<r->potencia)
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
                aux->ant=r;
                r->sig=aux;
                }
            }

        //Agrego al nuevo archivo
        punter=fopen("potencia.dat","ab");
        fwrite(&hola,sizeof(struct datos),1,punter);
        fclose(punter);

        //Salida
        printf("0 para salir, otro para seguir: ");
        scanf("%d",&op);
        fflush(stdin);
        }

    //Asigno p a aux para recorrer desde el principio
    aux=p;

    //Si aux no es el último elemento lo imprime y avanza aux
    while(aux)
        {
        printf("\n--------------------\nDescripcion: %s\nPotencia: %c\nEstado: %d\n--------------------\n",aux->desc,aux->potencia,aux->estado);
        aux=aux->sig;
        }

    //Buenas practicas
    free(aux);

    return 0;
    }


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            
//Ejercicio 40 TP2 - Martín Rosolino
 

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
    int i;
    char primera[60];

    //Pasa letra por letra
    for(i=0;i<strlen(desc);i++)
        {
        //Si es un espacio sale del ciclo
        if (desc[i]==' ')
            break;

        //Mientras no sea un espacio va agregando letras
        strcat(primera,desc[i]);
        }

    //Retorna la palabra invertida
    return strrev(primera);
    }


void funcion (long int clave,struct pila *p)
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

        //Permuta el estado del bit 3 de estado
        bf.estado=bf.estado^(0000000000001000);

        //Mueve el cursor a la posicion adecuada
        fseek(punter,(long)sizeof(struct datos)*(clave-1),0);

        //Reescribe el archivo
        fwrite(&bf,sizeof(struct datos),1,punter);

        //Si los bits 0 y 2 estan prendidos hace las tareas
        if(bf.estado&(1<<0000000000000101))
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
            //Abre archivo salida
            punter=fopen("salida.dat","ab");

            //Escribe el archivo
            fwrite(&bf,sizeof(struct datos),1,punter);
            }
        }
    //Retorna p para poder ubicarse en el proximo ciclo
    return p;
    }


