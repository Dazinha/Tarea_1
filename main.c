//================================================
//Incluir bibliotecas para nuestro programa
//================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
//================================================
//Definir capacidad máxima para valores string
//================================================
#define MAXCHAR51 51
#define MAXCHAR21 21
//================================================
//Definición de estructuras para el programa
//================================================
typedef struct Libro {
  char titulo[MAXCHAR51];
  char autor[MAXCHAR51];
  char genero[MAXCHAR51];
  char ISBN[MAXCHAR21];
  char ubicacion[MAXCHAR51];
  char estado[MAXCHAR21];
  List *reservas;
} Libro;

typedef struct Node {
    void *data;
    struct Node *next;
} Node;
//================================================
//Funciones para nuestra lista de libros
//================================================
void leer51(char cadena[MAXCHAR51]);
void leer21(char cadena[MAXCHAR21]);
void registrarLibro(List *lista);
void mostrarDatosLibro(List *lista);
void mostrarLibros(List *lista);
void reservarLibro(List *lista);
void cancelarReservaLibro(List *lista);
void retirarLibro(List *lista);
void devolverLibro(List *lista);
void mostrarLibrosPrestados(List *lista);
const char *get_csv_field(char *tmp, int k);
void importarLibrosCSV(List *lista);
void exportarLibrosACSV(List *lista, const char *nombreArchivo);

//================================================
//Función para nuestro menú principal
//================================================
void imprimirMenu() {
  printf("==================================================\n");
  printf("                    Biblioteca                  \n");
  printf("==================================================\n\n");
  printf("1. Registrar un libro\n");
  printf("2. Mostrar datos de un libro\n");
  printf("3. Mostrar libros de la biblioteca\n");
  printf("4. Reserva de un libro\n");
  printf("5. Cancelar la reserva de libro\n");
  printf("6. Retirar un libro\n");
  printf("7. Devolver un libro\n");
  printf("8. Mostrar los libros prestados\n");
  printf("9. Importar los libros desde archivo CSV\n");
  printf("10. Exportar los libros a archivo CSV\n");
  printf("0. Exit\n\n");
  printf("Ingrese una opción: ");
}

int main() {
  List *lista = createList();
  int opcion;

  while(true){
    imprimirMenu();
    scanf("%d", &opcion);
    if(opcion == 1)
    {
      registrarLibro(lista);
    }
    else if(opcion == 2)
    {
      mostrarDatosLibro(lista);
    }
    else if(opcion == 3)
    {
      mostrarLibros(lista);
    }
    else if(opcion == 4)
    {
      reservarLibro(lista);
    }
    else if(opcion == 5)
    {
      cancelarReservaLibro(lista);
    }
    else if(opcion == 6)
    {
      retirarLibro(lista);
    }
    else if(opcion == 7)
    {
      devolverLibro(lista);
    }
    else if(opcion == 8)
    {
      mostrarLibrosPrestados(lista);
    }
    else if(opcion == 9)
    {
      importarLibrosCSV(lista);
    }
    else if( opcion == 10)
    {
      exportarLibrosACSV(lista, "biblioteca.csv");
    }
    else if( opcion == 0)
    {
      printf("\nSesión Finalizada.\n");
      printf("\n¡Has finalizado tu sesión!\n");
      return 0;
    }
    else
    {
      printf("\nOpción inválida. Ingrese opción nuevamente.\n");
    }
  }
    
  // liberar memoria de la biblioteca
  Node *nodoLibro = firstList(lista);

  while (nodoLibro != NULL) 
  {
    Libro *libro = nodoLibro->data;
    cleanList(libro->reservas);
    free(libro);
    nodoLibro = nextList(lista);
  }

  cleanList(lista);
  free(lista);
  return 0;
}

//================================================
//Funciones de lectura de caracteres
//================================================
void leer51(char cadena[MAXCHAR51]){
  scanf("%50[^\n]s",cadena);
  int largo=strlen(cadena);
  if(largo>50){
    printf("No se ha podido registrar");
  }
  getchar();
}

