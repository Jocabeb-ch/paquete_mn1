#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        printf("\033[H\033[J");
    #endif
}

void pausar() {
    #ifdef _WIN32
        system("pause"); // Windows
    #else
        printf("Presiona Enter para continuar...");
        getchar();
    #endif
}

int menuMetodo(){
	int opcion;
	limpiarPantalla();

	printf("\n\n===== Primer programa =====\n\n");

	printf("--- MÉTODOS ---\n\n");

	printf("1. MÉTODO DE BISECCION.\n");
	printf("2. MÉTODO DE LA SECANTE.\n");
	printf("3. SALIDA\n");

	printf("Opción: ");
	scanf("%d", &opcion);

	return opcion;
}

int menuFuncion(){
	int op;
	limpiarPantalla();

	printf("\n\n--- FUNCIONES ---\n\n");

	printf("1.  f(x) = x^2 cos(x) - 2x \n");
	printf("2.  f(x) = (6 - 2/x^2) * exp^(2 + x^4) + 1 \n");
	printf("3.  f(x) = x^3 - 3 * sin(x^2) + 1 \n");
	printf("4.  f(x) = x^3 + 6x^2 + 9.4x + 2.5 \n");
	printf("5.  REGRESAR \n");

	printf("Opción: ");
	scanf("%d", &op);

	printf("\n\n");

	return op;
}

double Evaluar(int op,double x) {

	switch(op){
		case 1:
			return(x*x*cos(x))-(2 * x);
			break;
		case 2:
			return((6-2/pow(x,2))*(exp(2+x)/4)+1);
			break;
		case 3:
			return(pow(x,3)-3*sin(x*x)+1);
			break;
		case 4:
			return(pow(x,3)+6*x*x+9.4*x+2.5);
			break;
	}
}

void biseccion(double a, double b, int max_iter,int op, double tol) {
    double fa,fb,p,fp,errorAprox,p_anterior;
    int i=0;

    //Inicia tabulación.
    printf("%3s %12s %12s %12s %12s %12s %12s %12s\n","i","a","b","f(a)","f(b)","p=(a+b)/2","f(p)","Error Aproximado");
    do {
        fa=Evaluar(op,a);
        fb=Evaluar(op,b);

        p=(a+b)/2.0;
        fp=Evaluar(op,p);

        if(i==0)
            errorAprox=fabs(b-a);  // Error inicial
        else
            errorAprox=fabs((p-p_anterior)/p)*100;  // Error relativo porcentual

        // Imprimir fila de la tabla
        printf("%3d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n",i,a,b,fa,fb,p,fp,errorAprox);

        //Algortimo
        if(fa*fp<0)
            b=p;
         else
		 	if (fa*fp>0)
            	a=p;
        	else
            break;
        p_anterior=p;
        i++;

    }while(i<max_iter&&errorAprox>tol);
   	if(errorAprox<tol)
   		printf("Se alcanzo la tolerancia, terminando proceso antes del maximo de iteraciones\n");
	else
		printf("No se alcanzo la tolerancia\n");
	
    printf("La raíz aproximada es: %f\n",p);
}

//Revisión de lo necesario para comenzar con el método de bisección
void Revision(int op) {
    double a,b,tol;
    int max_iter;

    printf("Introduce el valor de a (límite inferior): ");
    scanf("%lf",&a);

    printf("Introduce el valor de b (límite superior): ");
    scanf("%lf",&b);

    printf("Introduce el número máximo de iteraciones: ");
    scanf("%d",&max_iter);

    printf("Introduce la tolerancia deseada: ");
    scanf("%lf",&tol);

    if (Evaluar(op,a)*Evaluar(op,b)>0)
        printf("El intervalo no encierra una raíz\n\n");
    else
        biseccion(a, b, max_iter, op, tol);
}

