#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <ctype.h>
double *vectorInd = NULL;

// Función para verificar si una cadena es un número válido
int esNumeroValido(char *cadena) {
  char *ptr = cadena;
  int hay_punto = 0;
  if (*ptr == '-' || *ptr == '+')
    ptr++;
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      if (*ptr == '.' && !hay_punto) {
        hay_punto = 1; // Permitir un punto decimal
      } else {
        return 0; // No es un número válido
      }
    }
    ptr++;
  }
  return 1; // Es un número válido
}

// Función para leer un número válido
double leerNumero() {
  char input[100];
  while (1) {
    scanf("%s", input);
    if (esNumeroValido(input))
      return atof(input);
    else
      printf("Entrada inválida. Solo se aceptan números enteros o con punto "
             "decimal. Inténtalo de nuevo: ");
  }
}

void imprimirMatriz(double **matriz, int n) {
  int i, j;
  printf("Matriz:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%.2lf ", matriz[i][j]);
    }
    printf("\n");
  }
}

void imprimirVector(double *vector, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%.5f ", vector[i]);//ajustar hasta donde truncar decimales
  }
  printf("\n");
}

// Multiplicar matriz por vector
double *multiplicarMatrizVector(double **matriz, double *vector, int n) {
    double *resultado = (double *)malloc(n * sizeof(double));
    if (!resultado) {
        printf("Error: No se pudo asignar memoria para el vector resultado.\n");
        return NULL;
    }
	int i,j;
    for ( i = 0; i < n; i++) {
        resultado[i] = 0;
        for (j = 0; j < n; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }

    return resultado;
}


// Método de potencias
void met_Potencias(double **matriz, double *vector, int n, int iter, double tolerancia) {
    double max = 0, maxAnterior = 0, prueba_t;
    double *resultado;
	int j;
    for ( j = 1; j <= iter; j++) {
        printf("\nIteración %d\n", j);

        // Multiplicar matriz por vector
        resultado = multiplicarMatrizVector(matriz, vector, n);
        if (!resultado) return;

        printf("Resultado del producto A * x_k: ");
        imprimirVector(resultado, n);
		int i;
        // Encontrar el máximo en valor absoluto
        max = fabs(resultado[0]);
        for ( i = 1; i < n; i++) {
            if (fabs(resultado[i]) > max) {
                max = fabs(resultado[i]);
            }
        }

        // Imprimir el valor máximo
        printf("El mayor valor propio (lambda) de esta iteracion es: %lf\n", max);
        for (i = 0; i < n; i++) {
            vector[i] = resultado[i] / max;
        }

        // Imprimir vector normalizado
        printf("Vector normalizado x_{k+1}: ");
        imprimirVector(vector, n);

        // Verificar la tolerancia si estamos en la iteración 2 o más
        if (j >= 2) {
            prueba_t = fabs(max - maxAnterior);
            printf("Error: %lf\n", prueba_t);
            if (prueba_t < tolerancia) {
                printf("Se alcanzó la tolerancia: %lf < %lf\n", prueba_t, tolerancia);
                break;
            }
        }

        // Actualizar el máximo anterior
        maxAnterior = max;

        // Liberar memoria del vector resultado
        free(resultado);
    }

    // Imprimir el mayor valor propio encontrado
    printf("\nEl mayor valor propio encontrado es: %lf\n", max);
    if (resultado) free(resultado);
}


int main() {
    int i, j, n, iter;
    double tolerancia;

    printf("Metodo de Potencias\n");
    double **matriz = NULL;
    double *vectorIn = NULL;

    printf("Introduzca el valor de n (numero de filas y columnas de la matriz cuadrada):\n");
    n = (int)leerNumero();

    matriz = (double **)malloc(n * sizeof(double *));
    if (matriz == NULL) {
        printf("Error al asignar memoria para la matriz.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        matriz[i] = (double *)malloc(n * sizeof(double));
        if (matriz[i] == NULL) {
            printf("Error al asignar memoria para la fila %d.\n", i);
            return 0;
        }
    }

    vectorIn = (double *)malloc(n * sizeof(double));
    if (vectorIn == NULL) {
        printf("Error al asignar memoria para el vector inicial.\n");
        return 0;
    }

    printf("Introduce los coeficientes de la matriz por renglón:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            matriz[i][j] = leerNumero();
        }
    }

    printf("Introduce el vector inicial:\n");
    for (i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i);
        vectorIn[i] = leerNumero();
    }

    imprimirMatriz(matriz, n);
    printf("\nVector inicial:\n");
    imprimirVector(vectorIn, n);

    printf("Introduce el número máximo de iteraciones:\n");
    iter = (int)leerNumero();

    printf("Introduce la tolerancia:\n");
    tolerancia = leerNumero();

    // Llamar al método de potencias para obtener el mayor valor propio
    met_Potencias(matriz, vectorIn, n, iter, tolerancia);
    
    // Liberar memoria
    for (i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(vectorIn);

    return 0;
}
