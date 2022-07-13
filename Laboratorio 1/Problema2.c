#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//ENTRADA: Dos arreglos
//DESCRIPCION: Cambia y realiza la accion de swap (cambiar lo de a en b y lo de b en a)
//SALIDA: Ninguno

void swap(int *a, int *b)
{
  int aux; 
  aux = *a; //se guarda a en un auxiliar
  *a = *b; //se pone en a lo de b
  *b = aux; //se pone en b lo de aux 
}

//#####################################################################################################################

//ENTRADA: Un arreglo, un entero  y la matriz
//DESCRIPCION: Suma los pesos para obtener un camino resultante
//SALIDA: Un entero (La suma del camino dado el peso de la matriz)

int sumaC(int *camino,int n, int **matriz)
{
  int sumaCamino = 0;
  for(int i = 0; i < n; i++)
  {
    //Se busca generar todo el recorrido considerando el rango del arreglo
    if(i + 1 != n)
    {
      int x = camino[i];
      int y = camino[i+1];
      sumaCamino = sumaCamino + matriz[x][y];
    }
  }
  sumaCamino = sumaCamino + matriz[camino[n-1]][camino[0]];
  return sumaCamino;
}

//#####################################################################################################################

//ENTRADA: El camino a permutar, la matriz que sera referente para sacar los pesos, y el resultado que se espera
//DESCRIPCION: Permuta los caminos sumando los pesos para obtener le optimo
//SALIDA: Un entero que representa la suma del camino

void perm_sum(int * camino, int n,int ** matriz, int *resultado)
{
  int sumaCamino;
  int pos[n];

  for(int i = 0; i < n; ++i)
  {
    pos[i] = 0;
  }

  //Primer camino
  sumaCamino = sumaC(camino,n,matriz);

  if (sumaCamino < *resultado)
  {
    *resultado = sumaCamino;
  }

  //Comienza la permutacion moviendose hasta cumplir todos los indices
  //Es decir, por ejemplo tenemos una de 4x4, pos ira de 0 a 3 hasta completar
  //la sentecnia de i<n [0,0,0,0],[0,1,0,0],...[0,3,3,3]
  //luego ira permutando los caminos dados para realizar la suma de caminos
  int i = 0;
  while(i<n)
  {
    if(pos[i]<i)
    {
      if(i % 2 == 0)
      {
        swap(&camino[0],&camino[i]);
      }
      else
      {
        swap(&camino[pos[i]],&camino[i]);
      }

      sumaCamino = sumaC(camino,n,matriz);

      if (sumaCamino < *resultado)
      {
        *resultado = sumaCamino;
      }

      pos[i] = pos[i] + 1;
      i = 0;
    }
    else{
      pos[i] = 0;
      i = i + 1;
    }
  }
}

//#####################################################################################################################

//ENTRADA: Matriz con los caminos, un entero con la dimenson de la matriz
//DESCRIPCION: Realiza la suma del primer camino
//SALIDA: Un entero

int getValorIni(int ** matriz,int n)
{
  int ini = 0,x,y;
  for(int i = 0; i < n; i++) 
  {
    if (i + 1 != n )
    {
      ini = ini + matriz[i][i+1];
    }
  }
  ini = ini + matriz[n-1][0];
  return ini;
}

//#####################################################################################################################

//ENTRADA: Matriz con los pesos de los caminos y la dimension de la matriz
//DESCRIPCION: Obtiene la suma del camino optimo mediante una permutacion
//SALIDA: Un entero

int algoritmo(int ** matriz, int n)
{
  int resultado = getValorIni(matriz,n);
  
  int * camino = (int*)malloc(sizeof(int)*n);//Se reseva memoria para el camino

  for(int i = 0; i < n; i++) //se recorre los caminos
  {
    camino[i] = i;
  }
  
  perm_sum(camino,n,matriz,&resultado);//Se realiza la permutacion

  return resultado;
}

//#####################################################################################################################

//ENTRADA: Matriz y entero
//DESCRIPCION: Muestra la matriz
//SALIDA: 

void print_matriz(int ** matriz,int n)
{
  for(int fila = 0; fila < n; fila++)
  {
    for(int columna = 0; columna < n; columna++) //se recorren los elemenots de la matriz
    {
      printf("%d ",matriz[fila][columna]); // se printea el elemento de la matriz
    }
    printf("\n");
  }
}

//#####################################################################################################################

//ENTRADA: EL nombre del archivo, un entero(dimension de la matriz)
//DESCRIPCION: Guarda la informacion del archivo txt en la estructura de datos
//SALIDA: Matriz

int ** makeMatriz(char * name_file,int n)
{
  FILE * file_matriz;
  int a;
  file_matriz = fopen(name_file,"r"); //se abre el archivo para lectura

  int **matriz = (int**)malloc(sizeof(int*)*n); //se guarde el espacio para la matriz

  for(int fila = 0; fila < n; fila++)
  {
    matriz[fila] = (int*)malloc(sizeof(int)*n);
    for(int columna = 0; columna < n; columna++) //se recorre la matriz
    {
      fscanf(file_matriz,"%d",&a); //se lee el elemento
      matriz[fila][columna] = a; //se guarda el elemento
    }
  }
  return matriz; //se retorna la matriz
}

//#####################################################################################################################

//ENTRADA: Recibe el nombre de archivo, el resultado que se espera y la dimension de la matriz
//DESCRIPCION: Obtiene los datos del archivo
//SALIDA: 

void getData2(char * name_file, int * resultado, int * n)
{
  int contador = 0;
  char delimitador[] = "_",terminacion[] = ".txt"; //se determina el caracter especifico

  char * data = (char*)malloc(sizeof(char)*20);

  data = strtok(name_file,delimitador);

  while(data != NULL)
  {
    if (contador == 1)
    {
      * n = (int)atoi(data);
    }
    if(contador == 2)
    {
      * resultado = (int)atoi(strtok(data,terminacion));
    }
    data = strtok(NULL,delimitador);
    contador++;
  }
}

//#####################################################################################################################

//ENTRADA: Un char(el nombre de archivo)
//DESCRIPCION: Funcion principal del archivo que se encarga de realizar los llamados para resolver la problematica
//SALIDA: Retorna el resultado obtenido por el algoritmo ejecutado

int programa_P2(char * name_file)
{
  FILE * file_matriz;
  file_matriz = fopen(name_file,"r");
  if(file_matriz == NULL)
  {
    printf("ERROR: NO HAY ARCHIVO \n"); //si no hay archivo
    return -1;
  }
  int resultado = 0, n = 0;
  char * aux_name_file = (char*)malloc(sizeof(char)*(strlen(name_file)+1)); //swe guarda espacio para la matriz
  strcpy(aux_name_file,name_file);

  getData2(aux_name_file,&resultado,&n);
 

  int **matriz = makeMatriz(name_file,n);
 

  fclose(file_matriz);
  int resultado_final = algoritmo(matriz,n);
  free(matriz);
  return resultado_final;
}

int main(int argc, char *argv[]) {

  
  clock_t cini, cfin;
  cini=clock();
  int resultado = programa_P2(argv[1]);
  printf("Resultado: %d\n",resultado);
  cfin=clock();
  printf("Tiempo de ejecucion:  %f \n",(double)(cfin-cini)/CLOCKS_PER_SEC);


  return 0;
}