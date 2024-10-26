#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <ctype.h>
double *vectorInd = NULL;
//Presentación
void Presentacion(){
    printf("\n----- DETERMINANTE -----\n\n");

    printf("Instrucciones:");
    printf("Objetivo:");

    printf("Integrantes:"); printf("\tNo.cta.:\n");
    printf("> López Chee \n");
    printf("> Franco Mitzi \n");
    printf("> \n");
    printf("> \n");

    printf("Fecha de entrega:");
}

// Función para verificar si la matriz es dominante diagonalmente
int esDominanteDiagonalmente(double **matriz, int n) {
	int i,j;
    for ( i = 0; i < n; i++) {
        double suma = 0.0;
        for ( j = 0; j < n; j++) {
            if (i != j)
                suma += fabs(matriz[i][j]);
        }
        if (fabs(matriz[i][i]) <= suma)
            return 0; // No es dominante diagonalmente
    }
    return 1; // Es dominante diagonalmente
}

// Función para encontrar el determinante por triangulación
double determinantePorTriangulacion(double **matriz, int n) {
    double det = 1.0;
    int i, j, k;
    for (i = 0; i < n; i++) {
        if (matriz[i][i] == 0) {
            int swap_row = i + 1;
            while (swap_row < n && matriz[swap_row][i] == 0)
                swap_row++;
            if (swap_row == n)
                return 0;
            for (j = 0; j < n; j++) {
                double temp = matriz[i][j];
                matriz[i][j] = matriz[swap_row][j];
                matriz[swap_row][j] = temp;
            }
            det = -det;
        }
        det *= matriz[i][i];
        for ( j = i + 1; j < n; j++) {
            double factor = matriz[j][i] / matriz[i][i];
            for (k = i; k < n; k++) {
                matriz[j][k] -= factor * matriz[i][k];
            }
        }
    }
    return det;
}

// Función para verificar si una cadena es un número válido
int esNumeroValido(char *cadena) {
    char *ptr = cadena;
    int hay_punto = 0;
    if (*ptr == '-' || *ptr == '+') ptr++; // Saltar signos
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
            printf("Entrada inválida. Solo se aceptan números enteros o con punto decimal. Inténtalo de nuevo: ");
    }
}

void imprimirMatriz(double **matriz, int n) {
    int i,j;
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
    printf("Vector Independiente:\n");
    for (i = 0; i < n; i++) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

double** LecturaMatriz(int n) {
    int i, j,k;


    double **matriz = (double **)malloc(n * sizeof(double*));

    // Verificar si se reservó memoria para la matriz
    if (matriz == NULL) {
        printf("Error al asignar memoria para la matriz.\n");
        return NULL;
    }
    for (i = 0; i < n; i++) {
        matriz[i] = (double *)malloc(n * sizeof(double));
    }
    // Reservar memoria para el vector independiente
    vectorInd = (double *)malloc(n * sizeof(double));

    // Leer los coeficientes de la matriz y los valores del vector correspondiente.
		printf("Introduce los coeficientes de la matriz por renglón:\n");
			for (i = 0; i < n; i++) {
   				 for (j = 0; j < n; j++) {
      				printf("Elemento [%d][%d]: ", i, j);
        			matriz[i][j] = leerNumero();
    			}
    			printf("Elemento del vector independiente x%d: ", i + 1);
    				vectorInd[i] = leerNumero();
				}

		// Preguntar si los datos son correctos
		char correcto;
		printf("¿Son correctos los datos? (s/n): ");
		scanf(" %c", &correcto);

		while (correcto != 's'&&correcto != 'S') {
   		 int renglon, columna;

    	printf("Introduce el renglón (0 a %d) y la columna (0 a %d) del elemento a corregir (formato: r c): ", n - 1, n - 1);
    	renglon = (int) leerNumero();
    	columna = (int) leerNumero();

    	if (renglon < 0 || renglon >= n || columna < 0 || columna >= n) {
        printf("Índices fuera de rango. Por favor, introduce índices válidos.\n");
        continue;
    	}

    	printf("Introduce el nuevo valor: ");
    	matriz[renglon][columna] = leerNumero();

    	printf("¿Son correctos los datos ahora? (s/n): ");
    	scanf(" %c", &correcto);
	}

	imprimirMatriz(matriz, n);

    imprimirVector(vectorInd, n);
    // Verificar si la matriz es dominante diagonalmente
    if (esDominanteDiagonalmente(matriz, n)) {
        printf("La matriz es dominante diagonalmente.\n");
    } else {
        printf("La matriz no es dominante diagonalmente, calculando determinante por triangulación.\n");
    }

    // Calcular el determinante por triangulación
    double determinante = determinantePorTriangulacion(matriz, n);

    // Mostrar el determinante
    printf("El determinante de la matriz es: %.2lf\n", determinante);

    // Verificar si el determinante es diferente de cero
    if (determinante != 0) {
        printf("El determinante es diferente de cero. El sistema tiene solución.\n");
    } else {
        printf("El sistema asociado no tiene solución.\n");
    }

	return matriz;

}

int main(){
	int n, i, j;

	printf("Introduce la dimensión n de la matriz: ");
    n = (int) leerNumero();

    if (n <= 0) {
        printf("La dimensión de la matriz debe ser un número positivo.\n");
        return 1;
    }

    double **matriz = LecturaMatriz(n);

    if (matriz == NULL) {
        printf("Error al crear la matriz.\n");
        return 1;
    }
	 // Liberar memoria
        for ( i = 0; i < n; i++) {
            free(matriz[i]);
        }
        free(matriz);
        free(vectorInd);
    return 0;
    }