void Secante(int op){
    double xk_1, xk, tol;
    int max_iter, indicador = 0;
    double RaizAu, toleAu;

    printf("Introduce el valor del limite inferior: ");
    scanf("%lf",&xk_1);
    printf("Introduce el valor del límite superior: ");
    scanf("%lf",&xk);
    printf("Introduce el número máximo de iteraciones: ");
    scanf("%d",&max_iter);
    printf("Introduce la tolerancia deseada: ");
    scanf("%lf",&tol);

    if (fabs(xk-xk_1)<tol){
        printf("Error: Los límites iniciales no pueden ser iguales o demasiado cercanos.\n\n");
        return;
    }

    double fxk_1, fxk, xk1, fxk1, errorRelativo, xk1_anterior = 0;
    int i=0;
 // Inicia tabulación.
    printf("%3s %12s %12s %12s %12s %12s %12s %12s\n", "i", "xk-1", "xk", "f(xk-1)", "f(xk)", "xk+1", "f(xk+1)", "Error Relativo P");
    do{
        // Calcula las funciones en los puntos actuales
        fxk_1=Evaluar(op, xk_1);
        fxk=Evaluar(op, xk);

        if (fabs(fxk_1-fxk)<tol){
            printf("Error: División por cero, la función no cambia significativamente.\n\n");
            printf(">La raíz aproximada hasta este momento es: %lf con la tolerancia %lf \n\n",RaizAu,toleAu);
            return;
        }
        //xk+1
        xk1=xk-(fxk*(xk_1-xk)/(fxk_1-fxk));
        fxk1=Evaluar(op,xk1);

        if(i==0)
            errorRelativo=fabs(xk-xk_1);// Error inicial
        else
            errorRelativo=fabs((xk1-xk1_anterior)/xk1)*100; // Error relativo porcentual

        printf("%3d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n", i,xk_1,xk,fxk_1,fxk,xk1,fxk1,errorRelativo);

        //Algoritmo
        xk_1=xk;
        xk=xk1;
        xk1_anterior=xk1;
        i++;

        // Verifica la condición de convergencia
        if (errorRelativo<=tol) {
            RaizAu=xk1;
            toleAu=errorRelativo;
            indicador=1; // Indicador de convergencia
            break;
        }
    }while (i<max_iter);

    if(indicador==1)
        printf(">La raíz aproximada es: %lf con la tolerancia %lf sin llegar al maximo de iteraciones\n\n",RaizAu,toleAu);
    else {
        printf(">Se alcanzó el número máximo de iteraciones sin convergencia.\n");
        printf(">La última raíz aproximada es: %lf con el error relativo %lf \n\n", xk1, errorRelativo);
    }
}
void iterar(int met, int op) {
    int resp; // Declarar la variable resp
    do {
        printf("\n\n¿Desea obtener otra raíz? (1: Sí | 0: No): ");
        scanf("%d", &resp);

        if (resp == 1) { // Si la respuesta es 1, ejecutar el método correspondiente
            if (met == 1)
                Revision(op);
            else
                Secante(op);
        }
    } while (resp != 0); // Repetir mientras la respuesta no sea 0
}


void eleccionMetodo(int op,int met){
	int resp;
	do{
		op=menuFuncion();

		switch(op){
			case 1:
				printf("Has elegido la función 1. \n");
					if(met==1){
						printf("Resolviendo la función f(x) = x^2 cos(x) - 2x por el método de la BISECCION.\n  ");
						Revision(op);
						iterar(met,op);
						
					}
					else{
						printf("Resolviendo la función f(x) = x^2 cos(x) - 2x por el método de la SECANTE.\n  ");
						Secante(op);
						iterar(met,op);
					}

				pausar();
				break;
			case 2:
				printf("Has elegido la función 2. \n");
				if(met==1){
						printf("Resolviendo la función  f(x) = (6 - 2/x^2) * exp^(2 + x^4) + 1  por el método de la BISECCION.\n  ");
						Revision(op);
						iterar(met,op);
					}
					else{
						printf("Resolviendo la función  f(x) = (6 - 2/x^2) * exp^(2 + x^4) + 1 por el método de la SECANTE.\n  ");
						Secante(op);
						iterar(met,op);
					}
				pausar();
				break;
			case 3:
				printf("Has elegido la función 3. \n");
				if(met==1){
						printf("Resolviendo la función f(x) = x^3 - 3 * sin(x^2) + 1 por el método de la BISECCION\n  ");
						Revision(op);
						iterar(met,op);
					}
					else{
						printf("Resolviendo la función f(x) = x^3 - 3 * sin(x^2) + 1 por el método de la SECANTE.\n  ");
						Secante(op);
						iterar(met,op);
						
					}
				pausar();
				break;
			case 4:
				printf("Has elegido la función 4. \n");
				if(met==1){
						printf("Resolviendo la función f(x) = x^3 + 6x^2 + 9.4x + 2.5 por el método de la BISECCION.\n  ");
						Revision(op);
						iterar(met,op);
					}
					else{
						printf("Resolviendo la función f(x) = x^3 + 6x^2 + 9.4x + 2.5 por el método de la SECANTE.\n  ");
						Secante(op);
						iterar(met,op);
					}
				pausar();
				break;
			case 5:
				printf("Regresando al menú anterior...\n\n");
				pausar();
				break;
			default:
				printf("OPCIÓN NO VÁLIDA :c \n\n");
		}

	}while(op != 5);

}

