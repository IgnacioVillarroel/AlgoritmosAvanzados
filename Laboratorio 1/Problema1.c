#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ######################## PROBLEMA 1 ########################
// Autores: Matías Cortés - Ignacio Villarroel
// Asignatura: Algoritmos Avanzados
// ############################################################

//######################## DESCRIPCION PROGRAMA###############
// Programa que dado un archivo y una ponderación se encarga de generar todas las sumas
// posibles y luego elegir la mas cercana al número ponderado.

//#####################FUNCIONES#############################

//DESCRIPCION: Realiza las combinaciónes de posiciones y luego realiza las sumas respectivas en todas ellas
//DOMINIO: Arreglo que guardará las sumas + cantidad de combinaciones + cantidad de numeros + posición en el arreglo + posición final en el arreglo,
//        + arreglo de los valores a suma + valores de las ponderaciones + limite de ponderacion + resultado temporal
//RECORRIDO: Es una permutación, no se obtiene nada.
void busquedaMaxima (int v[], int start, int n, int k, int maxk,int *Vi,int *Pi,int *vmax, int pmax) {
        int i;
        //Si la posición está sobre la posición final
        if (k > maxk) {
                int pSuma = 0;
                for (i=1; i<=maxk; i++){
                  pSuma = pSuma + Pi[v[i]-1];
                }
                // Se ven las sumas de los valores de Valor con respecto a la Ponderacion
                if(pSuma <= pmax)
                {
                    // Se ven las sumas de los valores de Valor con respecto a la Ponderacion
                  int vSuma = 0;
                  for (i=1; i<=maxk; i++)
                  {
                    vSuma = vSuma + Vi[v[i]-1];
                  }
                  // Se comparan los valores si cumplen los específicado
                  if(vSuma>*vmax)
                  {
                    *vmax = vSuma;
                  }
                }

                return;
        }
        // Se crea la permutación (fuerza bruta) haciendo el ciclo tantas veces como combinaciones posibles.
        for (i=start; i<=n; i++) {
                v[k] = i;
                busquedaMaxima (v, i+1, n, k+1, maxk,Vi,Pi,vmax,pmax);
        }
}

// ############################################################

//DESCRIPCION: Realiza la combinaciones y las guarda.
//DOMINIO: Valores del Archivo a sumar + Valores de las ponderaciones del archivo + Ponderación solicitada + cantidad de elementos.
//RECORRIDO: Retorna el valor máximo posible

int almacenador(int * Vi, int * Pi, int pmax, int n) {
    // Se crea el arreglo para almacenar
    int X[n];
    // Se crea un límite que irá variando
    int vmax = 0;
    for(int k = 1; k<n;k++){
      //Se llama a la función que suma las combinaciones.
        busquedaMaxima (X, 1, n, 1, k,Vi,Pi,&vmax,pmax);
    }
    return vmax;
}

// ############################################################

//DESCRIPCIÓN: Funcion que ordena los datos del archivo .txt y los coloca en los arreglos Valor y Ponderacion
//DOMINIO: Numero para las cantidades de los valores del txt + Valor de las ponderaciones + Archivo.txt + Cantidad de filas.
//RECORRIDO: No retorna nada, solo ordena lo números.

void ordenador(int * Vi, int * Pi, char * name_file, int n){
     //Se llama al archivo.
    FILE * file;
    // Se crean los espaciones para los valores y ponderaciones del sub conjunto
    int v,p;
    //Se abre el archivo
    file = fopen(name_file,"r");
    // Se recorre el archivo
    for(int i = 0; i < n; i++){
        fscanf(file,"%d %d",&v,&p);
        //Se guardan los numeros.
        Vi[i] = v;
        Pi[i] = p;
    }
}

// ############################################################

//DESCRIPCION: Extrae los datos los y ve la cantidad de hileras (filas) va a tener.
//DOMINIO: Archivo.txt + Ponderación máxima + filas
//RECORRIDO: Obtiene la cantidad de filas pero no la retorna.
void extractor(char * name_file, int * pmax, int * n)
{
    int contador = 0;
    char delimitador[] = "_", terminacion[] = ".txt";
    char *data = (char*)malloc(sizeof(char)*40);
    data = strtok(name_file,delimitador);
      //Se recorre el archivo
    while(data != NULL){
    if (contador == 2){
      * n = (int)atoi(data);
    }
    if(contador == 3){
      * pmax = (int)atoi(strtok(data,terminacion));
    }
    data = strtok(NULL,delimitador);
    contador++;
  }
}

// ############################################################

//DESCRIPCION: Funcion principal del archivo que se encarga de realizar los llamados de la funciones.
//ENTRADA: El archivo.txt
//RECORRIDO: Retorna el resultado obtenido de la suma maxima
int programa_P1(char * name_file)
{
    FILE * file;
    file = fopen(name_file,"r");
    if(file == NULL)
    {
        printf("NO DOC \n");
        return -1;
    }
    int n = 0, pmax = 0;
    char * aux_name_file = (char*)malloc(sizeof(char)*(strlen(name_file)+1));
    strcpy(aux_name_file,name_file);
    // Se extraen los datos de las columnas para ordenarlas en los arreglos.
    extractor(aux_name_file,&pmax,&n);
    //Se crea el espacio para los valores (1 columna)
    int * Vi = (int*)malloc(sizeof(int)*n);
    //Se crea el espacio para las ponderaciones (2 columna)
    int * Pi = (int*)malloc(sizeof(int)*n);
    //Se llama al ordenador para que coloque los datos en los arreglos
    ordenador(Vi,Pi,name_file,n);
    fclose(file);
    //Se almacenan y se generan todas la combinaciones posibles.
    int resultado = almacenador(Vi,Pi,pmax,n);
    //Se libera la memoria
    free(Vi);
    free(Pi);
    return resultado;
}


//DESCRIPCION: Main, llama al desarrollo de todo
//DOMINIO: Archivo .txt principal.
//RECORRIDO: 0, solo ve el tiempo.
int main(int argc, char *argv[]) {
  // Se ve el tiempo.
  clock_t cini, cfin;
  cini=clock();
  int resultado = programa_P1(argv[1]);
  printf("Resultado: %d\n",resultado);
  cfin=clock();
  printf("Tiempo de ejecucion:  %f \n",(double)(cfin-cini)/CLOCKS_PER_SEC);
  return 0;
}
