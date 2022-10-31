#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define DIM 10000

const char ARCHI_USUARIOS[] = "usuarios.dat";
const char ARCHI_PELIS[] = "peliculas.dat";
const char ARCHI_PELIS_FAVS[] = "favoritos.dat";

/*** ESTRUCTURAS ***/
 typedef struct {
    int  idCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
//    nodo* listaFavoritos;
    int baja;              /// 0 si esta activo - 1 si esta eliminado
 }stCliente;

 typedef struct {
    int idPelicula;
    char nombrePelicula;
    int anio;
    char genero[20];
    char director[20];
    int baja;                      /// 0 si esta activo - 1 si esta eliminado
    int favorita;               /// 0 si no es favorita - 1 si es favorita
}stPelicula;


/*** PROTOTIPADO ***/
/*** FUNCIONES DE MENU ***/
void tituloPrincipal();
void menuPrincipal();
void menuInicio();
void modoUsuario();
void modoAdmin();
void menuSaludoFinal();
char finalizaModificacion();
void estadoDeUsuario(int estadoCliente, char estado[]);
void estadoDelFilm(int estadoFilm, char estado[]);
void altaDeUsuario(char archivo[]);
void altaDePelicula(char archivo[]);
int searchByDNI(char archivo[],char dni[]);
int searchByTittle(char archivo[],char titulo[]);
void cargaUsuario(char cliente[]);
void cargaFilm(char pelicula[]);
int buscaClientesInactivos(char archivo[]);
int buscaClientesActivos(char archivo[]);
void muestraClientesActivos(char archivo[]);
void muestraClienteInactivos(char archivo[]);
void muestraCliente(stCliente c);
void muestraPelicula(stPelicula p);
void muestraArregloClientes(stCliente c[], int v);
stCliente returnByDNI(char archivo[], char dni[]);
stCliente seleccionCampoAmodificar(stCliente c);
void muestraUsuarios(char archivo[]);
void muestraPeliculas(char archivo[]);
void muestraPeliculasFavoritas(char archiFavsUsuario[]);
void menuBuscar();
void stopProgram();
int bajaCliente(char archivo[], char dni[]);
int bajaPelicula(char archivo[], char titulo[]);
int reactivarCliente(char archivo[],char dni[]);
int reactivarPelicula(char archivo[],char titulo[]);
void modificaCliente(char archivo[],stCliente c);
void modificaPeli(char archivo[],stPelicula p);
int buscarPorGenero(char archivo[],char genero[]);
int buscarPorDirector(char archivo[],char director[]);
int buscarPorTitulo(char archivo[],char titulo[]);
stPelicula retornaPorDirector(char archivo[],char director[]);
void muestraClienteDos(stCliente cli);
int archiToArregloPorDirector(char archivo[], stPelicula array[],int dim,char director[]);
int archiToArregloPorGenero(char archivo[], stPelicula array[],int dim,char genero[]);
void menuEditarPeliculas();
void menuEditarUsuarios();
void menuBajas();
int lastID(char archivo[]);
int lastIDPelicula(char archivo[]);

int main(){

    menuPrincipal();
    return 0;

}

///**** FUNCIONES MENU **** ///
/*** Titulo Principal ***/  //titulo que aparece en cada pantalla
void tituloPrincipal(){
    system("cls");
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t************************************************* NETFLIX **************************************************");
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t------------------------------------------------------------------------------------------------------------\n");
}

/*** Menu Principal ***/ //inicio del programa
void menuPrincipal(){
    int opcion = -1;
    char repite = 1;

    do{
        system("cls");
        tituloPrincipal();
        printf("\n\n\n\t\t\t\t   Bienvenido a nuestra plataforma de peliculas \n");
        printf("\n\n\t\t\t\t\t\t Desea ingresar %c",63);
        printf("\n\n\n\t\t\t\t [1].SI \t\t\t\t  [2].NO \n\n");
        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\t [0].SALIR \n");
        printf("\t------------------------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\t\t\t  Ingrese su opci%cn: [ ]\b\b",162);   //se solicita una opcion de acceso a los submenús
        scanf("%d",&opcion);

        switch(opcion){
            case 1:   //en caso de que se elija S, ingresa
                menuInicio();
                break;

            case 2:   // en caso de que se elija N, sale.
                menuSaludoFinal();
				printf("\n\n\n\n\n\t\t\t\t");
				system("pause");
                break;

            case 0:     // si elije salir muestra el saludo final y sale
				repite = 0;
				menuSaludoFinal();
				printf("\n\n\n\n\n\t\t\t\t");
				system("pause");
				break;
            }
	}while(repite);
}