///Principal
void menu_Primero(){
	int opcion;
	int met;

	do{
		opcion=menuMetodo();

		switch(opcion){
			case 1://Bisección
				met=1;
				eleccionMetodo(opcion,met);
				break;
			case 2://Secante
				met=0;
				eleccionMetodo(opcion,met);
				break;
			case 3://Salida
				printf("HASTA LUEGO :) \n\n");
				break;
			default:
				printf("OPCIÓN NO VÁLIDA :c \n\n");
		}

	}while(opcion != 3);

	pausar();
}
int menuPrincipal(){
	int opcionP;
	limpiarPantalla();


	printf("--- PAQUETE ---\n\n");

	printf("1. SOLUCION DE ECUACIONES.\n");
	printf("2. SOLUCION DE SISTEMAS DE ECUACIONES.\n");
	printf("3. OBTENCION DE VALORES PROPIOS.\n");
	printf("4. SALIDA\n");

	printf("Opción: ");
	scanf("%d", &opcionP);

	return opcionP;
}
///PARTE DEL SEGUNDO Y TERCER PROGRAMA/////////////////////////////////////////////////////////////////
double *vectorInd = NULL;

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
  printf("\n --- Matriz ---\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%.4lf ", matriz[i][j]);
    }
    printf("\n");
  }
}

void imprimirVector(double *vector, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%.5f ", vector[i]); // ajustar hasta donde truncar decimales
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
  printf("2. solucion del sistema por Jacobi\n");
  printf("3. regresar a menu principal\n\n");

  printf("Opción: ");
  scanf("%d", &seleccion);

  return seleccion;
}

int m_Sol() {
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
      printf("HASTA LUEGO\n\n");
      break;
    default:
      printf("OPCION NO VALIDA\n\n");
    }

  } while (seleccion != 3);
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



////////////////////////////////////////////////////////////////////////////////////////////
//////////////CUARTO PROGRAMA
// Función para normalizar un vector
void normalizarVector(double *vector, int n) {
  double norma = 0;
  int i;
  for (i = 0; i < n; i++) {
    norma += vector[i] * vector[i];
  }
  norma = sqrt(norma);
  for (i = 0; i < n; i++) {
    vector[i] /= norma;
  }
}
// Función para corregir un coeficiente de la matriz
void corregirCoeficiente(double **matriz, int n) {
  int fila, columna;
  printf("Introduce la posición (fila columna) del coeficiente incorrecto (1 a "
         "%d):\n",
         n);
  scanf("%d %d", &fila, &columna);

  // Validar posición
  if (fila < 1 || fila > n || columna < 1 || columna > n) {
    printf("\n Posición no válida. Intente de nuevo.\n");
    return;
  }

  printf("Introduce el nuevo valor para el coeficiente (%d,%d):\n", fila,
         columna);
  matriz[fila - 1][columna - 1] = leerNumero();
}

// Multiplicar matriz por vector
double *multiplicarMatrizVector(double **matriz, double *vector, int n) {
  double *resultado = (double *)malloc(n * sizeof(double));
  if (!resultado) {
    printf("\n Error: No se pudo asignar memoria para el vector resultado.\n");
    return NULL;
  }

  int i, j;
  for (i = 0; i < n; i++) {
    resultado[i] = 0;
    for (j = 0; j < n; j++) {
      resultado[i] += matriz[i][j] * vector[j];
    }
  }

  return resultado;
}

