#include <math.h>
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
        validate_input("%d", &variant, "\nEnter method of integration"
                                       "\nLeft rectangles (1)"
                                       "\nRight rectangles (2)"
                                       "\nTrapezioid (3)"
                                       "\nParabola(4)\n");
        if (0 >= variant || 4 < variant) {
            printf("\nSelect 1, 2, 3 or 4.");
        }
    } while (variant != 1 && variant != 2 && variant !=3 && variant != 4);
    // system("cls");

    switch (variant) {
        case 1:
            // integral_S = calculate_integral_left_rectangles(left_boundary_a, right_boundary_b, intervals_n);
            l1 = calculate_integral_left_rectangles(left_boundary_a, right_boundary_b, intervals_n);
            for (int i = 0; i < 2; i++) {
                if (i == 1) {
                    intervals_n += 2;
                    l2 = calculate_integral_left_rectangles(left_boundary_a, right_boundary_b, intervals_n);
                    if (fabs(l1 - l2) <= measurement_error) {
                        break;
                    }
                } else {
                    i = 0;
                }
            }
            printf("L1: %lf", l1);
            printf("L2: %lf", l2);
            // printf("L1: %lf", l1);
            //
            // while (1) {
            //     intervals_n += 2;
            //     l2 = calculate_integral_left_rectangles(left_boundary_a, right_boundary_b, intervals_n);
            //     if (fabs(l1 - l2) <= measurement_error) {
            //         break;
            //     }
            //     printf("L2: %lf", l2);
            // }
            // printf("L1: %lf, L2: %lf", l1, l2);
            break;
        case 2:
            integral_S = calculate_integral_right_rectangles(left_boundary_a, right_boundary_b, intervals_n);
            break;
        case 3:
            integral_S = calculate_integral_trapezium(left_boundary_a, right_boundary_b, intervals_n);
            break;
        case 4:
            integral_S = calculate_integral_parabola(left_boundary_a, right_boundary_b, intervals_n);
            break;
    }

    // printf("%lf", integral_S);
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
double calculate_integral_right_rectangles(double left_boundary_a, double right_boundary_b, int intervals_n) {
    // n - amount of rectangles, a - lower border of integrating, b - higher border of integrating
    double h = (right_boundary_b - left_boundary_a) / intervals_n; // (b - a) / n - step
    double sum = 0.0;

    for (int i = 1; i <= intervals_n; i++) {
        sum += function_for_integration(left_boundary_a + i * h); // X value in left border of integration
    }

    return sum * h;
}
double calculate_integral_trapezium(double left_boundary_a, double right_boundary_b, int intervals_n) {
    // n - amount of rectangles, a - lower border of integrating, b - higher border of integrating
    double h = (right_boundary_b - left_boundary_a) / intervals_n; // (b - a) / n - step
    double sum = 0.0;

    sum += (function_for_integration(left_boundary_a) + function_for_integration(right_boundary_b)) / 2; // add first and last values

    for (int i = 1; i <= intervals_n; i++) {
        sum += function_for_integration(left_boundary_a + i * h); // X value in left border of integration
    }

    return sum * h;
}
double calculate_integral_parabola(double left_boundary_a, double right_boundary_b, int intervals_n) {
    if (intervals_n % 2 != 0) {
        intervals_n++; // amount of intervals should be even
    }

    double h = (right_boundary_b - left_boundary_a) / intervals_n; // define step
    double sum = function_for_integration(left_boundary_a) + function_for_integration(right_boundary_b); // adding first and last values

    for (int i = 1; i < intervals_n; i += 2) {
        sum += 4 * function_for_integration(left_boundary_a + i * h); //adding all odd values except first and last
    }

    for (int i = 2; i < intervals_n - 1; i += 2) {
        sum += 2 * function_for_integration(left_boundary_a + i * h); //adding all even values except last and first
    }

    return (sum * h) / 3;
}