/*** Menu Inicial ***/  //primer menu al ingresar al sistema
void menuInicio(){
	char repite = 1;
	int opcion = -1;

	/* Cuando el usuario ingresa texto en lugar de  una opción, el programa no modifica el valor de opcion.
	 En ese caso, se está inicializando la variable opcion con un valor que no permita ejecutar ningún case.
	 Vuelve a interar y pide nuevamente la opción. */

	do {
		system("cls");
		tituloPrincipal();  //muestra el nombre de la plataforma
		printf("\n\t\t\t\t\t\t    MENU PRINCIPAL  \n\n");
		printf("\n\n\t\t\t [1].MODO USUARIO \t\t\t\t  [2].MODO ADMINISTRADOR \n\n\n\n\n");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);   //se solicita una opcion de acceso a los submenús
		scanf( "%d",&opcion);

		switch(opcion){

			case 1:
			    tituloPrincipal();
				modoUsuario();
				break;

			case 2:
			    tituloPrincipal();
				modoAdmin();
				break;

			case 0:
				repite = 0; //en caso de querer salir, se elije el case 0 que cambia el valor de repite para cortar el ciclo
				break;
		}
	}while(repite);
}

/*** Modo Usuario // Menu de  Clientes ***/     // menu donde se podran ejecutar funciones relacionadas a los clientes
void modoUsuario(){
    char repite = 1;
    int opcion = -1;
    int bajaC = -1;
    int existe = -1;
    stCliente cliente;
    int reactivar = -1;
    char dni;

	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t\t MODO USUARIO \n\n");
        printf("\t\t\t\t\t[1]. Ver mi perfil. \n");
		printf("\t\t\t\t\t[2]. Modificar mi perfil. \n");
		printf("\t\t\t\t\t[3]. Ver listado de peliculas. \n");
		printf("\t\t\t\t\t[4]. Ver mis favoritos. \n");
		printf("\t\t\t\t\t[5]. Buscar pelicula. \n");

        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR ");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");

		printf("\n\t\t Ingrese su opci%cn: [ ]\b\b",162);   //solicita la opcion de ingreso a los submenús
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
			    tituloPrincipal();
			    printf("\n\t\t\t Ingrese su DNI para acceder a su perfil ");  //se solicita dni del cliente
                scanf("%s",dni);
                existe=searchByDNI(ARCHI_USUARIOS,dni);        //se corrobora la existencia del mismo
                if(existe == 1){
                    printf("\n\t\t\t\t MI PERFIL. \n");         //en caso de existencia se muestran sus datos para que el usuario vea si corresponden al cliente o hay algun error en la busqueda
                    cliente=returnByDNI(ARCHI_USUARIOS,dni);    //se devuelve la estructura de cliente
                    muestraCliente(cliente);                    //se muestran sus datos
                }
				break;

			case 2:
			    tituloPrincipal();
			    printf("\n\t\t\t\t Ingrese su DNI para acceder a la modificacion de datos");    //se solicita el DNI del cliente
                scanf("%s",dni);
			    cliente=returnByDNI(ARCHI_USUARIOS,dni);    //guardo el cliente encontrado con ese DNI en una estructura cliente
                cliente=seleccionCampoAmodificar(cliente); //la paso por parametro y guardo el resultado modificado en esa misma estructura
				modificaCliente(ARCHI_USUARIOS,cliente);    //la recibo nuevamente por parametro para modificarla en el archivo
				stopProgram();
                break;

			case 3:
			    tituloPrincipal();
			    printf("\n\t\t\t\t LISTADO DE PELICULAS ");
			    muestraPeliculas(ARCHI_PELIS);
				break;

            case 4:
                tituloPrincipal();
                printf("\n\t\t\t\t LISTADO DE PELICULAS A%cADIDAS A FAVORITAS",165);
			    muestraPeliculasFavoritas(ARCHI_PELIS_FAVS);
                break;

            case 5:
                tituloPrincipal();
                menuBuscar();
				break;

			case 0:
				repite = 0;
				break;
		}
	}while(repite);
}

