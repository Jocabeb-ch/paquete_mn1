#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <ctype.h>
double *vectorInd = NULL;
//Presentación
void Presentacion(){
    printf("\n----- DETERMINANTE Y JACOBI-----\n\n");

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
  int i, j;
  for (i = 0; i < n; i++) {
    double suma = 0.0;
    for (j = 0; j < n; j++) {
      if (i != j)
        suma += fabs(matriz[i][j]);
    }
    if (fabs(matriz[i][i]) <= suma)
      return 0; // No es dominante diagonalmente
  }
  return 1; // Es dominante diagonalmente
}

// Se necesita copiar la matriz porque la funcion por Triangulacion hacía el
// proceso en la matriz
// original y al tratr de acceder a ella después se accedía a la versión
// triangulada y no queremos modificar la original.
double **copiarMatriz(double **matriz, int n) {
  int i, j;
  double **copia = (double **)malloc(n * sizeof(double *));
  for (i = 0; i < n; i++) {
    copia[i] = (double *)malloc(n * sizeof(double));
    for (j = 0; j < n; j++) {
      copia[i][j] = matriz[i][j];
    }
  }
  return copia;
}

// Función para encontrar el determinante por triangulación sin modificar la
// matriz original
double determinantePorTriangulacion(double **matriz, int n) {
  double det = 1.0;
  int i, j, k;

  double **matrizCopia = copiarMatriz(matriz, n);

  for (i = 0; i < n; i++) {
    if (matrizCopia[i][i] == 0) {
      int swap_row = i + 1;
      while (swap_row < n && matrizCopia[swap_row][i] == 0)
        swap_row++;
      if (swap_row == n) {
        for (i = 0; i < n; i++)
          free(matrizCopia[i]);
        free(matrizCopia);
        return 0;
      }
      for (j = 0; j < n; j++) {
        double temp = matrizCopia[i][j];
        matrizCopia[i][j] = matrizCopia[swap_row][j];
        matrizCopia[swap_row][j] = temp;
      }
      det = -det;
    }

    det *= matrizCopia[i][i];
    for (j = i + 1; j < n; j++) {
      double factor = matrizCopia[j][i] / matrizCopia[i][i];
      for (k = i; k < n; k++) {
        matrizCopia[j][k] -= factor * matrizCopia[i][k];
      }
    }
  }
  // Liberar la memoria de la copia
  for (i = 0; i < n; i++)
    free(matrizCopia[i]);
  free(matrizCopia);

  return det;
}

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
  printf("Vector Independiente:\n");
  for (i = 0; i < n; i++) {
    printf("%.2f ", vector[i]);
  }
  printf("\n");
}

