//**********************LABORATORIO 3 ***********************
// Autores: Matías Cortés - Ignacio Villarroel.
// Profesor: Cristián Sepulveda.
// Asignatura: Algoritmos Avanzados.

// Descripción: Este programa se encarga de encontrar la cantidad óptima
// utilizando la metodología de Backtracking.

// Librerías a incluirse
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

//Se crea la figura STRUCT que contendrá los valores provenientes del archivo
typedef struct valoresElementales {
    int * Vi; //Array de enteros de los valores
    int * Pi; //Array de enteros de las ponderaciones
    int elementos; // elementos que se irán guardando
}valoresElementales;

//Se crea la figura STRUCT que contendrá las condiciones que hace que el STRUCT anterior deba cumplir
typedef struct Arreglo {
    int * indices; // Array de indices para las ponderaciones.
    int pmax; // Entero de número de ponderado máximo.
    int valor; // Acumulador que mantendrá la suma de los elementos.
    int ponderacion; // Entero ponderado a comparar.
}Arreglo;

//FUNCIONES

int ramificacion_acotamiento(char *);
void obtenerDatos(char *, int *, int *);
int maximaSuma(valoresElementales *, int, int);
void crearArreglo(valoresElementales *, char *, int);
Arreglo * crearStruct(int, int);
void sumarCamino(valoresElementales *, Arreglo *, int, int,Arreglo *);
void siguienteCamino(Arreglo *, Arreglo *, int);
void add(Arreglo *, int, valoresElementales *,int);
void delete(Arreglo *, int, valoresElementales *, int);
int existencia(Arreglo *, int, int);
valoresElementales * pasarDatos(int);
void mostrarValordeCamino(valoresElementales * );
void mostrarCamino(Arreglo * ,int );

// DESCRIPCIÓN: Se añade al array un posible candidato y
// también añade la ponderación y valor correspondiente a lo que se lleva hasta
// ese momento.
// ENTRADA: array + int + array + int.
// SALIDA: vacío (void).

void add(Arreglo * Base,int i, valoresElementales * Datos,int n) {
    for (int j = 0; j < n; j++) {
        if(Base->indices[j]==-1) {
            Base->indices[j] = i;
            Base->valor = Base->valor + Datos->Vi[i];
            Base->ponderacion = Base->ponderacion + Datos->Pi[i];
            return;
        }
    }
}

// DESCRIPCIÓN: Elimina del arreglo Base el indice del posible candidato.
// ENTRADA: array + int + array + int.
// SALIDA: vacío (void).

void delete(Arreglo * Base,int i, valoresElementales * Datos,int n) {
    for (int j = 0; j < n; j++) {
        //Se recorre hasta llegar al indice
        if(Base->indices[j]==i) {
            Base->indices[j] = -1; //No hay indices -1
            Base->valor = Base->valor - Datos->Vi[i];
            Base->ponderacion = Base->ponderacion - Datos->Pi[i];
            return;
        }
    }
}

// DESCRIPCIÓN: Función que se serciora si existencia el índice para la ponderación.
// ENTRADA: array + int + int.
// SALIDA: Boolean (0 , 1).

int existencia(Arreglo * Base,int i, int n) {
    for (int j = 0; j < n; j++) {
        if(Base->indices[j]==i) {
            return 1;
        }
    }
    return 0;
}

// DESCRIPCIÓN: Verifica si el dato que se obtiene es el óptimo o no.
// ENTRADA: array + array.
// SALIDA: vacío (void).

void siguienteCamino(Arreglo * Base,Arreglo * Solucion,int n) {
    // En caso que sea una mejor solucion
    if(Base->valor > Solucion->valor) {
        Solucion->valor = Base->valor;
        Solucion->ponderacion = Base->ponderacion;
        for (int i = 0; i < n; i++) {
            Solucion->indices[i] = Base->indices[i];
        }
    }
}
// DESCRIPCIÓN: Se implementa la metodología backtracking, crea ramifificaciones para encontrar la solución hasta llegar al óptimo.
// ENTRADA: array + array + int + int + int + array.
// SALIDA: vacío (void).

void sumarCamino(valoresElementales * Datos, Arreglo * Base, int n,int lleno,Arreglo * Solucion) {
    if(lleno) {
        siguienteCamino(Base,Solucion,n);
    }
    else {
        for (int i = 0; i < n; i++) {
            if(existencia(Base,i,n)==0) {
                if(Base->pmax >= Base->ponderacion + Datos->Pi[i]) {
                    add(Base,i,Datos,n);
                    sumarCamino(Datos,Base,n,0,Solucion);
                    delete(Base,i,Datos,n);
                }
                else {
                    //Se ve si es un posible candidato a mejorar
                    sumarCamino(Datos,Base,n,1,Solucion);
                }
            }
        }
    }
}

