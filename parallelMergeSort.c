#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// INSTRUCCIONES DE USO
// 1. compilacion :  gcc -lpthread -lm -o a.out parallelMergeSort.c
// 2. uso: ./a.out {elementos del arreglo separado por coma} {cantidad de elementos ingresados}
// 3. ej: ./a.out 6,5,12,10,9,1,43,7,15 9


// Crear main y recibir arreglo por consola.
// Convertir el arreglo de string a un arreglo int.
// Puedo pedir que se especifique la cantidad de numeros a recibir
// Implementar el algoritmo merge sort sin hilos
// Una vez funcional lo empiezo a implementar con hilos

#define LENGTH 1000

int arr[LENGTH];

// Uso la estructura para pasar argumentos al hilo
struct indices
{
    int inicio;
    int fin;
};

// Implementacion del merge

void merge(int arr[], int p, int q, int r) {

  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Implementacion del merge sort
void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

// Implementacion del metodo que recibe el hilo
// Llama al mergeSort, el cual debo enviarle los
// argumentos de la estructura

void* thread_mergeSort(void* arg)
{
    struct indices idx = *(struct indices*)arg;
    mergeSort(arr,idx.inicio,idx.fin);
    return 0;
}

// Print the array
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}


int main(int argc, char** argv)
{
    // Creo los hilos
    pthread_t t1;
    pthread_t t2;

    struct indices p1;
    struct indices p2;


    // Genero un arreglo de caracteres separados por coma del tamaño de la cadena
    char input[strlen(argv[1])];

    // Guardo la cadena en el arreglo
    strcpy(input,argv[1]);

    // Creo arreglo de enteros donde voy a guardar los valores de la cadena
    int arreglo[atoi(argv[2])];

    // Separo la cadena de caracteres por el delimitador ','
    char* token = strtok(input, ",");
    int i = 0;
    while(token != NULL){
        arreglo[i] = atoi(token);
        arr[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    int size = sizeof(arreglo)/sizeof(arreglo[0]);

    // Creo los hilos luego de llenar los arreglos
    // Inicializo valores de los primeros argumentos

    p1.inicio = 0;
    p1.fin = (size/2) - 1;

    if(pthread_create(&t1,NULL,&thread_mergeSort,&p1) != 0){

        perror("No se creó el hilo 1\n");
    }

    // Inicializo valores de los argumentos para el segundo hilo
    p2.inicio = (size/2);
    p2.fin = size - 1;
    if(pthread_create(&t2,NULL,&thread_mergeSort,&p2) != 0){

        perror("No se creó el hilo 2\n");
    }

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    // Como el arreglo es global, debo llamar una vez a merge
    // Calcular los parametros de merge
    // Indice inicial del arr
    int l = 0;
    // Indice final del arr
    int r = size - 1;
    // Indice inicial de la segunda mitad
    int m = (size / 2) - 1;
    merge(arr, l, m, r);


    printf("Arreglo ordenado: \n");
    printArray(arr, size);
    return 0;
}
