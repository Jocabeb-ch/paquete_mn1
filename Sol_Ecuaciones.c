#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limpiarPantalla() {
    //Alternativa para system("cls")
    printf("\033[H\033[J");//Usamos secuencias de escape ANSI
}

void pausar(){
    //Alternativa para system("pause")
    printf("Presiona Enter para continuar...");
    getchar();
    getchar();
}

int menuMetodo(){
	int opcion;
	limpiarPantalla();

	printf("\n\n===== Primer programa =====\n\n");

	printf("--- M�TODOS ---\n\n");

	printf("1. M�TODO DE BISECCION.\n");
	printf("2. M�TODO DE LA SECANTE.\n");
	printf("3. SALIDA\n");

	printf("Opci�n: ");
	scanf("%d", &opcion);

	return opcion;
}

int menuFuncion(){
	int op;
	limpiarPantalla();

	printf("\n\n--- FUNCIONES ---\n\n");

	printf("1.  f(x) = x^2 cos(x) - 2x \n");
	printf("2.  f(x) = (6 - 2x^2) * exp^(2 + x^4) + 1 \n");
	printf("3.  f(x) = x^3 - 3 * sin(x^2) + 1 \n");
	printf("4.  f(x) = x^3 + 6x^2 + 9.4x + 2.5 \n");
	printf("5.  REGRESAR \n");

	printf("Opci�n: ");
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
			return((6-2/pow(x,2))*(exp(2+x))/4+1);
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

    //Inicia tabulaci�n.
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

    printf("La ra�z aproximada es: %f\n",p);
}

//Revisi�n de lo necesario para comenzar con el m�todo de bisecci�n
void Revision(int op) {
    double a,b,tol;
    int max_iter;

    printf("Introduce el valor de a (l�mite inferior): ");
    scanf("%lf",&a);

    printf("Introduce el valor de b (l�mite superior): ");
    scanf("%lf",&b);

    printf("Introduce el n�mero m�ximo de iteraciones: ");
    scanf("%d",&max_iter);

    printf("Introduce la tolerancia deseada: ");
    scanf("%lf",&tol);

    if (Evaluar(op,a)*Evaluar(op,b)>0)
        printf("El intervalo no encierra una ra�z\n\n");
    else
        biseccion(a, b, max_iter, op, tol);
}

void Secante(int op){
    double xk_1, xk, tol;
    int max_iter, indicador = 0;
    double RaizAu, toleAu;

    printf("Introduce el valor del limite inferior: ");
    scanf("%lf",&xk_1);
    printf("Introduce el valor del l�mite superior: ");
    scanf("%lf",&xk);
    printf("Introduce el n�mero m�ximo de iteraciones: ");
    scanf("%d",&max_iter);
    printf("Introduce la tolerancia deseada: ");
    scanf("%lf",&tol);

    if (fabs(xk-xk_1)<tol){
        printf("Error: Los l�mites iniciales no pueden ser iguales o demasiado cercanos.\n\n");
        return;
    }

    double fxk_1, fxk, xk1, fxk1, errorRelativo, xk1_anterior = 0;
    int i=0;
 // Inicia tabulaci�n.
    printf("%3s %12s %12s %12s %12s %12s %12s %12s\n", "i", "xk-1", "xk", "f(xk-1)", "f(xk)", "xk+1", "f(xk+1)", "Error Relativo P");
    do{
        // Calcula las funciones en los puntos actuales
        fxk_1=Evaluar(op, xk_1);
        fxk=Evaluar(op, xk);

        if (fabs(fxk_1-fxk)<tol){
            printf("Error: Divisi�n por cero, la funci�n no cambia significativamente.\n\n");
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

        // Verifica la condici�n de convergencia
        if (errorRelativo<=tol) {
            RaizAu=xk1;
            toleAu=errorRelativo;
            indicador=1; // Indicador de convergencia
            break;
        }
    }while (i<max_iter);

    if(indicador==1)
        printf(">La ra�z aproximada es: %lf con la tolerancia %lf \n\n",RaizAu,toleAu);
    else {
        printf(">Se alcanz� el n�mero m�ximo de iteraciones sin convergencia.\n");
        printf(">La �ltima ra�z aproximada es: %lf con el error relativo %lf \n\n", xk1, errorRelativo);
    }
}

void eleccionMetodo(int op,int met){
	do{
		op=menuFuncion();

		switch(op){
			case 1:
				printf("Has elegido la funci�n 1. \n");
					if(met==1){
						printf("Resolviendo la funci�n f(x) = x^2 cos(x) - 2x por el m�todo de la BISECCION.\n  ");
						Revision(op);
					}
					else{
						printf("Resolviendo la funci�n f(x) = x^2 cos(x) - 2x por el m�todo de la SECANTE.\n  ");
						Secante(op);
					}

				pausar();
				break;
			case 2:
				printf("Has elegido la funci�n 2. \n");
				if(met==1){
						printf("Resolviendo la funci�n  f(x) = (6 - 2x^2) * exp^(2 + x^4) + 1  por el m�todo de la BISECCION.\n  ");
						Revision(op);
					}
					else{
						printf("Resolviendo la funci�n  f(x) = (6 - 2x^2) * exp^(2 + x^4) + 1 por el m�todo de la SECANTE.\n  ");
						Secante(op);
					}
				pausar();
				break;
			case 3:
				printf("Has elegido la funci�n 3. \n");
				if(met==1){
						printf("Resolviendo la funci�n f(x) = x^3 - 3 * sin(x^2) + 1 por el m�todo de la BISECCION\n  ");
						Revision(op);
					}
					else{
						printf("Resolviendo la funci�n f(x) = x^3 - 3 * sin(x^2) + 1 por el m�todo de la SECANTE.\n  ");
						Secante(op);
					}
				pausar();
				break;
			case 4:
				printf("Has elegido la funci�n 4. \n");
				if(met==1){
						printf("Resolviendo la funci�n f(x) = x^3 + 6x^2 + 9.4x + 2.5 por el m�todo de la BISECCION.\n  ");
						Revision(op);
					}
					else{
						printf("Resolviendo la funci�n f(x) = x^3 + 6x^2 + 9.4x + 2.5 por el m�todo de la SECANTE.\n  ");
						Secante(op);
					}
				pausar();
				break;
			case 5:
				printf("Regresando al men� anterior...\n\n");
				pausar();
				break;
			default:
				printf("OPCI�N NO V�LIDA :c \n\n");
		}

	}while(op != 5);

}
int main(){

	int opcion;
	int met=0;

	do{
		opcion=menuMetodo();

		switch(opcion){
			case 1://Bisecci�n
				met=1;
				eleccionMetodo(opcion,met);
				break;
			case 2://Secante
				eleccionMetodo(opcion,met);
				break;
			case 3://Salida
				printf("HASTA LUEGO :) \n\n");
				break;
			default:
				printf("OPCI�N NO V�LIDA :c \n\n");
		}

		printf("\n\n�Desea obtener otra ra�z? (1: S� | 0: No): ");
        int resp;
        scanf("%d", &resp);
        if (!resp) break;

	}while(opcion != 3);

	pausar();
	return 0;
}