void leer21(char cadena[MAXCHAR21]){
  scanf("%20[^\n]s",cadena);
  int largo=strlen(cadena);
  if(largo>20){
    printf("No se ha podido registrar");
  }
  getchar();
}
//==================================================
//Función para la Opción 1: Registrar libro.
//==================================================
void registrarLibro(List *lista){
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];
  char generoAux[MAXCHAR51];
  char ISBNAux[MAXCHAR21];
  char ubicacionAux[MAXCHAR51];
  
  printf("Ingrese título del libro: ");
  leer51(tituloAux);

  printf("Ingrese autor del libro: ");
  leer51(autorAux);

  printf("Ingrese género del libro: ");
  leer51(generoAux);

  printf("Ingrese ISBN del libro: ");
  leer21(ISBNAux);

  printf("Ingrese ubicación del libro: ");
  leer51(ubicacionAux);

  
  Libro *aux = (Libro *)malloc(sizeof(Libro));
  strcpy(aux->titulo, tituloAux);
  strcpy(aux->autor, autorAux);
  strcpy(aux->genero, generoAux);
  strcpy(aux->ISBN, ISBNAux);
  strcpy(aux->ubicacion, ubicacionAux);
  strcpy(aux->estado, "Disponible");
  aux->reservas = createList();

  pushFront(lista, aux);
  printf("\n¡El libro se añadió a la biblioteca!\n");
  printf("Operación Finalizada.\n\n");
}
//==================================================
//Función para la Opción 2: Mostrar datos de libro.
//==================================================
void mostrarDatosLibro(List *lista) {
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];

  printf("Ingrese título del libro: ");
  leer51(tituloAux);

  printf("Ingrese autor del libro: ");
  leer51(autorAux);

  Libro *aux = firstList(lista);
  while (aux != NULL) {
    if (strcmp(tituloAux,aux->titulo) == 0 && strcmp(autorAux,aux->autor) == 0)
    {
      printf("\n------------------------------------------\n");
      printf("         Datos del libro '%s'\n", aux->titulo);
      printf("------------------------------------------\n\n");
      printf("Título: %s\n", aux-> titulo);
      printf("Autor: %s\n", aux-> autor);
      printf("Género: %s\n", aux-> genero);
      printf("ISBN: %s\n", aux-> ISBN);
      printf("Ubicación: %s\n", aux-> ubicacion);

      if (strcmp(aux-> estado, "Disponible") != 0) 
      {
        printf("Estado: %s\n", aux-> estado);
        char *nodoReservas = firstList(aux-> reservas);
        printf("Reservado por:");

        while (nodoReservas != NULL) 
        {
          //char *reserva = nodoReservas->data;
          printf(" %s", nodoReservas);
          nodoReservas = nextList(aux-> reservas);
          if (nodoReservas != NULL) 
          {
            printf(",");
          }
        }
          
        printf("\n");
      } 
      else 
      {
        printf("Estado: Disponible\n");
      }
      printf("\n");
      return;
      }
    
      aux = nextList(lista);
  }
  
    printf("\nEl libro no está en biblioteca :(\n");
    printf("Fin de la operación.\n\n");
}
//==================================================
// Función para la Opción 3: Mostrar todos los libros.
//==================================================
void mostrarLibros(List *lista) {
  Libro *aux = (Libro *)firstList(lista);
  if (aux == NULL) {
      printf("\nNo existen libros en la biblioteca!\n\n");
      return;
  }

    printf("================================================\n");
    printf("              Libros en la Biblioteca\n");
    printf("================================================\n");

    printf("      Título                            Autor\n");
    printf("--------------------------------------------------\n\n");

    while (aux != NULL) {
      printf("%-36s%-36s\n", aux->titulo, aux->autor);
      aux = (Libro *)nextList(lista);
    }
    printf("\n");
}
//==================================================
// Función opción 4 para reservar libro
//==================================================
void reservarLibro(List *lista) {
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];

  printf("Ingrese título del libro: ");
  leer51(tituloAux);

  printf("Ingrese autor del libro: ");
  leer51(autorAux);

  Libro *aux = firstList(lista);
  while (aux != NULL) 
  {
    if (strcmp(tituloAux,aux->titulo) == 0 && strcmp(autorAux,aux->autor) == 0) 
    {
      char estudiante[MAXCHAR51];
      printf("Ingrese nombre del estudiante: ");
      leer51(estudiante);
      pushBack(aux->reservas, strdup(estudiante));
      strcpy(aux->estado, "Reservado");
      printf("\nEl libro se reservó con éxito a %s!\n\n",estudiante);
      return;
    }

    aux = nextList(lista);
  }
  
  printf("\nNo encontramos el libro!.\n");
  printf("Operación Finalizada.\n\n");
}
//==================================================
// Función opción 5 para cancelar la reserva de un libro
//==================================================
void cancelarReservaLibro(List *lista) {
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];
  char estudianteAux[MAXCHAR51];

  printf("Ingrese título del libro: ");
  leer51(tituloAux);

  printf("Ingrese autor del libro: ");
  leer51(autorAux);

  printf("Ingrese nombre del estudiante que desea cancelar la reserva: ");
  leer51(estudianteAux);

  Node *nodoLibro = firstList(lista);

  while (nodoLibro != NULL) 
  {
    Libro *libro = nodoLibro->data;
    if (strcmp(tituloAux,libro->titulo) == 0 && strcmp(autorAux,libro->autor) == 0) 
    {
      Node *nodoReservas = firstList(libro->reservas);

      while (nodoReservas != NULL)
      {
        char *reserva = nodoReservas->data;

        if (strcmp(estudianteAux, reserva) == 0) 
        {
          printf("\nReserva cancelada con éxito para %s.\n\n", estudianteAux);
          popCurrent(libro->reservas);

          Node *aux = firstList(libro->reservas);
          if (aux == NULL) {
            strcpy(libro->estado, "Disponible");
          }
          return;
        }

        nodoReservas = nodoReservas->next;
      }
      
      printf("\nEl estudiante no tiene una reserva para este libro.\n\n");
      return;
    }

    nodoLibro = nodoLibro->next;
  }
  
  printf("\nEl libro no se encuentra en la biblioteca.\n");
  printf("Operación Finalizada.\n\n");
}
//==================================================
//Función para retirar libro si está disponible
//==================================================
void retirarLibro(List *lista) {
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];
  char estudianteAux[MAXCHAR51];

  printf("Ingrese título del libro: ");
  leer51(tituloAux);

  printf("Ingrese autor del libro: ");
  leer51(autorAux);

  printf("Ingrese su nombre para retirar el libro: ");
  leer51(estudianteAux);

  Node *nodoLibro = (Node *)firstList(lista);

  while (nodoLibro != NULL) 
  {
    Libro *libro = (Libro *)nodoLibro->data;

    if (strcmp(tituloAux,libro->titulo) == 0 && strcmp(autorAux,libro->autor) == 0)
    {
      
      if (strcmp(libro->estado, "Disponible") == 0) 
      {
        strcpy(libro->estado, "Prestado");
        printf("\nLibro \"%s\" de \"%s\" ha sido retirado por %s.\n\n",
        libro->titulo, libro->autor, estudianteAux);
        return;
      } else if (strcmp(libro->estado, "Reservado") == 0) {
        Node *nodoReservas = (Node *)firstList(libro->reservas);

        if (nodoReservas != NULL && strcmp(estudianteAux, (char *)nodoReservas->data) == 0)
        {
          popFront(libro->reservas);
          strcpy(libro->estado, "Prestado");
          printf("\nLibro \"%s\" de \"%s\" ha sido retirado por %s.\n\n",
          libro->titulo, libro->autor, estudianteAux);
          return;
        }
        
      }
      
      printf("\nEl libro no puede ser retirado en este momento.\n\n");
      return;
    }

    nodoLibro = (Node *)nodoLibro->next;
  }
  
  printf("\nEl libro no se encuentra en la biblioteca.\n");
  printf("Operación Finalizada.\n\n");
}
//==================================================
// Función opción 7 para devolver un libro
//==================================================
void devolverLibro(List *lista) {
  getchar();
  char tituloAux[MAXCHAR51];
  char autorAux[MAXCHAR51];

  printf("Ingrese el título del libro: ");
  leer51(tituloAux);

  printf("Ingrese el autor del libro: ");
  leer51(autorAux);

  Node *nodoLibro = (Node *)firstList(lista);

  while (nodoLibro != NULL) {
    Libro *libro = (Libro *)nodoLibro->data;

    if (strcmp(tituloAux, libro->titulo) == 0 &&
      strcmp(autorAux, libro->autor) == 0) {
      if (strcmp(libro->estado, "Disponible") == 0) {
      printf("\nEl libro \"%s\" de \"%s\" ya está disponible.\n\n",libro->titulo, libro->autor);
      } else if (strcmp(libro->estado, "Reservado") == 0) {
        strcpy(libro->estado, "Disponible");
        printf("\nLibro \"%s\" de \"%s\" ha sido devuelto.\n\n", libro->titulo,libro->autor);
        }
        return; // Salir una vez que se ha encontrado el libro.
    }

    nodoLibro = (Node *)nodoLibro->next;
  }

  printf("\nEl libro no está en la biblioteca o los datos ingresados son incorrectos.\n\n");
}