/*** Modo Administrador ***/     // menu donde se podran modificar peliculas, usuarios y dar bajas
void modoAdmin(){
    char repite = 1;
    int opcion = -1;
    char dni[10];
    int bajaC = -1;
    int existe = -1;
    stCliente cliente;
    int reactivar = -1;

	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t\t MODO ADMINISTRADOR \n\n");
        printf("\t\t\t\t\t[1]. Ver mi perfil. \n");
		printf("\t\t\t\t\t[2]. Modificar mi perfil. \n");
		printf("\t\t\t\t\t[3]. Editar peliculas. \n");
		printf("\t\t\t\t\t[4]. Editar usuarios. \n");
		printf("\t\t\t\t\t[5]. Bajas \n"); /// ---> a submenu de baja de usuarios o peliculas

        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR ");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");

		printf("\n\t\t Ingrese su opci%cn: [ ]\b\b",162);   //solicita la opcion de ingreso a los submenús
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
			    tituloPrincipal();
			    printf("\n\t\t\t Ingrese su DNI para acceder a su perfil ");  //se solicita dni del cliente
                scanf("%s",dni);
                existe=searchByDNI(ARCHI_USUARIOS,dni);        //se corrobora la existencia del mismo
                if(existe == 1){
                    printf("\n\t\t\t\t MI PERFIL. \n");         //en caso de existencia se muestran sus datos para que el usuario vea si corresponden al cliente o hay algun error en la busqueda
                    cliente=returnByDNI(ARCHI_USUARIOS,dni);    //se devuelve la estructura de cliente
                    muestraCliente(cliente);                    //se muestran sus datos
                }
				break;

			case 2:
			    tituloPrincipal();
			    printf("\n\t\t\t\t Ingrese su DNI para acceder a la modificacion de datos");    //se solicita el DNI del cliente
                scanf("%s",dni);
			    cliente=returnByDNI(ARCHI_USUARIOS,dni);    //guardo el cliente encontrado con ese DNI en una estructura cliente
                cliente=seleccionCampoAmodificar(cliente); //la paso por parametro y guardo el resultado modificado en esa misma estructura
				modificaCliente(ARCHI_USUARIOS,cliente);    //la recibo nuevamente por parametro para modificarla en el archivo
				stopProgram();
                break;

			case 3:
			    tituloPrincipal();
			    menuEditarPeliculas();
				break;

            case 4:
                tituloPrincipal();
                menuEditarUsuarios();
                break;

            case 5:
                tituloPrincipal();
                menuBajas();
                break;

			case 0:
				repite = 0;
				break;
		}
	}while(repite);
}

/*** Saludo Final ***/ //saludo de cierre del programa
void menuSaludoFinal(){

    system("cls");
    tituloPrincipal();
    printf("\n\n\n\n\t\t\t\t\t   Gracias por utilizar nuestro servicio.");
    printf("\n\n\n\n\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t   created by XXXX",169);
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");

}

