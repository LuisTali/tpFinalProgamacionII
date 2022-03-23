#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct
{
    char apellidoYnombre[50];
    char mail[50];
    int celular;
    char contrasenia[8];
} admin;

typedef struct
{
    int id;
    char apellidoYnombre[50];
    char mail[50];
    int celular;
    char contrasenia[8];
    int estado;
} usuario;

typedef struct
{
    int id;
    char nombre[50];
    int anio;
    char genero[50];
    char cantantes[3][50];
    int cantCantantes;
    int estado;
} cancion;

typedef struct nodoArbol
{
    struct nodoArbol* izq;
    struct nodoArbol* der;
    cancion dato;
} nodoArbol;

typedef struct nodoListaCanc
{
    cancion dato;
    struct nodoListaCanc* sig;
} nodoListaCanc;

typedef struct nodoListaUsers
{
    usuario dato;
    nodoListaCanc * playlist;
    struct nodoListaUsers * sig;
} nodoListaUsers;

typedef struct
{
    int idRegistroPlaylist;
    int idUsuario;
    int idCancion;
} stRegistroPlaylist;

//MENU
int menu(); //Ingresar como admin, como usuario o registrarse
int menuAdmin(); //Opciones para admin
int menuUsuario(); //Opciones para usuario
int subMenuUsuario(); //Opciones para manejo de datos de usuario
int subMenuUsuarioCanciones(); //Opciones para manejo de canciones desde la vista del usuario
int subMenuMostrarCancionesAgregarPlaylist(); //Opciones para agregar canciones a la playlist desde la vista del usuario
int subMenuMostrarCanciones(); //Opciones para mostrar canciones desde la vista del usuario
int menuModificarUser(); //Opciones para modificar los datos de un usuario
int menuAdminUsuarios(); //Opciones para manipular los datos de los usuarios desde la vista del admin
int menuAdminCanciones(); //Opciones para manipular los datos de las canciones desde la vista del admin
int menuModificarCancion(); //Opciones para modificar los datos de una cancion
int menuMostrarListaC(); //Opciones para mostrar las canciones de una lista

//ADMIN
admin cargarAdmin(); //Carga y retorna una variable auxiliar de tipo admin
void mostrarArch(); //Muestra el archivo con el admin cargado
void crearArchAdmin(); //Crea el archivo para guardar los datos del administrador
int validarAdmin(); //Valida los datos del admin para permitir ingresar a las funciones de administrador
void modificarUser(int id); //Permite modificar al usuario
int menuModificarCantantes(cancion aux); //Permite elegir que cantante de la cancion se desea modificar

///CANCIONES
void mostrarCancion(cancion aux); //Se envia una variable de tipo cancion por parametro y luego es mostrada
nodoArbol* inicArbol(); //Inicializa el arbol
int cantArchivosFseek(); //Retorna la cantidad de registros en el archivo de canciones
cancion cargarCancion(); //Carga y retorna una variable auxiliar de tipo cancion
void crearArchCanciones(); //Crea y carga canciones en el archivo
void mostrarArchCanciones(); //Muestra el archivo canciones
nodoArbol* crearNodoArbol(cancion aux); //Crea un nodo tipo arbol
int dividirArch(int num); //Calcula la cantidad de registros en el archivo y retorna la mitad para balancear el arbol
cancion buscarCancionArch(int id); //Busca una cancion en el archivo por ID
nodoArbol* insertarArchBalanceado(nodoArbol* arbolC); //Inserta los registros del archivo en el arbol balanceadamente
nodoArbol* insertar(nodoArbol* arbolC,cancion aux); //Inserta el nuevo nodo en el arbol
nodoArbol * nodoDerecho(nodoArbol * Arbol); //Retorna el nodo mas de la derecha del arbol
nodoArbol * borrarNodo(nodoArbol * Arbol,int id); //Borra un nodo del arbol
int esGrado1(nodoArbol * Arbol); //Retorna si un nodo es grado 1
int esHoja(nodoArbol * Arbol); //Retorna si un nodo es hoja
int cuentaHojas (nodoArbol * Arbol); //Cuenta la cantidad de nodos
char eliminarCancionLogica(int id); //Cambia el estado de 1 a 0
void preorder(nodoArbol * arbol); //Muestra preorder
void inorder(nodoArbol* arbol); //Muestra inorder
void postorder(nodoArbol * arbol); //Muestra postorder
cancion buscarCancionID(nodoArbol* arbolC,int id); //Busca y retorna una cancion por ID
nodoArbol* buscapornombreArbol(nodoArbol* Arbol,char nombre[]); //Busca y retorna una cancion por nombre
void modificarCancion(int id); //Modifica la cancion buscada por ID
nodoListaCanc* crearNodoLista(cancion dato); //Crea un nodo lista cancion
nodoListaCanc* agregarPrim(nodoListaCanc* listaC,nodoListaCanc* aux); //Agrega el nuevo nodo al principio
nodoListaCanc* arbolListaAnio(nodoArbol* arbolC,nodoListaCanc* listaC); //Pasa los datos del arbol a la lista ordenados por año
nodoListaCanc* insertarXanio(nodoListaCanc* listaC,nodoListaCanc* aux); //Inserta el  nuevo nodo en la lista ordenada por antiguedad
nodoListaCanc* arbolListaNombre(nodoArbol* arbolC,nodoListaCanc* listaC); //Pasa los datos del arbol a la lista ordenados por nombre
nodoListaCanc* insertarXnombre(nodoListaCanc* listaC,nodoListaCanc* auxN); //Inserta el  nuevo nodo en la lista ordenada por nombre
nodoListaCanc* arbolListaGenero(nodoArbol* arbolC,nodoListaCanc* listaC,char genero[]); //Pasa las canciones del genero enviado por parametro a la lista
void mostrarArbolGenero(nodoArbol* arbolC,char genero[]); //Muestra el arbol filtrado por genero enviado por parametro
nodoListaCanc* liberarListaC(nodoListaCanc* listaC); //Deja la lista de canciones vacia para trabajar nuevamente
void mostrarLista(nodoListaCanc* listaC); //Muestra la lista de canciones