double **LecturaMatriz(int n) {
  int i, j;
  double **matriz = NULL;

  // Asignar memoria para la matriz de tamaño n x n
  matriz = (double **)malloc(n * sizeof(double *));
  if (matriz == NULL) {
    printf("Error al asignar memoria para la matriz.\n");
    return NULL;
  }

  for (i = 0; i < n; i++) {
    matriz[i] = (double *)malloc(n * sizeof(double));
    if (matriz[i] == NULL) {
      printf("Error al asignar memoria para la fila %d.\n", i);
      return NULL;
    }
  }

  vectorInd = (double *)malloc(n * sizeof(double));

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

  while (correcto != 's' && correcto != 'S') {
    int renglon, columna;

    printf("Introduce el renglón (0 a %d) y la columna (0 a %d) del elemento a "
           "corregir (formato: r c): ",
           n - 1, n - 1);
    renglon = (int)leerNumero();
    columna = (int)leerNumero();

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

  return matriz;
}
int verificarSol(double **matriz, int n) {
  double determinante = determinantePorTriangulacion(matriz, n);
  printf("El determinante de la matriz es: %.2lf\n", determinante);
  if (determinante != 0) {
    printf(
        "El determinante es diferente de cero. El sistema tiene solución.\n");
    return 1;
  } else {
    printf("El sistema asociado no tiene solución.\n");
    return 0;
  }
}

int verificarDom(double **matriz, int n, int *edd) {
    int dom=esDominanteDiagonalmente(matriz, n);
  if ( dom== 1) {
    printf("La matriz es dominante diagonalmente.Tiene solucion\n");
    *edd = 1;
    return 1;
  } else {
    printf("La matriz no es dominante diagonalmente, calculando determinante "
           "por triangulación.\n");
    return verificarSol(matriz, n);
  }
}
// recibir los dos vectores, el vectorInicial y el siguienteVector, y hacer la
// diferencia entre las dos en valor absoluto, hacer el algoritmo de cual es el
// más grande de esas diferencias renglon a renglon y devolver el mayor de esos
// valores para recibirlos en la funcion de metJacobi
double mayorDeDiferencias(double *vectorInicial, double *siguienteVector,int n) {
  int i;
  double maxDiferencia = 0.0;
  for (i=0;i<n;i++){
    double diferencia=fabs(siguienteVector[i] - vectorInicial[i]);
    if (diferencia>maxDiferencia){
      maxDiferencia=diferencia;
    }
  }
  return maxDiferencia;
}

// Primer paso:
// Despejar xi con i=1,2,3,...n, en n renglón.
// Despeje=
// 1/matriz[0][0]*(vectorInd[0]-matriz[0][1]*vectorInicial[1]-matriz[0][2]*vectorInicial[2]-matriz[0][3]*vectorInicial[3]....
void metJacobi(double **matriz, int n) {
  int i, j, max_Iter, iter;
  double *vectorInicial = NULL;
  double *siguienteVector = NULL;
  double tolerancia;

  printf("COMENZAMOS EL PROCESO DE JACOBI\n\n");
  vectorInicial = (double *)malloc(n * sizeof(double));

  printf("Introduce el vector inicial:\n");
  for (i = 0; i < n; i++) {
    printf("Elemento del vector inicial x%d: ", i + 1);
    vectorInicial[i] = leerNumero();
  }
  printf("Introduce el máximo de iteraciones: ");
  max_Iter = leerNumero();
  printf("Establece la tolerancia: ");
  scanf("%lf", &tolerancia);

  siguienteVector = (double *)malloc(n * sizeof(double));

  for (iter = 1; iter <= max_Iter; iter++) {
    printf("\nIteración %d:\n", iter);

    // Calcula el siguiente vector con base en el despeje de cada variable
    for (i = 0; i < n; i++) {
      siguienteVector[i]=vectorInd[i]; // Inicializa con el término independiente
      for (j = 0; j < n; j++) {
        if (i != j) {
          siguienteVector[i]-=matriz[i][j]*vectorInicial[j];
        }
      }
      siguienteVector[i] /= matriz[i][i];
      printf("siguienteVector[%d] = %.5lf\n", i, siguienteVector[i]);//aqui podemos cambiar cuantos decimales truncar
    }

    // Verificar diferencia y condición de convergencia
    double maxDiferencia = mayorDeDiferencias(vectorInicial, siguienteVector, n);
    printf("Mayor diferencia en esta iteración: %.5lf\n", maxDiferencia);

    if (maxDiferencia < tolerancia) {
      printf("Proceso convergió en la iteración %d.\n", iter);
      break;
    }
    // Actualizar vectorInicial para la siguiente iteración
    for (i = 0; i < n; i++) {
      vectorInicial[i] = siguienteVector[i];
    }
  }

  // Liberar la memoria
  free(vectorInicial);
  free(siguienteVector);
}

int menuSE() {
  int seleccion;

  system("cls");

  printf("2. SOLUCION DE SISTEMAS DE ECUACIONES\n\n");

  printf("1. lectura de matriz\n");
  printf("2. solucion del sistema\n");
  printf("3. solucion por factorizacion de Cholesky\n");
  printf("4. SALIDA\n\n");

  printf("Opción: ");
  scanf("%d", &seleccion);

  return seleccion;
}

int main() {
  int seleccion, i, n, sol;
  int edd = 0;
  double **matriz = NULL;

  do {
    seleccion = menuSE();

    switch (seleccion) {
    case 1:
      printf("\t\t1. lectura de matriz\n");
      printf("Introduce la dimensión n de la matriz: ");
      n = (int)leerNumero();
      if (n <= 0) {
        printf("La dimensión de la matriz debe ser un número positivo.\n");
        break;
      }
      matriz = LecturaMatriz(n);
      if (matriz == NULL) {
        printf("Error al crear la matriz.\n");
        break;
      }
      sol = verificarDom(matriz, n, &edd); // Variable creada para verificar
      // si la matriz tiene solucin, sea por EDD o por triangulacion
      system("pause");
      break;
    case 2:
      printf("\t\t2. solucion del sistema\n");
      if(matriz==NULL){
      	printf("\nNo has capturado la matriz\n");
      	break;
	  }else{
	  	// EDD ES PARA VER SI ES EDD
      	if (sol == 1) { // tiene solucion, por triangulacion o EDD
        	if (edd != 1) {
          	printf("...\tLa convergencia no se garantiza por no tratarse de un ""sistema EDD\n");
          	printf("¿Desea seguir con el proceso (1-Si//2-No)?\n");
          	int resp;
          	scanf("%d", &resp);
          		if (resp == 1){
          			metJacobi(matriz, n);
           		 	system("pause");
				  }
          		else
            		break; /// Sino adiooos
          }else{
          	metJacobi(matriz, n);
          	system("pause");
		  }
		}
      	else{
      		printf("El sistema no tiene solucion por det=0\n");
      		system("pause");
	  		}
	  	}
      break;
    case 3:
      printf("3. solucion por factorizacion de Cholesky\n");
      system("pause");
      break;
    case 4:
      printf("HASTA LUEGO\n\n");
      break;
    default:
      printf("OPCION NO VALIDA\n\n");
    }

  } while (seleccion != 4);
  // Liberar memoria
  if (matriz != NULL) {
    for (i = 0; i < n; i++) {
      free(matriz[i]);
    }
    free(matriz);
  }
  free(vectorInd);
  system("pause");

  return 0;
}
