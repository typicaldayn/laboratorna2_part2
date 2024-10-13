#include <stdio.h>

// Variant 1 Integral(0,1) (1 / 4 + x^2)dx
unsigned int validateInput(const char* formatSpecifier, void* value, char message[]);
double calculateIntegralRectangles();
double calculateIntegralTrapezium();
double calculateIntegralParabola();

int main(void) {
    double left_boundary_a;
    double right_boundary_b;
    double measurement_error = 0;
    int intervals_n;
    int variant;
    double S = 0; // Integral value
    validateInput("%lf", &left_boundary_a, "\nEnter the left boundary \n X(first): ");
    validateInput("%lf", &right_boundary_b, "\nEnter the right boundary \n X(last): ");
    do {
        validateInput("%d", &intervals_n, "\nEnter the number of partition intervals (N>0)\nN=");
    } while (intervals_n <= 0);
    printf("%lf, %lf, %d", left_boundary_a, right_boundary_b, intervals_n);
    return 0;
}

unsigned int validateInput(const char* formatSpecifier, void* value, char message[]) {
    char input[100];

    printf(message);
    do {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, formatSpecifier, value) == 1) {
            return 1;
        } else {
            printf("\nInvalid input, try again");
            printf(message);
        }
    } while (1);
}