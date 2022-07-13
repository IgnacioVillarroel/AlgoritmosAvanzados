/*--------LABORATORIO 2 --------- */
// METODOLOGIA: GREDDY
// OBJETIVO: El objetivo de este archivo es definir todas las funciones
//           que solucionan el problema 2, utilizando una metodologia greddy o goloso
// AUTORES: Matias Cortes - Ignacio Villarroel
// RAMO: Algoritmos Avanzados
// PROFESOR: Cristián Sepulveda
/*---------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h> //Tiempo de ejecucion


//FUNCIONES A UTILIZAR
int recorridoCamino(int ** matriz,int * desplazamiento,int n);
int caminoMinimo(int * fila,int * nodoPasado, int n);
int caminoCompleto(int * nodoPasado,int n);
int caminoCorto(int ** matriz,int n);
int goloso (int **matriz,int n);
int ** crearMatriz(char * name_file,int n);
void obtenerDatos(char * name_file, int * resultado, int * n);
int obtenerArchivo(char * name_file);

//DESCRIPCIÓN: Se obtiene la suma del camino a partir de recorrer el
// conjunto solución de la matriz M, al terminar de recorrer se añade la
// suma del punto de origen del conjunto solución
//DOMINIO: matriz + array + int
//RECORRIDO: int

int recorridoCamino(int ** matriz,int * desplazamiento,int n)
{
    int suma = 0;
    for(int i = 0; i<n; i++)
    {
        if(i+1 < n)
        {
            int x = desplazamiento[i];
            int y = desplazamiento[i+1];
            suma = suma + matriz[x][y];
        }
    }
    suma = suma + matriz[desplazamiento[n-1]][desplazamiento[0]];
    return suma;
}

//DESCRIPCION: Se obtiene el mínimo valor de este arreglo, que
// representa el destino siguiente para nuestro camino, dado que tiene el
// camino más óptimo para nosotros
//DOMINIO: array + array + array
//RECORRIDO: int

int caminoMinimo(int * fila,int * nodoPasado, int n)
{
    int minimo = INT_MAX, pos_min = 0;
    for(int i = 0; i<n; i++) //se recorre el arreglo
    {
        if(fila[i]!=-1 && fila[i]<minimo && nodoPasado[i]==0) //si la posicion es menor que el minimo y se ha visitado
        {
            minimo = fila[i]; //se agrega como el minimo
            pos_min = i;
        }
    }
    return pos_min;
}

//DESCRIPCION: Se verifica que si todos arreglos son nodoPasado, es decir,
// todos los valores de este arreglo posean un valor booleano verdadero,
// si no es así se obtendrá lo contrario
//DOMINIO: Arreglo + entero
//RECORRIDO: Bool (T or F)

int caminoCompleto(int * nodoPasado,int n) {
  //Se recorre el arreglo
    for(int i = 0; i<n; i++) {
        //Se ve si se ha visitado
        if(nodoPasado[i] == 0) {
            return 0;
        }
    }
    return 1;
}

//DESCRIPCIÓN: Se obtiene el VALOR MÍNIMO de esta matriz, que representa
// el origen  para nuestro camino, dado que tiene el camino más óptimo
// para empezar ya que son los más pequeños.
//DOMINIO: Matriz + entero
//RECORRIDO: int (posición)

int caminoCorto(int ** matriz,int n) {
    int fila_min = INT_MAX, fila_pos = 0;
    for(int i = 0; i<n; i++) {
        int suma = 0;
        //se recorre la matriz
        for(int j = 0; j<n; j++) {
          //si el elemento es distinto de -1
            if(matriz[i][j] != -1) {
                //se agrega el valor a la suma
                suma = suma + matriz[i][j];
            }
        }
        if(suma<fila_min) {
            fila_min = suma;
            fila_pos = i;
        }
    }
    return fila_pos;
}

//DESCRIPCION: Algoritmo que por medio de metodología goloso o greddy,
// obtiene la suma del mejor camino dado una matriz, encontrando el mejor
// camino.
//DOMINIO: matriz + int
//RECORRIDO: int

int goloso(int **matriz,int n) {
    //Se determina el origen
    int origen = caminoCorto(matriz,n);
    int resultado = 0, contador = 0;
    int * nodoPasado = (int *)calloc(n,sizeof(int));
    int * desplazamiento = (int *)calloc(n,sizeof(int));
    nodoPasado[origen] = 1;
    desplazamiento[contador] = origen;
    contador++;
    while(caminoCompleto(nodoPasado,n) == 0) {
        int pos_min = caminoMinimo(matriz[origen],nodoPasado,n);
        desplazamiento[contador] = pos_min;
        nodoPasado[pos_min] = 1;
        origen = pos_min;
        contador++;
    }
    resultado = recorridoCamino(matriz,desplazamiento,n);
    return resultado;
}

//DESCRIPCION: A partir de la información crea una matriz (estilo mapa).
//DOMINIO: char + int
//RECORRIDO: matriz

int ** crearMatriz(char * name_file,int n)
{
  FILE * file_matriz;
  int a;
  //se abre el archivo para lectura
  file_matriz = fopen(name_file,"r");
  //se asigna memoria para la matriz
  int **matriz = (int**)malloc(sizeof(int*)*n);
  //se recorre la fila
  for(int fila = 0; fila < n; fila++) {
    //se asigna memoria para las filas de la matriz
    matriz[fila] = (int*)malloc(sizeof(int)*n);
    //se recorren las columnas de la matriz
    for(int columna = 0; columna < n; columna++) {
      //se obtienen los valores del archivo
      fscanf(file_matriz,"%d",&a);
      //se asigna el valor obtenido a la posicion
      matriz[fila][columna] = a;
    }
  }
  return matriz;
}

//DESCRIPCION: Obtiene los datos del archivo, siendo la dimension de la matriz y el resultado esperado
//DOMINIO: char + int + int
//RECORRIDO: Vacío (void)

void obtenerDatos(char * name_file, int * resultado, int * n) {
  int contador = 0;
  char limite[] = "_",finish[] = ".txt";
  char * data = (char*)malloc(sizeof(char)*20);
  data = strtok(name_file,limite);
  while(data != NULL) {
    if (contador == 1) {
      * n = (int)atoi(data);
    }
    if(contador == 2) {
      * resultado = (int)atoi(strtok(data,finish));
    }
    data = strtok(NULL,limite);
    contador++;
  }
}

//DESCRIPCION: Funcion del archivo que los llama para resolver la problemática
//DOMINIO: Char Archivo
//RECORRIDO: int

int obtenerArchivo(char * name_file){
    FILE * file_matriz;
    //se abre la matriz para lectura
    file_matriz = fopen(name_file,"r");
    //si el archivo no existe
    if(file_matriz == NULL ) {
        printf("ERROR: NO HAY ARCHIVO \n");
        return -1;
    }

    int resultado = 0, resultado_final = 0, n = 0;
    char * aux_name_file = (char*)malloc(sizeof(char)*(strlen(name_file)+1)); //se asignas espacio para un archivo auxiliar
    strcpy(aux_name_file,name_file); //se copia un archivo auxiliar
    obtenerDatos(aux_name_file,&resultado,&n);
    int **matriz = crearMatriz(name_file,n);
    fclose(file_matriz);
    resultado_final = goloso(matriz,n);
     //se libera espacio
    for(int i = 0; i<n; i++){
        free(matriz[i]);
    }
    //Se libre la memoria
    free(matriz);
    return resultado_final;
}

// FUNCIÓN MAIN
int main(int argc, char *argv[]){
    clock_t cini,cfin;
    cini = clock();
    int resultado = obtenerArchivo(argv[1]);
    printf("Resultado: %d\n",resultado);
    cfin = clock();
    printf("Tiempo de ejecucion:  %f \n",(double)(cfin-cini)/CLOCKS_PER_SEC);
    return 0;
  }
