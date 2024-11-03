#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//se agregan los comentarios del laboratorio con el fin de intentar llevar un orden para saber si se estaban cumpliendo todas las condiciones.

// Funci[on para reservar la matriz en memoria dinamica.
// Params:
// - int ***matrix: Doble puntero para la matriz que sera creada.
// - int size: Tamano de la matriz (numero de filas y columnas).
// Retorno:
// - No retorna un valor. Reserva memoria para la matriz.

void allocateMatrix(int ***matrix, int size) {
    *matrix = (int **)malloc(size * sizeof(int *)); // Reservar memoria
    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (int *)malloc(size * sizeof(int)); // Reservar memoria para cada columna en la fila i
    }
}

// Funcion para encontrar la longitud de la linea mas larga de 1s en una matriz cuadrada de tamaño `size`.
// Params:
// - int **matrix: Puntero a la matriz cuadrada de enteros.
// - int size: Tamano de la matriz (numero de filas y columnas).
// - int *result: Puntero donde se almacenar[a la longitud de la secuencia mas larga de 1s.
// Retorno:
// - No retorna un valor, pero modifica el valor en `result`.
void findLargestLine(int **matrix, int size, int *result) {
    *result = 0;  // Inicializa el resultado a 0
    int largo_max = 0;  // Longitud maxima de la secuencia encontrada
    int largo = 0;  // Longitud actual de la secuencia de 1s

    for (int i = 0; i < size; i++) {
        // Contar 1s en la fila actual
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                largo++;  // Incrementar la longitud actual
            } else {
                largo = 0;  // Reiniciar la longitud si se encuentra un 0
            }

            // Actualizar la longitud maxima si se encuentra una secuencia maas larga
            if (largo > largo_max) {
                largo_max = largo;
            }
        }

        // Manejo de la continuidad entre filas
        if (i < size - 1 && matrix[i][size - 1] == 1 && matrix[i + 1][0] == 1) {
            // Contar la longitud de 1s en la siguiente fila
            int siguiente_largo = 0;
            for (int k = 0; k < size; k++) {
                if (matrix[i + 1][k] == 1) {
                    siguiente_largo++;  // Contar 1s en la fila siguiente
                } else {
                    break;  // Detenerse al encontrar un 0
                }
            }
            // Sumar la longitud de la fila actual y la siguiente
            largo_max += siguiente_largo;  
        }

       
        largo = 0;  
    }

    *result = largo_max;  // Almacenar el resultado final
}


// Funcion para llenar la matriz con numeros aleatorios.
// Params:
// - int **matrix: Puntero a la matriz a llenar.
// - int size: Tamano de la matriz (numero de filas y columnas).
// Retorno:
// - No retorna un valor. Llena la matriz con valores aleatorios.
void fillMatrix(int **matrix, int size) {
    srand(time(NULL)); // Inicializar para generación de números aleatorios
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 2; // Genera 0 o 1 aleatoriamente
        }
    }
}
// Funci[on para imprimir la matriz.
// Params:
// - int **matrix: Puntero a la matriz a imprimir.
// - int size: Tamano de la matriz (número de filas y columnas).
// Retorno:
// - No retorna un valor. Imprime la matriz en la consola.
void printMatrix(int **matrix, int size) {
    printf("Matriz (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Funcion para liberar la memoria asignada a la matriz.
// Params:
// - int **matrix: Puntero a la matriz a liberar.
// - int size: Tamano de la matriz (numero de filas y columnas).
// Retorno:
// - No retorna un valor. Libera la memoria de la matriz.
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Funci[on para transponer la matriz.
void transposeMatrix(int **matrix, int **transposed, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

// Funcion principal dada
int main() {
    int size;
    printf("Ingrese el tamano de la matriz: ");
    scanf("%d", &size); // Leer el tamano de la matriz

    if (size < 1) {
        printf("El tamano de la matriz debe ser al menos 1.\n");
        return 1; // Manejo de tamano de matriz incorrecto o que no se puede
    }

    int **matrix = NULL;
    allocateMatrix(&matrix, size); // Reservar memoria para la matriz
    fillMatrix(matrix, size); // Llenar la matriz con numeros aleatorios
    printMatrix(matrix, size); // Imprimir la matriz

    int largestLineLength;
    findLargestLine(matrix, size, &largestLineLength); // Encontrar la secuencia mas larga de 1s
    printf("La longitud de la secuencia mas larga de 1s es: %d\n", largestLineLength);

    // Crear y llenar la matriz transpuesta
    int **transposedMatrix = NULL;
    allocateMatrix(&transposedMatrix, size); // Reservar memoria para la matriz transpuesta
    transposeMatrix(matrix, transposedMatrix, size);

    findLargestLine(transposedMatrix, size, &largestLineLength); // Encontrar la secuencia mas larga de 1s en la matriz transpuesta
    printf("La longitud de la secuencia mas larga de 1s en la matriz transpuesta es: %d\n", largestLineLength);

    freeMatrix(matrix, size); // Liberar la memoria de la matriz
    freeMatrix(transposedMatrix, size); // Liberar la memoria de la matriz transpuesta
    return 0;
}