// DESCRIPCIÓN: Llena el STRUCT con los datos necesarios para realizar el Backtracking.
// ENTRADA: int + int.
// SALIDA: STRUCT.

Arreglo * crearStruct(int n, int pmax) {
    Arreglo * aux = (Arreglo *)malloc(sizeof(Arreglo));
    aux->indices = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        aux->indices[i]  = -1;
    }
    aux->pmax = pmax;
    aux->valor = 0;
    aux->ponderacion = 0;
    return aux;
}

// DESCRIPCIÓN: Obtiene la máxima suma de valores que cumpla con una ponderación dada.
// ENTRADA: array + int + int.
// SALIDA: array

int maximaSuma(valoresElementales * Datos,int n,int pmax){
    Arreglo * Base = crearStruct(n,pmax);
    Arreglo * Solucion = crearStruct(n,pmax);
    sumarCamino(Datos,Base,n,0,Solucion);
    return Solucion->valor;
}

// DESCRIPCIÓN: Obtiene los datos por columna y los almacena para ser pasados al STRUCT
// ENTRADA: array + string + int
// SALIDA: vacío (void)

void crearArreglo(valoresElementales * Datos, char * name_file, int n) {
    FILE * file;
    int v,p;
    file = fopen(name_file,"r");

    for(int i = 0; i < n; i++) {
        fscanf(file,"%d %d",&v,&p);
        Datos->Vi[i] = v;
        Datos->Pi[i] = p;
    }
}

// DESCRIPCIÓN: Obtiene el almacenamiento para los STRUCT
// ENTRADA: int.
// SALIDA: array.

valoresElementales * pasarDatos(int n){
    valoresElementales * aux = (valoresElementales*)malloc(sizeof(valoresElementales));
    aux->elementos = n;
    aux->Pi = (int*)malloc(sizeof(int)*n);
    aux->Vi = (int*)malloc(sizeof(int)*n);
    return aux;
}

// DESCRIPCIÓN: Obtiene los datos del archivo ponderación máxima y número de filas por medio de su nombre.
// ENTRADA: array + int + int.
// SALIDA: void (vacío)

void obtenerDatos(char * name_file, int * pmax, int * n) {
    int contador = 0;
    char delimitador[] = "_", terminacion[] = ".txt";
    char *data = (char*)malloc(sizeof(char)*40);
    data = strtok(name_file,delimitador);
    while(data != NULL) {
    if (contador == 2) {
      * n = (int)atoi(data);
    }
    if(contador == 3) {
      * pmax = (int)atoi(strtok(data,terminacion));
    }
    data = strtok(NULL,delimitador);
    contador++;
  }
}

// DESCRIPCIÓN: Muestra el arreglo por panntalla.
// ENTRADA: array + int
// SALIDA: vacío(void)

void mostrarCamino(Arreglo * A,int n) {
    printf("-Arreglo-\n");
    printf("Valor: %d\nPonderacion: %d\n",A->valor,A->ponderacion);
    for(int i = 0;i<n;i++ ) {
        printf("%d ",A->indices[i]);
    }
    printf("\n");
}

// DESCRIPCIÓN: Muestra por pantalla el contenido de esta estructura
// ENTRADA: STRUCT
// SALIDA: vacío(void)

void mostrarValordeCamino(valoresElementales * Datos) {
    printf("Valores y Ponderaciones\n");
    for(int i = 0; i<Datos->elementos;i++) {
        printf("%d - %d \n",Datos->Vi[i],Datos->Pi[i]);
    }
}

// DESCRIPCIÓN: Función principal del archivo que se encarga de realizar los llamados para resolver el problema.
// ENTRADA: string.
// SALIDA: string.

int ramificacion_acotamiento(char * name_file){
    FILE * file;
    file = fopen(name_file,"r");
    if(file == NULL){
        printf("ERROR: NO HAY ARCHIVO \n");
        return -1;
    }
    int n = 0, pmax = 0;
    char * aux_name_file =(char*)malloc(sizeof(char)*(strlen(name_file)+1));
    strcpy(aux_name_file,name_file);
    obtenerDatos(aux_name_file,&pmax,&n);
    valoresElementales * Datos = pasarDatos(n);
    crearArreglo(Datos,name_file,n);
    fclose(file);
    int resultado = maximaSuma(Datos,n,pmax);
    free(Datos);
    return resultado;
}

//Menu Principal acá se implementará el menu principal
int main(int argc, char *argv[])
{
    //Ejecucion del problema 1 
    clock_t cini, cfin;
    cini=clock();
    int resultado = ramificacion_acotamiento(argv[1]);
    printf("Resultado: %d\n",resultado);
    cfin=clock();
    printf("Tiempo de ejecucion:  %f \n",(double)(cfin-cini)/CLOCKS_PER_SEC);
    //----------------------------------------------------------------------------
    return 0;

}