// Método de potencias
void met_Potencias(double **matriz, double *vector, int n, int iter,
                   double tolerancia, int ban) {
  double max = 0, maxAnterior = 0, prueba_t;
  double *resultado;
  int i, j;

  for (j = 0; j <= iter; j++) {
    printf("\n --- Iteración %d --- \n", j);

    // Multiplicar matriz por vector
    resultado = multiplicarMatrizVector(matriz, vector, n);
    if (!resultado)
      return;

    printf(">Resultado del producto A * x_k: ");
    imprimirVector(resultado, n);

    // Encontrar el máximo en valor absoluto
    max = fabs(resultado[0]);
    for (i = 1; i < n; i++) {
      if (fabs(resultado[i]) > max) {
        max = fabs(resultado[i]);
      }
    }

    // Imprimir el valor máximo y mínimo
    printf(">El mayor valor propio (lambda) de esta iteración es: %lf\n", max);
    for (i = 0; i < n; i++) {
      vector[i] = resultado[i] / max;
    }

    // Imprimir vector normalizado
    printf(">Vector normalizado x_{k+1}: ");
    imprimirVector(vector, n);

    // Verificar la tolerancia si estamos en la iteración 2 o más
    if (j >= 1) {
      prueba_t = fabs(max - maxAnterior);
      printf(">Error: %lf\n", prueba_t);
      if (prueba_t < tolerancia) {
        printf(">Se alcanzó la tolerancia: %lf < %lf\n", prueba_t, tolerancia);
        break;
      }
    }

    // Actualizar el máximo anterior
    maxAnterior = max;

    // Liberar memoria del vector resultado
    free(resultado);
  }

  // Imprimir el mayor valor propio encontrados
  printf("\n>El mayor valor propio encontrado es: %lf\n", max);
  if (ban == 1) {
    printf("Se aplico potencias inversas, por lo tanto el menor valor propio "
           "encontrado es: %lf\n",
           1 / max);
  }
  // if (resultado) free(resultado);
}

// Liberar memoria de una matriz
int i;
void liberar_matriz(double **matriz, int filas) {
  for (i = 0; i < filas; i++) {
    free(matriz[i]);
  }
  free(matriz);
}

// Función para calcular la inversa de una matriz
double **inversa(double **matriz, int n) {
  // Crear la matriz aumentada
  double **aumentada = (double **)malloc(n * sizeof(double *));
  if (!aumentada) {
    printf("Error al asignar memoria para la matriz aumentada.\n");
    return NULL;
  }
  int i,j,k;

  for (i = 0; i < n; i++) {
    aumentada[i] = (double *)malloc(2 * n * sizeof(double));
    if (!aumentada[i]) {
      printf("Error al asignar memoria para la fila %d.\n", i);
      liberar_matriz(aumentada, i);
      return NULL;
    }
  }

  // Llenar la matriz aumentada
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      aumentada[i][j] = matriz[i][j];
      aumentada[i][j + n] = (i == j) ? 1.0 : 0.0;
    }
  }

  // Eliminación gaussiana
  for (i = 0; i < n; i++) {
    if (fabs(aumentada[i][i]) < 1e-10) {
      int k;
      for (k = i + 1; k < n; k++) {
        if (fabs(aumentada[k][i]) > 1e-10) {
          double *temp = aumentada[i];
          aumentada[i] = aumentada[k];
          aumentada[k] = temp;
          break;
        }
      }
      if (k == n) {
        printf("La matriz no es invertible.\n");
        liberar_matriz(aumentada, n);
        return NULL;
      }
    }

    double pivote = aumentada[i][i];
    for (j = 0; j < 2 * n; j++) {
      aumentada[i][j] /= pivote;
    }

    for (k = 0; k < n; k++) {
      if (k != i) {
        double factor = aumentada[k][i];
        for (j = 0; j < 2 * n; j++) {
          aumentada[k][j] -= factor * aumentada[i][j];
        }
      }
    }
  }

  // Extraer la matriz inversa
  double **inversa = (double **)malloc(n * sizeof(double *));
  if (!inversa) {
    printf("Error al asignar memoria para la matriz inversa.\n");
    liberar_matriz(aumentada, n);
    return NULL;
  }

  for (i = 0; i < n; i++) {
    inversa[i] = (double *)malloc(n * sizeof(double));
    if (!inversa[i]) {
      printf("Error al asignar memoria para la fila %d de la matriz inversa.\n", i);
      liberar_matriz(inversa, i);
      liberar_matriz(aumentada, n);
      return NULL;
    }
    for (j = 0; j < n; j++) {
      inversa[i][j] = aumentada[i][j + n];
    }
  }

  liberar_matriz(aumentada, n);
  return inversa;
}