//USERS
int validarUsuario(usuario* auxU); //Valida el nombre y contraseña del usuario
nodoListaUsers* inicLDL(); //Inicia lista de lista
nodoListaCanc* inicLCanc(); //Inicia lista de canciones
nodoListaUsers* crearLDL(usuario dato); //Crea nodo lista de listas
usuario cargarUser(); //Crea una variable auxiliar usuario y la retorna
int alta(usuario auxU); //Corrobora que el mail del usuario a registrarse no este ya en uso
int cantArchivosFseekUsuario(FILE* archi); //Retorna la cantidad de registros de usuarios en el archivo
int cantArchivosFseekPlaylist(FILE* archi); //Retorna la cantidad de registros de playlists en el archivo
void crearArchUsers(); //Crea y carga usuarios en el archivo
void registrarse(); //Funcion para registrarse desde el punto de vista Usuario
nodoListaUsers* insertarEnListaFinal(nodoListaUsers* listaU,nodoListaUsers* nuevoU); //Inserta el usuario al final de la lista
nodoListaUsers* archivoAldl(nodoListaUsers* listaU); //Pasa los usuarios del archivo a la lista de listas
nodoListaUsers* buscarUserID(nodoListaUsers* listaU,int id); //Busca en la lista el usuario por ID
void mostrarUser(usuario aux); //Muestra un usuario enviado por parametro
void mostrarPlaylist(nodoListaCanc* playlist); //Muestra una playlist enviada por parametro
void mostrarLDL(nodoListaUsers* listaU); //Muestra la lista de lista de usuarios
void archPlaylist(usuario u,nodoArbol* arbolC); //Crea y carga registros de playlists en el archivo
nodoListaUsers* eliminarLDL(nodoListaUsers* listaU); //Elimina la lista de listas completamente y lo deja en NULL para trabajar nuevamente
nodoListaUsers* crearPlaylist(nodoListaUsers* user,nodoArbol* arbolC); //
nodoListaUsers* agregarPrimUser(nodoListaUsers* listaU,nodoListaUsers* aux); //Agrega un usuario al principio de la lista de lista
nodoListaUsers* listaEstado1(nodoListaUsers* listaU); //Pasa a una lista los usuarios dados de alta con estado=1
void eliminarUserArch(int id); //Cambia el estado del usuario de 1 a 0
void bajaLogicaCancionPlaylist(int idRegistro); //Cambia el id del registro de la playlist a -1 dandole asi una baja logica
nodoListaCanc* borrarCancionLista(nodoListaCanc* playlist,int auxID); //Borra la cancion enviada por parametro de la playlist de ese usuario
nodoListaUsers* eliminarCancionPlaylist(nodoListaUsers* user,int* IDaux); //Se envia el usuario y se pregunta que cancion se desea borrar, *IDaux sirve para luego darle la baja logica
void recomendadas(nodoListaCanc* playlist,nodoArbol* arbolC); //Muestra las canciones recomendadas para ese usuario en base a su playlist

