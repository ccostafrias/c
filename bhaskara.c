#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

	double a, b, c;

	printf("BHASKARA\n");

	while (1) {
		printf("Digite os coeficientes (a, b, c): \n");
		scanf("%lf %lf %lf", &a, &b, &c);
		if (a != 0) break;
	}

	double delta = (b*b) - (4*a*c);

	if (delta < 0) {
		double p;
		p = ((-b)/2*a);
		printf("As ra�zes complexas da equa��o s�o:\n");
		if (p != 0 ) {
			printf("Raiz 1: %g + %gi\n", p, sqrt(-delta)/(2*a));
			printf("Raiz 2: %g + (%g)i\n", p, (-sqrt(-delta))/(2*a));
		}
		else {
			printf("Raiz 1: %gi\n", sqrt(-delta)/(2*a));
			printf("Raiz 2: (%g)i\n", (-sqrt(-delta))/(2*a));
		}
		
	} else {
		double r1, r2;
		r1 = (-b + sqrt(delta))/(2*a);
		r2 = (-b - sqrt(delta))/(2*a);
		if (delta == 0) printf("H� apenas uma raiz: %g\n", r1);
		else printf("As ra�zes da equa��o s�o:\n%g e %g\n", r1, r2);
	}

	return 0;
}