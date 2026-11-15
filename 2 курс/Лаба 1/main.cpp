#include <cstdio>


const double K = 2.0;
const double B = 3.0;

const double X_START = 0.0;
const double X_END = 3.0;
const double STEP = 0.5;

double func(double x) {
	return K * x + B;
}

int main() {
	printf("\nCalculating function y(x) = 2 * x + 3 for x={0, 3} with step STEP = 1.5\n");
	printf("%-10s %-10s %-10s\n", "N", "x", "y");

	int count = 1;
	for (double x = X_START; x <= X_END; x += STEP) {
		printf("%-10d %-10.3f %-10.3f\n", count, x, func(x));
		count++;
	}

	printf("\nPress Enter to exit");
	getchar();
	return 0;
}













