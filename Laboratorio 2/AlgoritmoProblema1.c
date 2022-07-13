/*--------LABORATORIO 2 --------- */
// METODOLOGIA: GREDDY
// OBJETIVO: El objetivo de este archivo es definir todas las funciones
//           que solucionan el problema 1, utilizando una metodologia greddy o goloso
// AUTORES: Matias Cortes - Ignacio Vllarroel
// RAMO: Algoritmos Avanzados
// PROFESOR: Cristián Sepulveda
/*-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //Tiempo de ejecucion

//FUNCIONES A IMPLEMENTAR
int programa_P1(char * name_file);
void obtenerDatos(char * name_file, int * pmax, int * n);
void crearArray(int * Val, int * Pond, char * name_file, int n);
int goloso(int * Val,int * Pond,int pmax,int n);
void mergesort(float * indices,int * Val,int *Pond,int final, int inicio);
void ordenamiento(float * indices,int * Val,int * Pond, int final, int mitad, int inicio);

//DESCRIPCION: El algoritmo realiza el ordenamiento de  mergesort
//DOMINIO: array + array + array + int + int + int
//RECORRIDO: Vacío (void)

void ordenamiento(float * indices,int *Val,int * Pond, int final, int mitad, int inicio){
    //Contadores y variables a usar para crear las particiones
    int i, j, k;
    int izquierda = mitad - final + 1;
    int derecha = inicio - mitad;

    // Se hace una copia de cada array a ordenar para el ambos lados indices
    float lado_i1[izquierda], lado_d1[derecha];
    //valores
    int lado_i2[izquierda], lado_d2[derecha];
    //ponderaciones
    int lado_i3[izquierda], lado_d3[derecha];

    //Se coPonda el contenido de estas 2 partes
    for (i = 0; i < izquierda; i++){
        lado_i1[i] = indices[final + i];
        lado_i2[i] = Val[final + i];
        lado_i3[i] = Pond[final + i];
    }
    for (j = 0; j < derecha; j++){
        lado_d1[j] = indices[mitad + 1 + j];
        lado_d2[j] = Val[mitad + 1 + j];
        lado_d3[j] = Pond[mitad + 1 + j];
    }

    //Se inicia el ordenamiento
    i = 0;
    j = 0;
    k = final;
    while (i < izquierda && j < derecha) {
        //Si las razones izquierda<=derecha (indices) entonces se agrega el valor
        //del lado izquierdo y afecta a todos los arreglos restantes
        if (lado_i1[i] >= lado_d1[j]) {
            indices[k] = lado_i1[i];
            Val[k] = lado_i2[i];
            Pond[k] = lado_i3[i];
            i++;
        }
        else { //Sino se agrega el valor del lado derecho
            indices[k] = lado_d1[j];
            Val[k] = lado_d2[j];
            Pond[k] = lado_d3[j];
            j++;
        }
        k++;
    }
    // si quedan elementos del lado izquierdauierdo se coPondan
    while (i < izquierda) {
        indices[k] = lado_i1[i];
        Val[k] = lado_i2[i];
        Pond[k] = lado_i3[i];
        i++;
        k++;
    }
    //si quedan elementos del lado derecho se coPondan
    while (j < derecha) {
        indices[k] = lado_d1[j];
        Val[k] = lado_d2[j];
        Pond[k] = lado_d3[j];
        j++;
        k++;
    }
}

//DESCRIPCIÓN: Es la baso del algoritmos ordenamiento-Sort ordenándolo mediente los índices
// para ordenar los cambios, luego estos se
// harían en los dos arreglos restantes para mantener los índices correlativos de
// cada arreglo
//DOMINIO: array + array + array + array + int
//RECORRIDO: Vacío (void)

void mergesort(float * indices, int * Val,int * Pond,int final, int inicio){
    if (final < inicio) {
        int mitad = final + (inicio - final) / 2;
        //Permutación que va dividiendo la solución por la mitad
        mergesort(indices,Val,Pond, final, mitad);
        mergesort(indices,Val,Pond, mitad + 1, inicio);
        //se realiza el ordenamiento
        ordenamiento(indices,Val,Pond, final, mitad, inicio);
    }
}

//DESCRIPCION:Resuelve el problema de la mochila con la implementacion greddy o goloso.
//DOMINIO:arreglo + array + int + int
//RECORRIDO: int

int goloso(int * Val,int * Pond,int pmax,int n){

    // variables para calcular Val/Pond
    int valor = 0, ponderacion = 0;
    float * indices = (float*)malloc(sizeof(float)*n);

    // se calcula valor/ponderacion entre ambos arreglos de DOMINIO y se
    // guardan los resultados en el arreglo indices
    for(int i = 0; i<n; i++){
        float valor = (float)Val[i];
        float ponderacion = (float)Pond[i];
        indices[i] = valor/ponderacion;
    }

    // se ordenan todos los arreglos de mayor a menor con mergesort
    mergesort(indices,Val,Pond,0,n-1);

    int pondTotal = 0; // ponderacion total
    int * canditados = (int *)calloc(n,sizeof(int)); // arreglo de puros ceros

    int k = 0; // contador para el while

    // mientras la ponderacion lograda no supere la maxima
    while(k <= n && pondTotal < pmax){
        // si se puede agregar otra ponderacion sin superar la maxima
        if(pondTotal + Pond[k] <= pmax){
            // se agrega un valor al arreglo de candidatos para la solucion
            canditados[k] = Val[k];
            // se actualiza la ponderacion total
            pondTotal = pondTotal + Pond[k];
        }
        k++;
    }

    int maxSum = 0; //variable que contendrá la solución

    // se recorre el arreglo con los canditos, calculando la suma entre sus valores
    for(int i = 0; i<n; i++){
        maxSum = maxSum + canditados[i];
    }

    // se retorna la maxima suma
    return maxSum;
}

//DESCRIPCION: Almacena el valor de: Val(primer columanda del archivo) y Pond(segunda columna del archivo)
//DOMINIO: array + array + string + int
//RECORRIDO: Vacío (void)

void crearArray(int * Val, int * Pond, char * name_file, int n){
    FILE * file;
    int v,p;
    //se abre el archivo para lectura
    file = fopen(name_file,"r");
    //se recorren las filas del archivo
    for(int i = 0; i < n; i++) {
        fscanf(file,"%d %d",&v,&p);
        //se guarda el primer valor de la fila
        Val[i] = v;
        //se guarda el segundo valor de la fila
        Pond[i] = p;
    }
}

//DOMINIO: Cadena del nombre del archivo, variable de ponderación máxima, variable de cantidad de filas
//DESCRIPCION: char + int + int
//RECORRIDO: Ninguna

void obtenerDatos(char * name_file, int * pmax, int * n){
    int contador = 0;
    char delimitador[] = "_", terminacion[] = ".txt";
    char *data = (char*)malloc(sizeof(char)*40);
    data = strtok(name_file,delimitador);

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

//DESCRIPCION: Funcion principal del archivo que se encarga de realizar los llamados para resolver el problema
//DOMINIO: Archivo
//RECORRIDO: Retorna el resultado obtenido por el algoritmo ejecutad

int programa_P1(char * name_file){
    FILE * file;
    file = fopen(name_file,"r");  //se abre el archivo para lectura
    if(file == NULL) //si el archivo no existe
    {
        printf("ERROR: NO HAY ARCHIVO \n");
        return -1;
    }
    int n = 0, pmax = 0;
    char * aux_name_file = (char*)malloc(sizeof(char)*(strlen(name_file)+1));
    strcpy(aux_name_file,name_file);
    obtenerDatos(aux_name_file,&pmax,&n);

    int * Val = (int*)malloc(sizeof(int)*n);
    int * Pond = (int*)malloc(sizeof(int)*n);

    crearArray(Val,Pond,name_file,n);
    fclose(file);
    int resultado = goloso(Val,Pond,pmax,n);
    free(Val);
    free(Pond);
    return resultado;
}

// FUNCIÓN MAIN
int main(int argc, char *argv[]){
    clock_t cini, cfin;
    cini=clock();
    int resultado = programa_P1(argv[1]);
    printf("Resultado: %d\n",resultado);
    cfin=clock();
    printf("Tiempo de ejecucion:  %f \n",(double)(cfin-cini)/CLOCKS_PER_SEC);
    return 0;
  }