int main()
{
    int rta;
    nodoArbol* arbolC=inicArbol(); //Arboles Canciones Totales
    nodoListaCanc* listaC=inicLCanc(); //Lista Canciones
    nodoListaUsers* listaU=inicLDL(); //LdL Usuarios
    mostrarArch(); //Muestra los datos del administrador para facilitar el ingreso.
    rta=menu();
    printf("\n");
    while (rta<4)
    {
        switch (rta)
        {
        case 1:
        {
            if (validarAdmin()==1)
            {
                rta=menuAdmin();
                printf("\n");
                while(rta<3)
                {
                    switch(rta)
                    {
                    case 1:
                    {
                        rta=menuAdminUsuarios();
                        printf("\n");
                        while(rta<6)
                        {
                            listaU=eliminarLDL(listaU);
                            listaU=archivoAldl(listaU);
                            switch (rta)
                            {
                            case 1:
                            {
                                crearArchUsers();
                                break;
                            }
                            case 2:
                            {
                                int id;
                                printf("Que usuario desea eliminar? Ingrese el ID\n");
                                printf("\n");
                                mostrarLDL(listaU);
                                printf("\n");
                                scanf("%i",&id);
                                eliminarUserArch(id);
                                listaU=eliminarLDL(listaU);
                                listaU=listaEstado1(listaU);
                                break;
                            }
                            case 3:
                            {
                                int id;
                                printf("Que usuario desea modificar? Ingrese el ID\n");
                                mostrarLDL(listaU);
                                scanf("%i",&id);
                                modificarUser(id);
                                break;
                            }
                            case 4:
                            {
                                int id;
                                printf("Ingrese el ID del usuario a buscar\n");
                                scanf("%i",&id);
                                nodoListaUsers* aux=buscarUserID(listaU,id);
                                mostrarUser(aux->dato);
                                break;
                            }
                            case 5:
                            {
                                mostrarLDL(listaU);
                                break;
                            }
                            }
                            rta=menuAdminUsuarios();
                            printf("\n");
                        }
                        break;
                    }
                    case 2:
                    {
                        rta=menuAdminCanciones();
                        printf("\n");
                        arbolC=insertarArchBalanceado(arbolC);
                        while (rta<6)
                        {
                            switch (rta)
                            {
                            case 1:
                            {
                                crearArchCanciones();
                                break;
                            }
                            case 2:
                            {
                                int id;
                                printf("Que cancion desea eliminar? Ingrese el ID\n");
                                inorder(arbolC);
                                scanf("%i",&id);
                                eliminarCancionLogica(id);
                                //eliminacionFisicaCancion();
                                break;
                            }
                            case 3:
                            {
                                int id;
                                printf("Que cancion desea modificar? Ingrese el ID\n");
                                scanf("%i",&id);
                                modificarCancion(id);
                                break;
                            }
                            case 4:
                            {
                                int id;
                                printf("Ingrese el ID de la cancion a buscar\n");
                                scanf("%i",&id);
                                cancion auxC=buscarCancionID(arbolC,id);
                                mostrarCancion(auxC);
                                break;
                            }
                            case 5:
                            {
                                int rta=menuMostrarListaC();
                                printf("\n");
                                while (rta<4)
                                {
                                    listaC=liberarListaC(listaC);
                                    switch(rta)
                                    {
                                    case 1:
                                    {
                                        listaC=arbolListaAnio(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 2:
                                    {
                                        listaC=arbolListaNombre(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 3:
                                    {
                                        char genero[30];
                                        printf("Que genero desea filtrar?\n Pop,Rap,Trap,Reggaeton,Balada\n");
                                        fflush(stdin);
                                        gets(genero);
                                        listaC=arbolListaGenero(arbolC,listaC,genero);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    break;
                                    }
                                    fflush(stdin);
                                    rta=menuMostrarListaC();
                                }
                                break;
                            }
                            }
                            rta=menuAdminCanciones();
                        }
                        break;
                    }
                    }
                    rta=menuAdmin();
                    printf("\n");
                }
            }
            break;
        }
        case 2:
        {
            usuario auxUs;
            if ((validarUsuario(&auxUs))==1)
            {
                rta=menuUsuario();
                while (rta<3)
                {
                    switch(rta)
                    {
                    case 1:
                    {
                        rta=subMenuUsuario();
                        printf("\n");
                        switch(rta)
                        {
                        case 1:
                        {
                            mostrarUser(auxUs);
                            break;
                        }
                        case 2:
                        {
                            modificarUser(auxUs.id);
                            break;
                        }
                        case 3:
                        {
                            eliminarUserArch(auxUs.id);
                            break;
                        }
                        case 4:
                            break;
                        }
                        break;
                    }
                    case 2:
                    {
                        rta=subMenuUsuarioCanciones();
                        printf("\n");
                        while (rta<6)
                        {
                            switch (rta)
                            {
                            case 1:
                            {
                                listaC=liberarListaC(listaC);
                                rta=menuMostrarListaC();
                                if (rta<4)
                                {
                                    switch(rta)
                                    {
                                    case 1:
                                    {
                                        listaC=arbolListaAnio(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 2:
                                    {
                                        listaC=arbolListaNombre(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 3:
                                    {
                                        char genero[30];
                                        printf("Que genero desea filtrar?\n POP,RAP,TRAP,REGGAETON");
                                        gets(genero);
                                        listaC=arbolListaGenero(arbolC,listaC,genero);
                                        printf("\n");
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    }
                                }
                                break;
                            }
                            case 2:
                            {
                                rta=subMenuMostrarCancionesAgregarPlaylist();
                                printf("\n");
                                while (rta<7)
                                {
                                    switch (rta)
                                    {
                                    // rta=subMenuMostrarCancionesAgregarPlaylist();
                                    //printf("\n");
                                    // switch (rta)
                                    //  {
                                    case 1:
                                    {
                                        listaC=arbolListaNombre(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 2:
                                    {
                                        listaC=arbolListaAnio(arbolC,listaC);
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 3:
                                    {
                                        char genero[30];
                                        printf("Que genero desea filtrar?\n POP,RAP,TRAP,REGGAETON");
                                        gets(genero);
                                        listaC=arbolListaGenero(arbolC,listaC,genero);
                                        printf("\n");
                                        mostrarLista(listaC);
                                        break;
                                    }
                                    case 4:
                                    {
                                        char nombre[30];
                                        printf("Ingrese el nombre a buscar\n");
                                        fflush(stdin);
                                        gets(nombre);
                                        nodoArbol* auxC=buscapornombreArbol(arbolC,nombre);
                                        mostrarCancion(auxC->dato);
                                        break;
                                    }
                                    case 5:
                                    {
                                        nodoListaUsers* auxU=buscarUserID(listaU,auxUs.id);
                                        if (auxU->playlist!=NULL)
                                            recomendadas(auxU->playlist,arbolC);
                                        else
                                            printf("Playlist vacia, no se generaron recomendaciones\n");
                                    }
                                    case 6:
                                    {
                                        break; //FINALIZA AGREGAR CANCIONES PLAYLIST
                                    }
                                        // }
                                    archPlaylist(auxUs,arbolC);
                                    nodoListaUsers* auxU=buscarUserID(listaU,auxUs.id);
                                    auxU=crearPlaylist(auxU,arbolC);
                                    mostrarPlaylist(auxU->playlist);
                                    }
                                }

                                break;
                            }
                            case 3:
                            {
                                int IDaux;
                                nodoListaUsers* auxU=buscarUserID(listaU,auxUs.id);
                                auxU=eliminarCancionPlaylist(auxU,&IDaux);
                                bajaLogicaCancionPlaylist(IDaux);
                                break;
                            }
                            case 4:
                            {
                                nodoListaUsers* auxU=buscarUserID(listaU,auxUs.id);
                                mostrarPlaylist(auxU->playlist);
                                break;
                            }
                            case 5:
                            {
                                nodoListaUsers* auxU=buscarUserID(listaU,auxUs.id);
                                if (auxU->playlist!=NULL)
                                    recomendadas(auxU->playlist,arbolC);
                                else
                                    printf("Playlist vacia, no se generaron recomendaciones\n");
                            }
                            }
                            rta=subMenuUsuarioCanciones();
                            printf("\n");
                        }
                    }
                    }
                    break;
                }
            }
            rta=menuUsuario();
            printf("\n");
            {
                registrarse();
                break;
            }
        }
        break;
        }
        rta=menu();
    }
    return 0;
}

//MENU

int menu()
{
    printf("------------------------------------------------\n");
    printf("1- Ingresar como Administrador\n");
    printf("2- Ingresar como Usuario\n");
    printf("3- Registrarse\n");
    printf("4- Salir\n");
    printf("------------------------------------------------\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int menuAdmin()
{
    printf("------------------------------------------------\n");
    printf("1- Acceder a las opciones de Usuarios\n");
    printf("2- Acceder a las opciones de Canciones\n");
    printf("3- Salir\n");
    printf("------------------------------------------------\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int menuUsuario()
{
    printf("1- SubMenu Usuario\n");
    printf("2- SubMenu Canciones\n");
    printf("3- Salir\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int subMenuUsuario()
{
    printf("1- Mostrar info del usuario\n");
    printf("2- Modificar info del usuario\n");
    printf("3- Dar de baja\n");
    printf("4- Salir\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int subMenuUsuarioCanciones()
{
    printf("1- Mostrar canciones de la plataforma\n");
    printf("2- Agregar canciones a la playlist\n");
    printf("3- Eliminar canciones de la playlist\n");
    printf("4 -Mostrar canciones de la playlist\n");
    printf("5- Mostrar canciones recomendadas\n");
    printf("6- Salir\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int subMenuMostrarCancionesAgregarPlaylist()
{
    printf("1- Ver todas las canciones por orden alfabetico\n");
    printf("2- Ver todas las canciones por antiguedad\n");
    printf("3- Filtrar por genero\n");
    printf("4- Buscar cancion por nombre\n");
    printf("5- Mostrar canciones recomendadas\n");
    printf("6- Salir\n");
    int rta;
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int menuAdminUsuarios()
{
    int rta;
    printf("------------------------------------------------\n");
    printf("1- Alta usuarios \n");
    printf("2- Baja usuarios \n");
    printf("3- Modificar usuarios \n");
    printf("4- Consulta usuarios \n");
    printf("5- Lista de usuarios \n");
    printf("6- Salir\n");
    printf("------------------------------------------------\n");
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int menuAdminCanciones()
{
    int rta;
    printf("------------------------------------------------\n");
    printf("1- Alta canciones \n");
    printf("2- Baja canciones \n");
    printf("3- Modificar canciones \n");
    printf("4- Consulta canciones \n");
    printf("5- Lista de canciones \n");
    printf("6- Salir\n");
    printf("------------------------------------------------\n");
    printf("Que opcion desea realizar?\n");
    fflush(stdin);
    scanf("%i",&rta);
    return rta;
}

int menuModificarUser()
{
    printf("1- Mail\n");
    printf("2- Nombre\n");
    printf("3- Telefono\n");
    printf("4- Contrasenia\n");
    printf("5- Dar de alta al usuario");
    int rta;
    scanf("%i",&rta);
    return rta;
}

int menuModificarCancion()
{
    printf("1- Anio\n");
    printf("2- Nombre\n");
    printf("3- Genero\n");
    printf("4- Cantantes\n");
    int rta;
    scanf("%i",&rta);
    return rta;
}

int menuModificarCantantes(cancion aux)
{
    printf("Que cantante desea cambiar?\n");
    for (int i=0; i<aux.cantCantantes; i++)
    {
        printf("%i- Cantante Numero %i",i,i);
    }
    int rta;
    scanf("%i",&rta);
    return rta;
}

int menuMostrarListaC()
{
    printf("1- Ordenadas por anio\n");
    printf("2- Ordenadas por nombre\n");
    printf("3- Filtradas por genero\n");
    printf("4- Salir\n");
    int rta;
    scanf("%i",&rta);
    return rta;
}

//ADMIN
admin cargarAdmin()
{
    admin aux;
    printf("Ingrese el nombre del administrador\n");
    fflush(stdin);
    gets(aux.apellidoYnombre);
    printf("Ingrese el mail\n");
    fflush(stdin);
    gets(aux.mail);
    printf("Ingrese el celular del administrador\n");
    fflush(stdin);
    scanf("%i",&aux.celular);
    printf("Ingrese una contraseña de 8 caracteres\n");
    fflush(stdin);
    gets(aux.contrasenia);
    return aux;
}

void crearArchAdmin()
{
    FILE* archi=fopen("admin","wb");
    admin aux;
    if (archi!=NULL)
    {
        aux=cargarAdmin();
        fwrite(&aux,sizeof(admin),1,archi);
    }
    fclose(archi);
}

void mostrarArch()
{
    FILE* archi=fopen("admin","rb");
    admin aux;
    if (archi!=NULL)
    {
        fread(&aux,sizeof(admin),1,archi);
        printf("Nombre: %s\n",aux.apellidoYnombre);
        printf("Mail: %s\n",aux.mail);
        printf("Celular: %i\n",aux.celular);
        printf("Contrasenia: %s\n",aux.contrasenia);
    }
    fclose(archi);
}

int validarAdmin()
{
    FILE* archi=fopen("admin","rb");
    int rta=0;
    char nombre[30];
    char contrasenia[30];
    admin aux;
    if (archi!=NULL)
    {
        printf("Ingrese el nombre del administrador\n");
        fflush(stdin);
        gets(nombre);
        printf("Ingrese una contraseña de 8 caracteres\n");
        fflush(stdin);
        gets(contrasenia);
        fread(&aux,sizeof(admin),1,archi);
        if (strcmp(aux.apellidoYnombre,nombre)==0 && strcmp(aux.contrasenia,contrasenia)==0)
        {
            rta=1;
            printf("Ingreso con exito\n");
        }
        else
        {
            printf("Usuario o contrasenia incorrecto\n");
        }
    }
    return rta;
}

//CANCIONES
nodoArbol* inicArbol()
{
    return NULL;
}

int cantArchivosFseek(FILE* archi)
{
    int pos;
    fseek(archi,0,SEEK_END);
    pos=ftell(archi)/sizeof(cancion);
    return pos;
}

cancion cargarCancion()
{
    cancion aux;
    char seguir;
    int i=0;
    aux.id=0;
    printf("Ingrese nombre de la cancion\n");
    fflush(stdin);
    gets(aux.nombre);
    printf("Ingrese anio de salida\n");
    fflush(stdin);
    scanf("%i",&aux.anio);
    printf("Ingrese el genero\n");
    fflush(stdin);
    gets(aux.genero);
    do
    {
        printf("Ingrese el nombre del cantante\n");
        fflush(stdin);
        gets(aux.cantantes[i]);
        printf("Tiene mas cantantes? S/N\n");
        fflush(stdin);
        i++;
        aux.cantCantantes=i;
        scanf("%c",&seguir);
    }
    while (seguir=='s' && i<3);
    aux.estado=1;
    return aux;
}

void crearArchCanciones()
{
    FILE* archi=fopen("listaCanciones","ab");
    cancion aux;
    char seguir;
    if (archi!=NULL)
    {
        printf("Desea ingresar canciones al archivo? S/N\n");
        fflush(stdin);
        scanf("%c",&seguir);
        while (seguir=='s')
        {
            aux=cargarCancion();
            int auxID=cantArchivosFseek(archi);
            aux.id=auxID+1;
            fwrite(&aux,sizeof(cancion),1,archi);
            printf("Desea ingresar mas canciones al archivo? S/N\n");
            fflush(stdin);
            scanf("%c",&seguir);
        }
    }
    fclose(archi);
}

void mostrarCancion(cancion aux)
{
    printf("ID: %i\n",aux.id);
    printf("Nombre de la cancion: %s\n",aux.nombre);
    printf("Anio de salida: %i\n",aux.anio);
    printf("Genero: %s\n",aux.genero);
    for (int i=0; i<aux.cantCantantes; i++)
    {
        printf("Cantante: %s\n",aux.cantantes[i]);
    }
    printf("Estado: %i\n",aux.estado);
}

void mostrarArchCanciones()
{
    FILE* archi=fopen("listaCanciones","rb");
    cancion aux;
    while (fread(&aux,sizeof(cancion),1,archi))
    {
        printf("\n");
        mostrarCancion(aux);
    }
    fclose(archi);
}

nodoArbol* crearNodoArbol(cancion aux)
{
    nodoArbol* auxC=(nodoArbol*)malloc(sizeof(nodoArbol));
    auxC->dato=aux;
    auxC->der=NULL;
    auxC->izq=NULL;
    return auxC;
}

int dividirArch(int num)
{
    int aux;
    aux=num/2;
    return aux;
}

cancion buscarCancionArch(int id)
{
    FILE* archi=fopen("listaCanciones","rb");
    cancion aux;
    if (archi)
    {
        fseek(archi,sizeof(cancion)*(id-1),SEEK_SET);
        fread(&aux,sizeof(cancion),1,archi);
    }
    fclose(archi);
    return aux;
}

nodoArbol* insertarArchBalanceado(nodoArbol* arbolC)
{
    FILE* archi=fopen("listaCanciones","rb");
    int aux;
    cancion auxC;
    aux=dividirArch(cantArchivosFseek(archi))+1;
    auxC=buscarCancionArch(aux);
    arbolC=insertar(arbolC,auxC);
    fseek(archi,0,SEEK_SET);
    while (fread(&auxC,sizeof(cancion),1,archi))
    {
        if (auxC.id!=aux)
        {
            arbolC=insertar(arbolC,auxC);
        }
    }
    fclose(archi);
    return arbolC;
}

nodoArbol* insertar(nodoArbol* arbolC,cancion aux)
{

    if (arbolC == NULL)
        arbolC = crearNodoArbol(aux);
    else
    {
        if (aux.id>arbolC->dato.id)
            arbolC->der=insertar(arbolC->der,aux);
        else
            arbolC->izq=insertar(arbolC->izq,aux);
    }
    return arbolC;
}

nodoArbol* nodoDerecho(nodoArbol* Arbol)
{
    nodoArbol * aux;
    if(Arbol->der==NULL)
    {
        aux=Arbol;
    }
    else
    {
        aux=nodoDerecho(Arbol->der);
    }
    return aux;
}

nodoArbol * nodoIzquierdo(nodoArbol * Arbol)
{
    nodoArbol * aux;
    if(Arbol->izq==NULL)
    {
        aux=Arbol;
    }
    else
    {
        aux=nodoIzquierdo(Arbol->izq);
    }
    return aux;
}

nodoArbol * borrarNodo(nodoArbol * Arbol,int id)
{
    if(Arbol!=NULL)
    {
        if(id > Arbol->dato.id)
        {
            Arbol->der=borrarNodo(Arbol->der,id);
        }
        else if(id<Arbol->dato.id)
        {
            Arbol->izq=borrarNodo(Arbol->izq,id);
        }
        else if(id==Arbol->dato.id)
        {
            if(esHoja(Arbol))//no tiene hijos
            {
                free(Arbol);
                Arbol=NULL;
            }
            else if(esGrado1(Arbol))//tiene un solo hijo
            {
                nodoArbol * aux;
                if(Arbol->der)
                {
                    aux=Arbol;
                    Arbol=Arbol->der;
                    free(aux);
                }
                else
                {
                    aux=Arbol;
                    Arbol=Arbol->izq;
                    free(aux);
                }
            }
            else//tiene dos hijos
            {
                nodoArbol * masDer= nodoDerecho(Arbol->izq);
                Arbol->dato=masDer->dato ;
                Arbol->izq=borrarNodo(Arbol->izq,Arbol->dato.id);
            }
        }
    }
    return Arbol;
}

int esGrado1(nodoArbol * Arbol)
{
    int rta=0;

    if(Arbol)
    {
        if((Arbol->izq==NULL && Arbol->der!=NULL)||(Arbol->izq!=NULL && Arbol->der==NULL))
        {
            rta=1;
        }
    }
    return rta;
}

int esHoja(nodoArbol * Arbol)
{
    int rta=0;
    if(Arbol)
    {
        if(Arbol->izq==NULL && Arbol->der==NULL)
        {
            rta=1;
        }
    }
    return rta;
}

int cuentaHojas (nodoArbol * Arbol)
{
    int contar;

    if(Arbol==NULL)
    {
        contar=0;
    }
    else
    {
        if(esHoja(Arbol))
        {
            contar=1;
        }
        else
        {
            contar=cuentaHojas(Arbol->izq)+cuentaHojas(Arbol->der);
        }
    }
    return contar;
}

char eliminarCancionLogica(int id)
{
    FILE *archivo=fopen("listaCanciones","r+b");
    cancion aux;
    char elimina;
    archivo = fopen("listaCanciones", "r+b");
    if (archivo == NULL)
    {
        elimina = 0;
    }
    else
    {
        elimina = 0;
        fread(&aux, sizeof(cancion), 1, archivo);
        while (!feof(archivo))
        {
            if (aux.id == id)
            {
                fseek(archivo, sizeof(cancion)*(id-1), SEEK_SET);
                aux.estado = 0;
                fwrite(&aux, sizeof(cancion), 1, archivo);
                elimina = 1;
                break;
            }
            fread(&aux, sizeof(cancion), 1, archivo);
        }
        fclose(archivo);
    }
    return elimina;
}

void preorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        printf("-----------------------\n");
        mostrarCancion(arbol->dato);
        printf("-----------------------\n");
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol* arbol)
{
    if (arbol!=NULL)
    {
        inorder(arbol->izq);
        printf("-----------------------\n");
        mostrarCancion(arbol->dato);
        printf("-----------------------\n");
        inorder(arbol->der);
    }
}

void postorder(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        printf("-----------------------\n");
        mostrarCancion(arbol->dato);
        printf("-----------------------\n");
    }
}

cancion buscarCancionID(nodoArbol* arbolC,int id)
{
    cancion rta;
    if (arbolC!=NULL)
    {
        if(id==arbolC->dato.id)
        {
            rta=arbolC->dato;
        }
        else
        {
            if(id>arbolC->dato.id)
            {
                rta=buscarCancionID(arbolC->der,id);
            }
            else
            {
                rta=buscarCancionID(arbolC->izq,id);
            }
        }
    }
    return rta;
}

nodoArbol* buscapornombreArbol(nodoArbol* Arbol,char nombre[])
{
    nodoArbol* rta=NULL;
    if(Arbol!=NULL)
    {
        if(strcmp(Arbol->dato.nombre,nombre)==0)
        {
            rta=Arbol;
        }
        else
        {
            rta=buscapornombreArbol(Arbol->izq,nombre);
            if(rta==NULL)
            {
                rta=buscapornombreArbol(Arbol->der,nombre);
            }
        }
    }
    if (rta==NULL)
    {
        printf("No se encontro la cancion %s\n",nombre);
    }
    return rta;
}

void modificarCancion(int id)
{
    FILE* archi=fopen("listaCanciones","r+b");
    int rta;
    cancion aux;
    int auxCant=cantArchivosFseek(archi);
    if (archi)
    {
        if (id>auxCant)
        {
            printf("ERROR Cancion no encontrado\n");
        }
        else
        {
            fseek(archi,sizeof(cancion)*(id-1),SEEK_SET);
            fread(&aux,sizeof(cancion),1,archi);
            mostrarCancion(aux);
            printf("Que campo desea modificar?\n");
            fflush(stdin);
            rta=menuModificarCancion();
            switch(rta)
            {
            case 1:
            {
                printf("Ingrese el año modificado\n");
                fflush(stdin);
                scanf("%i",&aux.anio);
                break;
            }
            case 2:
            {
                printf("Ingrese su nombre\n");
                fflush(stdin);
                gets(aux.nombre);
                break;
            }
            case 3:
            {
                printf("Ingrese su genero\n");
                fflush(stdin);
                gets(aux.genero);
                break;
            }
            case 4:
            {
                int rta=menuModificarCantantes(aux);
                switch(rta)
                {
                case 1:
                {
                    gets(aux.cantantes[0]);
                    break;
                }
                case 2:
                {
                    gets(aux.cantantes[1]);
                    break;
                }
                case 3:
                {
                    gets(aux.cantantes[2]);
                    break;
                }
                }
                break;
            }
            }
            fseek(archi,sizeof(cancion)*(id-1),SEEK_SET);
            fwrite(&aux,sizeof(cancion),1,archi);
        }
        fclose(archi);
    }
}
nodoListaCanc* crearNodoLista(cancion dato)
{
    nodoListaCanc* aux=(nodoListaCanc*)malloc(sizeof(nodoListaCanc));
    aux->dato=dato;
    aux->sig=NULL;
    return aux;
}
nodoListaCanc* agregarPrim(nodoListaCanc* listaC,nodoListaCanc* aux)
{
    if (listaC==NULL)
        listaC=aux;
    else
    {
        aux->sig=listaC;
        listaC=aux;
    }
    return listaC;
}

nodoListaCanc* arbolListaAnio(nodoArbol* arbolC,nodoListaCanc* listaC)
{
    cancion aux;
    if (arbolC!=NULL)
    {
        listaC=arbolListaAnio(arbolC->izq,listaC);
        aux=arbolC->dato;
        nodoListaCanc* auxN=crearNodoLista(aux);
        listaC=insertarXanio(listaC,auxN);
        listaC=arbolListaAnio(arbolC->der,listaC);
    }
    return listaC;
}
nodoListaCanc* insertarXanio(nodoListaCanc* listaC,nodoListaCanc* aux)
{
    if (listaC==NULL)
        listaC=aux;
    else if ((aux->dato.anio) <= (listaC->dato.anio))
        listaC=agregarPrim(listaC,aux);
    else
    {
        nodoListaCanc* ante=listaC;
        nodoListaCanc* seg=listaC->sig;
        while ( (seg != NULL) && (aux->dato.anio > seg->dato.anio) )
        {
            ante=seg;
            seg=seg->sig;
        }
        ante->sig=aux;
        aux->sig=seg;
    }
    return listaC;
}

nodoListaCanc* arbolListaNombre(nodoArbol* arbolC,nodoListaCanc* listaC)
{
    cancion aux;
    if (arbolC!=NULL)
    {
        listaC=arbolListaNombre(arbolC->izq,listaC);
        aux=arbolC->dato;
        nodoListaCanc* auxN=crearNodoLista(aux);
        listaC=insertarXnombre(listaC,auxN);
        listaC=arbolListaNombre(arbolC->der,listaC);
    }
    return listaC;
}
nodoListaCanc* insertarXnombre(nodoListaCanc* listaC,nodoListaCanc* nuevoNodo)
{
    if(listaC==NULL)
    {
        listaC=nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->dato.nombre,listaC->dato.nombre)<0)
        {
            listaC=agregarPrim(listaC,nuevoNodo);
        }
        else
        {
            nodoListaCanc* ante=listaC;
            nodoListaCanc* seg=listaC->sig;
            while((seg!=NULL)&&strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>=0)
            {
                ante=seg;
                seg=seg->sig;
            }
            nuevoNodo->sig=seg;
            ante->sig=nuevoNodo;
        }
    }
    return listaC;
}

nodoListaCanc* arbolListaGenero(nodoArbol* arbolC,nodoListaCanc* listaC,char genero[])
{
    cancion aux;
    if (arbolC!=NULL)
    {
        listaC=arbolListaGenero(arbolC->izq,listaC,genero);
        if (strcmp(arbolC->dato.genero,genero)==0)
        {
            aux=arbolC->dato;
            nodoListaCanc* auxN=crearNodoLista(aux);
            listaC=agregarPrim(listaC,auxN);

        }
        listaC=arbolListaGenero(arbolC->der,listaC,genero);
    }
    return listaC;
}

void mostrarArbolGenero(nodoArbol* arbolC,char genero[])
{
    if (arbolC!=NULL)
    {
        mostrarArbolGenero(arbolC->izq,genero);
        if (strcmp(arbolC->dato.genero,genero)==0)
        {
            mostrarCancion(arbolC->dato);

        }
        mostrarArbolGenero(arbolC->der,genero);
    }
}

nodoListaCanc* liberarListaC(nodoListaCanc* listaC)
{
    nodoListaCanc* aBorrar=listaC;
    while(listaC!=NULL)
    {
        aBorrar=listaC;
        free(aBorrar);
        listaC=listaC->sig;
    }
    free(aBorrar);
    return listaC;
}

void mostrarLista(nodoListaCanc* listaC)
{
    while (listaC!=NULL)
    {
        mostrarCancion(listaC->dato);
        listaC=listaC->sig;
    }
}

//USUARIOS

int validarUsuario(usuario* auxU)
{
    FILE* archi=fopen("usuarios","rb");
    int rta=0;
    char nombre[30];
    char contrasenia[30];
    usuario aux;
    if (archi!=NULL)
    {
        printf("Ingrese el nombre del usuario\n");
        fflush(stdin);
        gets(nombre);
        printf("Ingrese una contraseña de 8 caracteres\n");
        fflush(stdin);
        gets(contrasenia);
        while (fread(&aux,sizeof(usuario),1,archi))
        {
            if ((strcmp(aux.apellidoYnombre,nombre)==0) && (strcmp(aux.contrasenia,contrasenia)==0))
            {
                rta=1;
                printf("Ingreso con exito\n");
                *auxU=aux;
            }
        }
        if (rta==0)
        {
            printf("Usuario o contrasenia incorrecto\n");
        }
    }
    return rta;
}

nodoListaUsers* inicLDL()
{
    return NULL;
}

nodoListaCanc* inicLCanc()
{
    return NULL;
}

nodoListaUsers* crearLDL(usuario dato)
{
    nodoListaUsers* aux=(nodoListaUsers*)malloc(sizeof(nodoListaUsers));
    aux->dato=dato;
    aux->sig=NULL;
    aux->playlist=NULL;
    return aux;
}

usuario cargarUser()
{
    usuario aux;
    printf("Ingrese el nombre del usuario\n");
    fflush(stdin);
    gets(aux.apellidoYnombre);
    printf("Ingrese el mail\n");
    fflush(stdin);
    gets(aux.mail);
    printf("Ingrese el celular\n");
    fflush(stdin);
    scanf("%i",&aux.celular);
    printf("Ingrese una contrasenia de 8 caracteres\n");
    fflush(stdin);
    gets(aux.contrasenia);
    aux.estado=1;
    aux.id=0;
    return aux;
}

int alta(usuario auxU)
{
    FILE* archi=fopen("usuarios","rb");
    usuario aux;
    int rta=1;
    if (archi!=NULL)
    {
        while (fread(&aux,sizeof(usuario),1,archi))
        {
            if (strcmp(aux.mail,auxU.mail)==0)
            {
                rta=0;
            }
        }
    }
    return rta;
}

int cantArchivosFseekUsuario(FILE* archi)
{
    int pos;
    fseek(archi,0,SEEK_END);
    pos=ftell(archi)/sizeof(usuario);
    return pos;
}

int cantArchivosFseekPlaylist(FILE* archi)
{
    int pos;
    fseek(archi,0,SEEK_END);
    pos=ftell(archi)/sizeof(stRegistroPlaylist);
    return pos;
}

void crearArchUsers()
{
    FILE* archi=fopen("usuarios","ab");
    usuario aux;
    int rta;
    char seguir;
    if (archi!=NULL)

    {
        printf("Desea ingresar usuarios al sistema? S/N\n");
        fflush(stdin);
        scanf("%c",&seguir);
        while (seguir=='s')
        {
            aux=cargarUser();
            rta=alta(aux);
            while (rta==0)
            {
                printf("Mail ya en uso\n");
                printf("Ingrese un mail nuevo\n");
                gets(aux.mail);
                rta=alta(aux);
            }
            int auxID=cantArchivosFseekUsuario(archi);
            aux.id=auxID+1;
            fwrite(&aux,sizeof(usuario),1,archi);
            printf("Desea ingresar mas usuarios al sistema? S/N\n");
            fflush(stdin);
            scanf("%c",&seguir);
        }
    }
    fclose(archi);
}

void registrarse()
{
    FILE* archi=fopen("usuarios","ab");
    usuario aux;
    int rta;
    if (archi!=NULL)
    {
        aux=cargarUser();
        rta=alta(aux);
        while (rta==0)
        {
            printf("Mail ya en uso\n");
            printf("Ingrese un mail nuevo\n");
            gets(aux.mail);
            rta=alta(aux);
        }
        int auxID=cantArchivosFseekUsuario(archi);
        aux.id=auxID+1;
        fwrite(&aux,sizeof(usuario),1,archi);
    }
    fclose(archi);
}

nodoListaUsers* insertarEnListaFinal(nodoListaUsers* listaU,nodoListaUsers* nuevoU)
{
    if (listaU==NULL)
    {
        listaU=nuevoU;
    }
    else
    {
        nodoListaUsers* seg=listaU;
        while (seg->sig!=NULL)
        {
            seg=seg->sig;
        }
        seg->sig=nuevoU;
    }
    return listaU;
}

nodoListaUsers* archivoAldl(nodoListaUsers* listaU)
{
    FILE* archi=fopen("usuarios","rb");
    if (archi!=NULL)
    {
        usuario aux;
        while (fread(&aux,sizeof(usuario),1,archi))
        {
            nodoListaUsers* auxU=crearLDL(aux);
            listaU=insertarEnListaFinal(listaU,auxU);
        }
    }
    return listaU;
}

nodoListaUsers* buscarUserID(nodoListaUsers* listaU,int id)
{
    nodoListaUsers* auxU=NULL;
    if (listaU!=NULL)
    {
        nodoListaUsers* seg=listaU;
        while ((seg!=NULL) && (seg->dato.id!=id))
        {
            seg=seg->sig;
        }
        if (seg!=NULL)
        {
            auxU=seg;
        }
        else
            printf("No se encontro el usuario con ID %i\n",id);
    }
    return auxU;
}

void mostrarUser(usuario aux)
{
    printf("Nombre y apellido: %s\n",aux.apellidoYnombre);
    printf("Telefono: %i\n",aux.celular);
    printf("Mail: %s\n",aux.mail);
    printf("ID: %i\n",aux.id);
    printf("Estado: %i\n",aux.estado);
}

void mostrarPlaylist(nodoListaCanc* playlist)
{
    if (playlist!=NULL)
    {
        while(playlist!=NULL)
        {
            mostrarCancion(playlist->dato);
            playlist=playlist->sig;
        }
    }
    else
        printf("Playlist vacia\n");
}

void mostrarLDL(nodoListaUsers* listaU)
{
    if (listaU==NULL)
        printf("lista de usuarios vacia\n");
    while (listaU!=NULL)
    {
        printf("--------------------------\n");
        mostrarUser(listaU->dato);
        mostrarPlaylist(listaU->playlist);
        listaU=listaU->sig;
        printf("--------------------------\n");
    }
}

void archPlaylist(usuario u,nodoArbol* arbolC) //Crear archivo con estructura playlist, emparejando id de cancion con id de usuario.
{
    FILE* archi=fopen("registroPlaylist","ab");
    char nombreC[30];
    nodoArbol* aux;
    char seguir;
    stRegistroPlaylist auxP;
    if (arbolC!=NULL)
    {
        do
        {
            printf("Que cancion desea agregar a su playlist?\n");
            fflush(stdin);
            gets(nombreC);
            aux=buscapornombreArbol(arbolC,nombreC);
            auxP.idCancion=aux->dato.id;
            auxP.idRegistroPlaylist=cantArchivosFseekPlaylist(archi)+1;
            auxP.idUsuario=u.id;
            fwrite(&auxP,sizeof(stRegistroPlaylist),1,archi);
            printf("Desea ingresar mas canciones a su playlist?\n");
            fflush(stdin);
            scanf("%c",&seguir);
        }
        while (seguir=='s');
    }
    fclose(archi);
}

nodoListaUsers* eliminarLDL(nodoListaUsers* listaU)
{
    while (listaU!=NULL)
    {
        nodoListaUsers* ante=listaU;
        listaU=listaU->sig;
        free(ante);
    }
    return listaU;
}

nodoListaUsers* crearPlaylist(nodoListaUsers* user,nodoArbol* arbolC)
{
    FILE* archi=fopen("registroPlaylist","rb");
    stRegistroPlaylist aux;
    user->playlist=inicLCanc();
    while (fread(&aux,sizeof(stRegistroPlaylist),1,archi))
    {
        if (aux.idUsuario==user->dato.id)
        {
            cancion auxC=buscarCancionID(arbolC,aux.idCancion);
            nodoListaCanc* auxP=crearNodoLista(auxC);
            agregarPrim(user->playlist,auxP);
        }
    }
    return user;
}

nodoListaUsers* agregarPrimUser(nodoListaUsers* listaU,nodoListaUsers* aux)
{
    if (listaU==NULL)
        listaU=aux;
    else
    {
        aux->sig=listaU;
        listaU=aux;
    }
    return listaU;
}

nodoListaUsers* listaEstado1(nodoListaUsers* listaU)
{
    FILE* archi= fopen("usuarios","rb");
    usuario aux;
    if (archi)
    {
        while (fread(&aux, sizeof(usuario), 1, archi));
        {
            if (aux.estado==0)
            {
                nodoListaUsers* auxN=crearLDL(aux);
                listaU=agregarPrimUser(listaU,auxN);
            }
        }
    }
    fclose(archi);
    return listaU;
}

void eliminarUserArch(int id)
{
    FILE* archi=fopen("usuarios","r+b");
    char s;
    int flag=1;
    usuario aux;
    if (archi!=NULL)
    {
        fread(&aux,sizeof(usuario),1,archi);
        while ((!feof(archi)) && (flag==1))
        {
            if (aux.id==id)
            {
                fseek(archi,sizeof(usuario)*(id-1),SEEK_SET);
                aux.estado=0;
                printf("Desea eliminar el usuario?\n");
                fflush(stdin);
                scanf("%c",&s);
                if (s=='s')
                {
                    fwrite(&aux,sizeof(usuario),1,archi);
                    flag=0;
                    mostrarUser(aux);
                }
                break;
            }
            fread(&aux,sizeof(usuario),1,archi);
        }
        fclose(archi);
    }
}

void modificarUser(int id)
{
    usuario aux;
    int rta;
    FILE* archi=fopen("usuarios","r+b");
    int auxCant=cantArchivosFseekUsuario(archi);
    if (archi)
    {
        if (id>auxCant)
        {
            printf("ERROR Usuario no encontrado\n");
        }
        else
        {
            fseek(archi,sizeof(usuario)*(id-1),SEEK_SET);
            fread(&aux,sizeof(usuario),1,archi);
            mostrarUser(aux);
            printf("Que campo desea modificar?\n");
            fflush(stdin);
            rta=menuModificarUser();
            switch(rta)
            {
            case 1:
            {
                printf("Ingrese el nuevo mail\n");
                fflush(stdin);
                gets(aux.mail);
                int rta=alta(aux);
                while (rta==0)
                {
                    printf("Mail ya en uso\n");
                    printf("Ingrese un mail nuevo\n");
                    gets(aux.mail);
                    rta=alta(aux);
                }
                break;
            }
            case 2:
            {
                printf("Ingrese su nombre\n");
                fflush(stdin);
                gets(aux.apellidoYnombre);
                break;
            }
            case 3:
            {
                printf("Ingrese el nuevo telefono\n");
                scanf("%i",&aux.celular);
                break;
            }
            case 4:
            {
                printf("Ingrese su nueva contrasenia\n");
                fflush(stdin);
                gets(aux.contrasenia);
                break;
            }
            case 5:
            {
                aux.estado=1;
            }
            }
            fseek(archi,sizeof(usuario)*(id-1),SEEK_SET);
            fwrite(&aux,sizeof(usuario),1,archi);
        }
        fclose(archi);
    }
}

void bajaLogicaCancionPlaylist(int idRegistro)
{
    FILE* archi=fopen("registroPlaylist","rb");
    stRegistroPlaylist aux;
    if (archi)
    {
        fseek(archi,sizeof(stRegistroPlaylist)*(idRegistro-1),SEEK_SET);
        fread(&aux,sizeof(stRegistroPlaylist),1,archi);
        {
            if (idRegistro==aux.idRegistroPlaylist)
            {
                aux.idRegistroPlaylist=-1;
            }
            fseek(archi,sizeof(stRegistroPlaylist)*(idRegistro-1),SEEK_SET);
            fwrite(&aux,sizeof(stRegistroPlaylist),1,archi);
        }
    }
    fclose(archi);
}

nodoListaCanc* borrarCancionLista(nodoListaCanc* playlist,int auxID)
{
    if (playlist!=NULL)
    {
        if (playlist->dato.id==auxID)
        {
            nodoListaCanc* aBorrar=playlist;
            playlist=playlist->sig;
            free(aBorrar);
        }
        else
        {
            nodoListaCanc* ante=playlist;
            nodoListaCanc* seg=playlist->sig;
            while ((seg!=NULL) && (seg->dato.id!=auxID))
            {
                ante=seg;
                seg=seg->sig;
            }
            if (seg!=NULL)
            {
                ante->sig=seg->sig;
                free(seg);
            }
        }
    }
    return playlist;
}

nodoListaUsers* eliminarCancionPlaylist(nodoListaUsers* user,int* IDaux)
{
    int auxID;
    printf("Canciones en la playlist\n");
    mostrarPlaylist(user->playlist);
    printf("Que cancion desea borrar?\n");
    fflush(stdin);
    scanf("%i",&auxID);
    (*IDaux)=auxID;
    user->playlist=borrarCancionLista(user->playlist,auxID);
    return user;
}

void recomendadas(nodoListaCanc* playlist,nodoArbol* arbolC)
{
    int pop=0;
    int trap=0;
    int balada=0;
    int reggaeton=0;
    int rock=0;
    int techno=0;
    int mayor=0;
    char generoR[30];
    while (playlist!=NULL)
    {
        if (strcmp(playlist->dato.genero,"Pop")==0)
        {
            pop=pop+1;
        }
        else if (strcmp(playlist->dato.genero,"Trap")==0)
        {
            trap=trap+1;
        }
        else if(strcmp(playlist->dato.genero,"Balada")==0)
        {
            balada=balada+1;
        }
        else if (strcmp(playlist->dato.genero,"Reggaeton")==0)
        {
            reggaeton=reggaeton+1;
        }
        else if (strcmp(playlist->dato.genero,"Rock")==0)
        {
            rock=rock+1;
        }
        else
        {
            techno=techno+1;
        }
        playlist=playlist->sig;
    }
    mayor=pop;
    strcpy(generoR,"pop");
    if (trap>mayor)
    {
        mayor=trap;
        strcpy(generoR,"trap");
    };
    if (balada>mayor)
    {
        mayor=balada;
        strcpy(generoR,"balada");
    };
    if (reggaeton>mayor)
    {
        mayor=reggaeton;
        strcpy(generoR,"reggaeton");
    };
    if (rock>mayor)
    {
        mayor=rock;
        strcpy(generoR,"rock");
    };
    if (techno>mayor)
    {
        mayor=techno;
        strcpy(generoR,"techno");
    };
    printf("Canciones recomendadas\n");
    mostrarArbolGenero(arbolC,generoR);
}

















