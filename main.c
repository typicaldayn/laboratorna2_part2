#include <stdio.h>
#include <stdlib.h>

// Variant 1 Integral(0,1) (1 / 4 + x^2)dx
unsigned int validate_input(const char* formatSpecifier, void* value, char message[]);
double calculate_integral_left_rectangles(double left_boundary_a, double right_boundary_b, int intervals_n);
double calculate_integral_right_rectangles(double left_boundary_a, double right_boundary_b, int intervals_n);
double calculate_integral_trapezium(double left_boundary_a, double right_boundary_b, int intervals_n);
double calculate_integral_parabola(double left_boundary_a, double right_boundary_b, int intervals_n);
double function_for_integration(double x);

int main(void) {
    double left_boundary_a;
    double right_boundary_b;
    double measurement_error = 0;
    double l1, l2 = 0; //l1 - for n intervals, l2 - for n + 2 intervals
    int intervals_n;
    unsigned int variant;
    double integral_S = 0; // Integral value

    validate_input("%lf", &left_boundary_a, "\nEnter the left boundary \n X(first): ");
    validate_input("%lf", &right_boundary_b, "\nEnter the right boundary \n X(last): ");

    do { // Validating measurement error
        validate_input("%lf", &measurement_error, "\nEnter measurement error of integration.\nMeasurement error=");

        if (measurement_error < 0) {
            printf("\nIntegration error can't be lower than 0");
        }
    } while (measurement_error < 0);

    do { // Validating intervals value
        validate_input("%d", &intervals_n, "\nEnter the number of partition intervals (N>0)\nN=");
    } while (intervals_n <= 0);

    do {
        if (0 >= variant || 4 < variant) {
            printf("\nSelect 1, 2 or 3.");
        }
        validate_input("%d", &variant, "\nEnter method of integration"
                                       "\nLeft rectangles (1)"
                                       "\nRight rectangles (2)"
                                       "\nTrapezioid (3)"
                                       "\nParabola(4)\n");
    } while (variant != 1 && variant != 2 && variant !=3 && variant != 4);
    system("cls");

    printf("%lf = Result", integral_S);
    return 0;
}

double function_for_integration(double x) {
    return 1.0 / (4 - x * x);
}

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]) {
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

double calculate_integral_left_rectangles(double left_boundary_a, double right_boundary_b, int intervals_n) {
    // n - amount of rectangles, a - lower border of integrating, b - higher border of integrating
    double h = (right_boundary_b - left_boundary_a) / intervals_n; // (b - a) / n - step
    double sum = 0.0;

    for (int i = 0; i < intervals_n; i++) {
        sum += function_for_integration(left_boundary_a + i * h); // X value in left border of integration
    }

    return sum * h;
}