int mainPot() {
  int i, j, n, iter1, iter2;
  double tolerancia1, tolerancia2;
  char opcion;
  int ban = 0;

  printf("=== Metodo de Potencias ===\n");
  double **matriz = NULL;
  double **mInversa = NULL;
  double *vectorIn1 = NULL;
  double *vectorIn2 = NULL;

  printf("\n >Introduzca el valor de n (numero de filas y columnas de la "
         "matriz cuadrada):\n");
  n = (int)leerNumero();

  matriz = (double **)malloc(n * sizeof(double *));
  if (matriz == NULL) {
    printf("\n Error al asignar memoria para la matriz.\n");
    return 0;
  }

  for (i = 0; i < n; i++) {
    matriz[i] = (double *)malloc(n * sizeof(double));
    if (matriz[i] == NULL) {
      printf("\n Error al asignar memoria para la fila %d.\n", i);
      return 0;
    }
  }

  vectorIn1 = (double *)malloc(n * sizeof(double));
  if (vectorIn1 == NULL) {
    printf("\n Error al asignar memoria para el vector inicial.\n");
    return 0;
  }

  printf("\n >Introduce los coeficientes de la matriz por renglón:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("Elemento [%d][%d]: ", i + 1, j + 1);
      matriz[i][j] = leerNumero();
    }
  }

  printf("\n * * * * * * * * * * * * * * * * * * * * * * ");
  printf("\n ¿Desea cambiar algún coeficiente? (s/n): ");
  scanf(" %c", &opcion);
  while (opcion == 's' || opcion == 'S') {
    corregirCoeficiente(matriz, n);
    printf("\n ¿Desea cambiar otro coeficiente? (s/n): ");
    scanf(" %c", &opcion);
  }
  printf("\n * * * * * * * * * * * * * * * * * * * * * *\n");

  printf("\n >Introduce el vector inicial:\n");
  for (i = 0; i < n; i++) {
    printf("Elemento [%d]: ", i + 1);
    vectorIn1[i] = leerNumero();
  }

  imprimirMatriz(matriz, n);
  printf("\n >Vector inicial:\n");
  imprimirVector(vectorIn1, n);

  printf("\n >Introduce el número máximo de iteraciones:\n");
  iter1 = (int)leerNumero();

  printf("\n >Introduce la tolerancia:\n");
  tolerancia1 = leerNumero();

  // Llamar al método de potencias para obtener el mayor valor propio
  met_Potencias(matriz, vectorIn1, n, iter1, tolerancia1, ban);
  // Crear inversa
  printf("\n "
         "_______________________"
         "_\n");
  printf("Obteniendo el menor valor propio con Potencias Inverso\n");
  mInversa = (double **)malloc(n * sizeof(double *));
  if (matriz == NULL) {
    printf("\n Error al asignar memoria para la matriz.\n");
    return 0;
  }

  for (i = 0; i < n; i++) {
    mInversa[i] = (double *)malloc(n * sizeof(double));
    if (mInversa[i] == NULL) {
      printf("\n Error al asignar memoria para la fila %d.\n", i);
      return 0;
    }
  }

  mInversa = inversa(matriz, n);
  printf("\n >Matriz inversa:\n");
  imprimirMatriz(mInversa, n);

  vectorIn2 = (double *)malloc(n * sizeof(double));
  if (vectorIn2 == NULL) {
    printf("\n Error al asignar memoria para el vector inicial.\n");
    return 0;
  }

  printf("\n * * * * * * * * * * * * * * * * * * * * * *\n");

  printf("\n >Introduce el vector inicial:\n");
  for (i = 0; i < n; i++) {
    printf("Elemento [%d]: ", i + 1);
    vectorIn2[i] = leerNumero();
  }

  imprimirMatriz(mInversa, n);
  printf("\n >Vector inicial:\n");
  imprimirVector(vectorIn2, n);

  printf("\n >Introduce el número máximo de iteraciones:\n");
  iter2 = (int)leerNumero();

  printf("\n >Introduce la tolerancia:\n");
  tolerancia2 = leerNumero();

  ban = 1;
  met_Potencias(mInversa, vectorIn2, n, iter2, tolerancia2, ban);

  // Liberar memoria
  for (i = 0; i < n; i++) {
    free(matriz[i]);
  }
  free(matriz);

  for (i = 0; i < n; i++) {
    free(mInversa[i]);
  }
  free(mInversa);

  free(vectorIn1);
  free(vectorIn2);

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	int opcionP;
	int met=0;

	do{
		opcionP=menuPrincipal();

		switch(opcionP){
			case 1:
				menu_Primero();
				pausar();
				break;
			case 2:
				m_Sol();
				pausar();
				break;
			case 3:
				mainPot();
				pausar();
				break;
			case 4://Salida
				printf("HASTA LUEGO :) \n\n");
				break;
			default:
				printf("OPCIÓN NO VÁLIDA :c \n\n");
		}

	}while(opcionP != 4);

	pausar();
}