/*** Menu de finalizacion de modificaciones *** Aparece cada vez que se realiza un cambio para salir o continuar */
char finalizaModificacion(){
    int repite = 1;
    char opcion=-1;
    char ESC;

    system("cls");
    tituloPrincipal();
    printf("\n\n\t\t\t\t Los datos se actualizaron correctamente");

    do{
        printf("\n\n\n\t\t\t\t Desea realizar otro cambio o modificaci%cn? [S/N]",162);
        printf("\n\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        fflush(stdin);
        scanf("%c",&opcion);
        switch(opcion){
            case 'S':
                ESC=27;
                break;

            case 'N':
                repite=0;
                ESC=27;
                break;
        }
    }while(ESC !=27);

    return repite;
}

/// Muestra el estado del cliente si esta activo de baja.
/// Esta funcion pasa a string el estado de baja 0 o 1
void estadoDeUsuario(int estadoCliente, char estado[]){

    switch(estadoCliente){
        case 0: strcpy(estado, "Activo");
            break;
        case 1: strcpy(estado, "Inactivo");
            break;
    }
}

/// Muestra el estado de la pelicula si esta activa o de baja.
void estadoDelFilm(int estadoFilm, char estado[]){

    switch(estadoFilm){
        case 0: strcpy(estado, "Disponible");
            break;
        case 1: strcpy(estado, "No disponible");
            break;
    }
}

/*** Alta de usuario con validacion - Controla que el cliente no este ya cargado por su dni***/
void altaDeUsuario(char archivo[]){
    stCliente c;
    char ESC;
    char dni[20];
    int busquedaDni;

        system("cls");
        tituloPrincipal();
        while(ESC != 27){
            printf("\n\n\t\t\t\t\t Ingrese el DNI del nuevo usuario. \n\t\t\t\t Se verificar%c que no exista en la base de datos. \n",160);  ///pido el dni
            printf("\n\t\t\t\t\t DNI...................:");
            fflush(stdin);
            scanf("%s",dni);                                            //guardo en dni el valor del dni ingresado

            busquedaDni=searchByDNI(archivo,dni);                   // realizo validacion del dni y retorno su valor para saber si existe o no
            if(busquedaDni == 1){
                printf("\n\t\t\t-------------------------------------------------------------------------\n");
                printf("\n\t\t\t El DNI que intenta cargar ya se encuentra asociado a otro cliente. \n");
            }
            else{
                system("cls");
                tituloPrincipal();
                printf("\n\t\t\t\t\tEl dni ingresado NO fue encontrado.");
                printf("\n\t\t\t\t\t Puede continuar con la carga de datos.\n");
                cargaUsuario(archivo);
            }
            printf("\n\t\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
    }
}

/*** Alta de peliculas con validacion - Controla que el film no este ya cargado por su nombre***/
void altaDePelicula(char archivo[]){
    stPelicula p;
    char ESC;
    char titulo[20];
    int busquedaTitulo;

        system("cls");
        tituloPrincipal();
        while(ESC != 27){
            printf("\n\n\t\t\t\t\t Ingrese el Título de la nueva pelicula. \n\t\t\t\t Se verificar%c que no exista en la base de datos. \n",160);  ///pido el dni
            printf("\n\t\t\t\t\t TITULO...................:");
            fflush(stdin);
            scanf("%s",titulo);                                            //guardo en dni el valor del dni ingresado

            busquedaTitulo=searchByTittle(archivo,titulo);                   // realizo validacion del dni y retorno su valor para saber si existe o no
            if(busquedaTitulo == 1){
                printf("\n\t\t\t-------------------------------------------------------------------------\n");
                printf("\n\t\t\t El film que intenta cargar ya se encuentra asociado a nuestra base de datos. \n");
            }
            else{
                system("cls");
                tituloPrincipal();
                printf("\n\t\t\t\t\tEl titulo ingresado NO fue encontrado.");
                printf("\n\t\t\t\t\t Puede continuar con la carga de datos.\n");
                cargaFilm(archivo);
            }
            printf("\n\t\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
    }
}

/*** Busqueda por DNI *** // *** VALIDACION ***/
int searchByDNI(char archivo[],char dni[]){

    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");      //abro el archivo para leer sus datos
    if(pf){
        while(flag == 0 && fread(&c,sizeof(stCliente),1,pf) > 0){   // leer el archivo de a un usuario
             if(strcmp(c.dni,dni)==0){                          // comparo el dni ingresado con el dato dni de ese usuario
                flag=1;
             }
        }
        fclose(pf);
    }
    return flag;
}

/*** Busqueda por DNI *** // *** VALIDACION ***/
int searchByTittle(char archivo[],char titulo[]){

    stPelicula p;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");      //abro el archivo para leer sus datos
    if(pf){
        while(flag == 0 && fread(&p,sizeof(stPelicula),1,pf) > 0){   // leer el archivo de a un film
             if(strcmp(p.nombrePelicula,titulo)==0){                          // comparo el titulo ingresado con el dato titulo de ese film
                flag=1;
             }
        }
        fclose(pf);
    }
    return flag;
}

/*** Carga de datos de usuario ***/
void cargaUsuario(char cliente[]){
    stCliente c;
    char ESC = 0;
    int id=lastID(ARCHI_USUARIOS) + 1;
    char estado[15];

    FILE *pf= fopen(cliente,"ab");        //abro archivo en modo append
    if(pf){

        do{ printf("\n\t\t------------------------------------------------------------------------------\n");
            printf("\n\n\t\t\t\t   DATOS DEL NUEVO USUARIO \n\n");      //cargo el nuevo cliente

            c.idCliente=id;
            printf("\t\t\t   ID USUARIO................:%d \n",c.idCliente);

            printf("\t\t\t   NOMBRE................:");
            fflush(stdin);
            scanf("%[^\n]",c.nombre);   //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   APELLIDO..............:");
            fflush(stdin);
            scanf("%[^\n]",c.apellido); //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   DNI...................:");
            fflush(stdin);
            scanf("%s",c.dni);

            c.baja=0;   //colocamos 0 automaticamente, lo que significa que no esta de baja, por ende se esta activando en el alta
            estadoDeUsuario(c.baja, estado);
            printf("\t\t\t   ESTADO DE CLIENTE................:%s",estado);

            fwrite(&c, sizeof(stCliente), 1 ,pf);      //escribo los datos en el archivo
            id++;

            printf("\n\n\n\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
        }
        while(ESC != 27);

        fclose(pf);            //cierro el archivo
        tituloPrincipal();
        printf("\n\t\t\t        El nuevo cliente se ha cargado exitosamente \n\n\n");
        printf("\n\t\t------------------------------------------------------------------------------\n");
    }
}

/*** Carga de datos de usuario ***/
void cargaFilm(char pelicula[]){
    stPelicula p;
    char ESC = 0;
    int id=lastID(pelicula) + 1;
    char estado[15];

    FILE *pf= fopen(pelicula,"ab");        //abro archivo en modo append
    if(pf){

        do{ printf("\n\t\t------------------------------------------------------------------------------\n");
            printf("\n\n\t\t\t\t   DATOS DE LA NUEVA PELICULA \n\n");      //cargo el nuevo cliente

            p.idPelicula = id;
            printf("\t\t\t   ID PELICULA................:%d \n",p.idPelicula);

            printf("\t\t\t   TITULO................:");
            fflush(stdin);
            scanf("%[^\n]",p.nombrePelicula);   //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   DIRECTOR..............:");
            fflush(stdin);
            scanf("%[^\n]", p.director); //captura todos los datos ingresados hasta el enter, incluso espacios en blanco

            printf("\t\t\t   A%cO...................:",165);
            fflush(stdin);
            scanf("%s",p.anio);

            p.baja=0;   //colocamos 0 automaticamente, lo que significa que no esta de baja, por ende se esta activando en el alta
            estadoDelFilm(p.baja, estado);
            printf("\t\t\t   ESTADO DE LA PELICULA................:%s",estado);

            fwrite(&p, sizeof(stCliente), 1 ,pf);      //escribo los datos en el archivo
            id++;

            printf("\n\n\n\t\t     Presione ESC para salir o cualquier tecla para continuar\n");
            ESC = getch();
            system("cls");
        }
        while(ESC != 27);

        fclose(pf);            //cierro el archivo
        tituloPrincipal();
        printf("\n\t\t\t        La nueva pelicula se ha cargado exitosamente \n\n\n");
        printf("\n\t\t------------------------------------------------------------------------------\n");
    }
}

/*** Retorna ultimo ID de usuarios ***/
int lastID(char archivo[]){
    stCliente cli;
    int id=0;

    FILE *pf = fopen(archivo, "rb");          // abro en modo lectura
    if(pf){
        fseek(pf, sizeof(stCliente) * -1, SEEK_END);  //me posiciono -1 registro al final del archivo
        if(fread(&cli, sizeof(stCliente),1,pf) > 0){      //leo el dato de ese registro
                id=cli.idCliente;                                      //asigno el ultimo id
        }
      fclose(pf);         //cierro el archivo
    }
    return id;  //retorno el ultimo id encontrado en el archivo
}
/*** Retorna ultimo ID de usuarios ***/
int lastIDPelicula(char archivo[]){
    stPelicula p;
    int id=0;

    FILE *pf = fopen(archivo, "rb");          // abro en modo lectura
    if(pf){
        fseek(pf, sizeof(stPelicula) * -1, SEEK_END);  //me posiciono -1 registro al final del archivo
        if(fread(&p, sizeof(stPelicula),1,pf) > 0){      //leo el dato de ese registro
                id=p.idPelicula;                                      //asigno el ultimo id
        }
      fclose(pf);         //cierro el archivo
    }
    return id;  //retorno el ultimo id encontrado en el archivo
}


/*** Busca si hay clientes INACTIVOS ***/
int buscaClientesInactivos(char archivo[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura
    if(pf){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==1){
                flag=1;     //salgo si encuentro el dato con flag en 1
            }
        }
        fclose(pf); //cierro el archivo
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
    return flag;    //retorno si hay al menos un dato de cliente inactivo
}

/*** Busca si hay clientes ACTIVOS ***/
int buscaClientesActivos(char archivo[]){
    stCliente c;
    int flag=0;

    FILE *pf = fopen(archivo,"rb"); //abro archivo en modo lectura
    if(pf){
        while(flag ==0 && fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==0){  //si encuentor algun campo en 0, al menos 1
                flag=1;     //salgo del recorrido con flag en 1
            }
        }
        fclose(pf);
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
    return flag;    //retorno que existen datos de clientes activos
}

///****FUNCIONES DE MUESTRA ***/
/*** Muestra clientes Activos ***/
void muestraClientesActivos(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb"); //leo el archivo

    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==0){
            muestraCliente(c);  //muestro cada cliente que encuentre activo
            }
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Muestra clientes Inactivos ***/
void muestraClienteInactivos(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb");     //leo el archivo
    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0){
            if(c.baja==1){          //por cada cliente inactivo lo muestro
            muestraCliente(c);
            }
        }
        fclose(pf);
     }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Mostrar un cliente ***/
void muestraCliente(stCliente c){

    char estado[15];
    estadoDeUsuario(c.baja, estado);

    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ID CLIENTE: %-d \t\t\t\t", c.idCliente);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t Nombre y apellido: %-s %-s",c.nombre, c.apellido);
    printf("\n\t\t\t\t DNI: %s", c.dni);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ESTADO DE CLIENTE: %s",estado);  //muestro el estado en forma de texto pero conserva internamente su valor numerico 0 o 1 segun el estado
    printf("\n\t\t----------------------------------------------------------------------------------------\n\n\n");

}

/*** Mostrar una pelicula ***/
void muestraPelicula(stPelicula p){
    char estado[15];
    estadoDelFilm(p.baja, estado);

    printf("\n\t ID PELICULA   |   TITULO   |   A%cO   |   DIRECTOR   |   ESTADO   |   FAVORITA   \n",165);
    printf("\n\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t %6d %15d %14d %8d %10d %16d %20s %14d \n", p.idPelicula, p.nombrePelicula, p.anio, p.director, estado, p.favorita );
    printf("\t------------------------------------------------------------------------------------------------------------\n");

}

/*** Retorna cliente por DNI***/
stCliente returnByDNI(char archivo[], char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&c,sizeof(stCliente),1,pf)> 0){
            if(strcmp(c.dni,dni)==0){
               flag = 1;
            }
        }
        fclose(pf);
    }
    return c;
}