//==================================================
// Función opción 8 para mostrar libros prestados
//==================================================
void mostrarLibrosPrestados(List *lista) {
  Node *nodoLibro = (Node *)firstList(lista);
  int prestados = 0;

  printf("\n------------------------------------------\n");
  printf("              Libros Prestados              \n");
  printf("------------------------------------------\n");

  while (nodoLibro != NULL) {
    Libro *libro = (Libro *)nodoLibro->data;

    if (strcmp(libro->estado, "Prestado") == 0) {
      printf("Título: %-30s Autor: %-20s Estudiante: ", libro->titulo,
      libro->autor);

      Node *nodoReservas = (Node *)firstList(libro->reservas);

      while (nodoReservas != NULL) {
        char *reserva = (char *)nodoReservas->data;
        printf("%s", reserva);
        nodoReservas = (Node *)nodoReservas->next;
        if (nodoReservas != NULL) {
          printf(", ");
        }
      }

      printf("\n");
      prestados++;
    }

    nodoLibro = (Node *)nodoLibro->next;
  }

  if (prestados == 0) {
    printf("No hay libros prestados.\n");
  }

  printf("\n");
}

// Función para extraer un campo específico de una línea de texto en formato CSV 
const char *get_csv_field (char * tmp, int k) {
  int open_mark = 0;
  char* ret=(char*) malloc (100*sizeof(char));
  int ini_i=0, i=0;
  int j=0;
  while(tmp[i+1]!='\0'){

    if(tmp[i]== '\"'){
      open_mark = 1-open_mark;
      if(open_mark) ini_i = i+1;
        i++;
        continue;
      }

    if(open_mark || tmp[i]!= ','){
      if(k==j) ret[i-ini_i] = tmp[i];
        i++;
        continue;
      }

      if(tmp[i]== ','){
        if(k==j) {
          ret[i-ini_i] = 0;
          return ret;
        }
        j++; ini_i = i+1;
      }
      i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }
    return NULL;
}
//==================================================
// Función opción 9 para importar libros desde archivo CSV
//==================================================
void importarLibrosCSV(List *lista) {
  char nombreArchivo[100];

  printf("Ingrese el nombre del archivo en formato .csv: ");
  scanf("%s", nombreArchivo);

  FILE *archivo = fopen(nombreArchivo, "r");

  if (!archivo) {
    printf("Error: no se pudo abrir el archivo\n");
    return;
  }

  char linea[1024];
  fgets(linea, sizeof(linea), archivo); // Lee la primera línea (encabezado) y la descarta

  // Almacena cada línea del archivo csv 
  while (fgets(linea, sizeof(linea), archivo) != NULL) {
    Libro *libroN = (Libro *)malloc(sizeof(Libro));
    libroN->reservas = createList();

  // Utiliza la función get_csv_field para obtener los campos del CSV
    strcpy(libroN->titulo, get_csv_field(linea, 0));
    strcpy(libroN->autor, get_csv_field(linea, 1));
    strcpy(libroN->genero, get_csv_field(linea, 2));
    strcpy(libroN->ISBN, get_csv_field(linea, 3));
    strcpy(libroN->ubicacion, get_csv_field(linea, 4));
    strcpy(libroN->estado, get_csv_field(linea, 5));
          
    char *reservas = get_csv_field(linea, 6);
    char *token = strtok(reservas, ",");
    while (token != NULL) {
      pushBack(libroN->reservas, strdup(token));
      token = strtok(NULL, ",");
    }

    pushFront(lista, libroN);
  }

  fclose(archivo);
  printf("Los libros se han importado correctamente desde el archivo %s.\n\n", nombreArchivo);
}

//==================================================
// Función para exportar nuestros libros a archivo csv
//==================================================
void exportarLibrosACSV(List *lista, const char *nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "w");
  if (archivo == NULL) {
    printf("\nNo se pudo abrir el archivo %s para exportar libros.\n\n", nombreArchivo);
    return;
  }

  Node *nodoLibro = (Node *)firstList(lista);

  while (nodoLibro != NULL) {
    Libro *libro = (Libro *)nodoLibro->data;
    fprintf(archivo, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", libro->titulo, libro->autor, libro->genero, libro->ISBN, libro->ubicacion);
    nodoLibro = (Node *)nodoLibro->next;
  }

    
  printf("\nLos libros se han exportado correctamente al archivo %s.\n\n", nombreArchivo);
  fclose(archivo);

}