/*** Seleccion de campos a modificar y retorno de estructura modificada ***/
stCliente seleccionCampoAmodificar(stCliente c){
    int repite = 1;
    int opcion=0;
    char ESC;

    printf("\t\t------------------------------------------------------------------------------\n");
    printf("\n\n\t\t\t\t\t Datos Actuales del cliente: \n");
    muestraCliente(c);

	do {
        printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\n\t\t\t\t\t Seleccione el campo a modificar \n\n");
		printf("\t\t\t\t[1]. Nombre\n");
		printf("\t\t\t\t[2]. Apellido\n");
		printf("\t\t\t\t[3]. DNI\n");
        printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t [0].SALIR ");
		printf("\n\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

		switch(opcion){

			case 1:
                printf("\n\n\t\t\t\t Ingrese el nuevo nombre de Cliente: ");//solicita el dato a cambiar
                fflush(stdin);
			    scanf("%[^\n]", c.nombre);                  //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();          //pregunta si va a hacer mas cambio o no
                break;

			case 2:
		        printf("\n\n\t\t\t\t Ingrese el nuevo apellido de Cliente: ");   //solicita el dato a cambiar
		        fflush(stdin);
			    scanf("%[^\n]", c.apellido);            //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();      //pregunta si va a hacer mas cambio o no
                break;

			case 3:
                printf("\n\n\t\t\t\t Ingrese el nuevo DNI de Cliente: ");    //solicita el dato a cambiar
                fflush(stdin);
			    scanf("%s", c.dni);                 //guarda el nuevo dato en la estructura del cliente
			    repite=finalizaModificacion();         //pregunta si va a hacer mas cambio o no
                break;

			case 0:
                repite = 0;
                modoUsuario();
				break;
		}
	}while(repite);

    return c;   //retorna la estructura con los datos modificados para que luego sea reemplaza en el archivo por otra funcion
}

/***Muestra todos los clientes***/
void muestraUsuarios(char archivo[]){
    stCliente c;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&c, sizeof(stCliente), 1 ,pf)> 0 ){ //recorro todo el archivo y por cada vez que leo muestro un cliente
            muestraCliente(c);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/***Muestra todos los clientes***/
void muestraPeliculas(char archivo[]){
    stPelicula p;

    FILE *pf = fopen(archivo,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&p, sizeof(stPelicula), 1 ,pf)> 0 ){ //recorro todo el archivo y por cada vez que leo muestro un cliente
            muestraPelicula(p);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/***Muestra todos los clientes***/
void muestraPeliculasFavoritas(char archiFavsUsuario[]){
    stPelicula p;

    FILE *pf = fopen(archiFavsUsuario,"rb"); //abro en modo lectura

    if(pf){
        while(fread(&p, sizeof(stPelicula), 1 ,pf)> 0 ){ //recorro todo el archivo y por cada vez que leo muestro un cliente
            muestraPeliculasFavoritas(ARCHI_PELIS_FAVS);
        }
        fclose(pf);
    } else{
        printf("\n ERROR DE APERTURA DE ARCHIVO \n");
    }
}

/*** Menu Búsqueda de Peliculas ***/
void menuBuscar(){
    int existe;
    int validos = 0;
    int validos2 = 0;
    char repite = 1;
	char titulo[30];
	char genero[30];
	char director[30];
	char arrayPorGenero[DIM];
	char arrayPorDirector[DIM];
	char opcion=-1;
	stCliente peli;
	stPelicula peliEncontrada;


	do {
		system("cls");
        tituloPrincipal();
        printf("\n\t\t\t\t\t  BUSQUEDA DE PELICULAS \n\n");
		printf("\t\t\t\t\t[1]. Buscar por Titulo \n");
		printf("\t\t\t\t\t[2]. Buscar por Genero \n");
		printf("\t\t\t\t\t[3]. Buscar por Director \n");
        printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t [0].SALIR \n");
		printf("\t------------------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t Ingrese su opci%cn: [ ]\b\b",162);
        scanf("%d",&opcion);

        switch(opcion){
            case 1:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el Titulo de la pelicula: ");  //se solicita el DNI para realizar la busqueda en el archivo
            fflush(stdin);
            scanf("%s",titulo);
            ///existe=searchByLastname(AR_CLI, apellido);
            existe=buscarPorTitulo(ARCHI_PELIS, titulo);
            if(existe == 1){
                printf("\n\t\t\t\t Los datos encontrados para el Título %s fueron: \n",titulo);  //en caso de existencia se muestran sus datos
              //  peliEncontrada = buscarPorTitulo(ARCHI_PELIS, titulo);
              //  muestraPelicula(peliEncontrada);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron coincidencias para el Titulo %s \n\n\n\n",titulo);
                }
            stopProgram();
            break;

            case 2:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el Genero que desea buscar: ");  //se solicita el DNI para realizar la busqueda en el archivo
            fflush(stdin);
            scanf("%s",genero);
            existe=buscarPorGenero(ARCHI_PELIS, genero);
            if(existe == 1){
                ///paso los apellidos a un arreglo por si hay mas de un cliente con el mismo apellido
                validos=archiToArregloPorGenero(ARCHI_PELIS,arrayPorGenero,DIM,genero);
                printf("\n\t\t\t\t Los datos encontrados para el genero %s fueron: \n",genero);  //en caso de existencia se muestran sus datos
                muestraArregloClientes(arrayPorGenero,validos);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron datos asociados al genero: %s \n\n\n\n",genero);
                }
            stopProgram();
            break;

            case 3:
            system("cls");
            tituloPrincipal();
            printf("\n\t\t\t\t  Ingrese el Director que desea buscar: ");  //se solicita el DNI para realizar la busqueda en el archivo
            fflush(stdin);
            scanf("%s",director);
            existe=buscarPorGenero(ARCHI_PELIS, director);
            if(existe == 1){
                ///paso los apellidos a un arreglo por si hay mas de un cliente con el mismo director
                validos2=archiToArregloPorDirector(ARCHI_PELIS,arrayPorDirector,DIM,director);
                printf("\n\t\t\t\t Los datos encontrados para el Director %s fueron: \n",genero);  //en caso de existencia se muestran sus datos
                muestraArregloClientes(arrayPorDirector,validos2);
                }else{
                printf("\n\n\n\t\t\t\t No se encontraron datos asociados al genero: %s \n\n\n\n",genero);
                }
            stopProgram();
            break;

        case 0:
            repite = 0; //en caso de que la opcion ingresada sea SALIR, repite toma valor 0 para finalizar la iteracion del ciclo.
            break;
        }
    }while (repite);
}

/*** Muestra arreglo de usuarios  ***/
void muestraArregloClientes(stCliente c[], int v){
    for(int i=0;i<v;i++){
        muestraCliente(c[i]);
    }
}

/*** Ejecuta una pausa con mensaje para continuar ***/
void stopProgram(){
    printf("\n\t\t\t\t\t");
    system("pause");    //pausa el sistema y muestra el mensaje centrado con el diseño del programa
}

/*** Baja de cliente (sin eliminar sus datos) ***/
int bajaCliente(char archivo[], char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&c, sizeof(stCliente), 1, pf) > 0){
            if(strcmp(c.dni,dni)==0){
                c.baja=1;   //coloco el estado en baja
                flag = 1;
                fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&c,sizeof(stCliente),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;        //retorna si se puso hacer la baja correctamente.
}

/*** Baja de pelicula (sin eliminar sus datos) ***/
int bajaPelicula(char archivo[], char titulo[]){
    int flag=0;
    stPelicula p;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&p, sizeof(stCliente), 1, pf) > 0){
            if(strcmp(p.nombrePelicula,titulo)==0){
                p.baja=1;   //coloco el estado en baja
                flag = 1;
                fseek(pf, -1 * sizeof(stPelicula), SEEK_CUR);
                fwrite(&p,sizeof(stPelicula),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;        //retorna si se puso hacer la baja correctamente.
}

/*** Reactivar de Cliente ***/
int reactivarCliente(char archivo[],char dni[]){
    int flag=0;
    stCliente c;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&c, sizeof(stCliente), 1, pf) > 0){
            if(strcmp(c.dni,dni)==0){
                c.baja=0;   //posiciona en 0 al cliente, en alta.
                flag = 1;
                fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&c,sizeof(stCliente),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;    //retorna si se pudo hacer la reactivacion.
}

/*** Reactivar Pelicula ***/
int reactivarPelicula(char archivo[],char titulo[]){
    int flag=0;
    stPelicula p;

    FILE *pf = fopen(archivo, "r+b");

    if(pf){
        while(flag==0 && fread(&p, sizeof(stPelicula), 1, pf) > 0){
            if(strcmp(p.nombrePelicula,titulo)==0){
                p.baja=0;   //posiciona en 0 al cliente, en alta.
                flag = 1;
                fseek(pf, -1 * sizeof(stPelicula), SEEK_CUR);
                fwrite(&p,sizeof(stPelicula),1, pf);
                }
            }
        fclose(pf);
    }
    return flag;    //retorna si se pudo hacer la reactivacion.
}

/*** Modificacion de datos del cliente en archivo ***/
void modificaCliente(char archivo[],stCliente c){
    stCliente a;
    FILE *pf = fopen(archivo, "r+b");   //abro el archivo en modo lectura y escritura
    int flag=0;

    if(pf){
        while(flag == 0 && fread(&a, sizeof(stCliente), 1, pf)>0){ // recorro el archivo
            if(a.idCliente==c.idCliente){                             // encuentro el id donde esta el dato a modificar
                a=c;        //coloco los datos de la nueva estructura recibida en la posicion deseada
                flag=1;
            }
            fseek(pf, -1 * sizeof(stCliente), SEEK_CUR);    //me posiciono una estructura para atras desde donde quedo el cursor de lectura
            fwrite(&a, sizeof(stCliente), 1, pf);            // escribo la nueva estructura
        }
        fclose(pf);
    }
}

/*** Modificacion de datos del cliente en archivo ***/
void modificaPeli(char archivo[],stPelicula p){
    stPelicula a;
    FILE *pf = fopen(archivo, "r+b");   //abro el archivo en modo lectura y escritura
    int flag=0;

    if(pf){
        while(flag == 0 && fread(&a, sizeof(stPelicula), 1, pf)>0){ // recorro el archivo
            if(a.idPelicula==p.idPelicula){                             // encuentro el id donde esta el dato a modificar
                a=p;        //coloco los datos de la nueva estructura recibida en la posicion deseada
                flag=1;
            }
            fseek(pf, -1 * sizeof(stPelicula), SEEK_CUR);    //me posiciono una estructura para atras desde donde quedo el cursor de lectura
            fwrite(&a, sizeof(stPelicula), 1, pf);            // escribo la nueva estructura
        }
        fclose(pf);
    }
}

/*** Busqueda de pelicula por genero ***/
int buscarPorGenero(char archivo[],char genero[]){
    stPelicula p;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&p,sizeof(stPelicula),1,pf)> 0){
            if(strcmp(p.genero,genero)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Busqueda de pelicula por Director ***/
int buscarPorDirector(char archivo[],char director[]){
    stPelicula p;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&p,sizeof(stPelicula),1,pf)> 0){
            if(strcmp(p.director,director)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Busqueda de pelicula por Titulo ***/
int buscarPorTitulo(char archivo[],char titulo[]){
    stPelicula p;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&p,sizeof(stPelicula),1,pf)> 0){
            if(strcmp(p.nombrePelicula,titulo)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return flag;
}

/*** Retorna estructura por director ***/
stPelicula retornaPorDirector(char archivo[],char director[]){
    stPelicula p;
    int flag=0;

    FILE *pf = fopen(archivo,"rb");         //solo lectura
    if(pf){
        while(flag==0 && fread(&p,sizeof(stPelicula),1,pf)> 0){
            if(strcmp(p.director,director)==0){
                flag=1;
            }
        }
        fclose(pf);
    }
    return p;
}

/*** Mostrar un cliente ***/
void muestraClienteDos(stCliente cli){
    stCliente c = cli;
    char estado[15];
    estadoDeUsuario(c.baja, estado);

    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ID USUARIO: %-d", c.idCliente);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
   // printf("\n\t\t\t DATOS PERSONALES:");
    printf("\n\t\t\t\t Nombre y apellido: %-s %-s",c.nombre, c.apellido);
    //printf("\n\t\t\t Apellido: %-s", c.apellido);
    printf("\n\t\t\t\t DNI: %s", c.dni);
    printf("\n\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t ESTADO DE CLIENTE: %s",estado);  //muestro el estado en forma de texto pero conserva internamente su valor numerico 0 o 1 segun el estado
    printf("\n\t\t----------------------------------------------------------------------------------------\n\n\n");

}

/*** Pasa peliculas a un arreglo por director***/
int archiToArregloPorDirector(char archivo[], stPelicula array[],int dim,char director[]){
    stPelicula p;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&p,sizeof(stPelicula),1,pf)>0 && i<dim){
            if(strcmp(p.director,director)==0){
                array[i]=p; //paso al arreglo cada estructura del archivo
                i++;
            }
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

/*** Pasa peliculas a un arreglo por genero***/
int archiToArregloPorGenero(char archivo[], stPelicula array[],int dim,char genero[]){
    stPelicula p;
    int i=0;

    FILE *pf = fopen(archivo, "rb");    //abro en modo lectura
    if(pf){
        while(fread(&p,sizeof(stPelicula),1,pf)>0 && i<dim){
            if(strcmp(p.genero,genero)==0){
                array[i]=p; //paso al arreglo cada estructura del archivo
                i++;
            }
        }
        fclose(pf);
        }
    return i;   //retorno la cantidad de datos que se cargaron para saber los validos
}

void menuEditarPeliculas(){
}

void menuEditarUsuarios(){
}

void menuBajas(){
}
