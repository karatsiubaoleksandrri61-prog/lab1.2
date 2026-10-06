#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) 
{
    return (x-50.) * cos(x / 10) - 3. * x + 500.;
}

void print_border_line(void)
{
    printf("+");
    for (int i = 0; i < 11; i++) printf("-");
    printf("+");
    for (int i = 0; i < 22; i++) printf("-");
    printf("+");
    for (int i = 0; i < 26; i++) printf("-");
    printf("+\n");
}

int main()
{
    int input_variant = 0;
    double x1 = 0.0;
    double x2 = 0.0;
    double delta = 0.0;
    unsigned int n_points = 0;

    // Вибір варіанта введення
    do {
        printf("====================================================\n");
        printf("  LABORATORY WORK #1. VARIANT #16\n");
        printf("  Function: f(x) = (x - 50)*cos(x/10) - 3*x + 500\n");
        printf("====================================================\n");
        printf("Select input method:\n");
        printf("  1 - Enter X1, X2 and number of points N\n");
        printf("  2 - Enter X1, X2 and step delta\n");
        printf("Your choice (1 or 2): ");
        scanf("%d", &input_variant);

        if (input_variant != 1 && input_variant != 2) {
            printf("\n[ERROR] Invalid option! Please enter 1 or 2.\n\n");
        }
    } while (input_variant != 1 && input_variant != 2);

    // Введення меж
    do {
        printf("\nEnter start argument x1: ");
        scanf("%lf", &x1);
        printf("\nEnter start argument x2 (must be greater than X1): ");
        scanf("%lf", &x2);

        if (x2 <= x1)
        {
            printf("[ERROR] X2 must be strictly greater than X1!\n");
        }
    } while (x2 <= x1);

    // Розрахунок параметрів
    if (input_variant == 1)
    {
        do {
            printf("Enter number of points N (N => 2): ");
            scanf("%u", &n_points);
            if (n_points < 2)
            {
                printf("[ERROR] N must be a least 2! \n");
            }
        } while (n_points < 2);

        delta = (x2 - x1) / (double)(n_points - 1);
    } 
    else {
        do {
            printf("Enter step delta (delta > 0): ");
            scanf("%lf", &delta);
            if (delta <= 0. || delta > (x2 - x1)) 
            {
                printf("[ERROR] Delta must be > 0 and <= (X2 - X1)!\n");
            }
        } while (delta <= 0. || delta > (x2 - x1));

        n_points = (unsigned int)((x2 - x1) / delta) + 1;
    }

    printf("\nInitial parameter:\n");
    printf("X1 = %.4lf, X2 = %.4lf, delta = %.4lf, N = %u\n\n", x1, x2, delta, n_points);

    //Друк таблиці
    print_border_line();
    printf("|  Point N  |     Argument (X)     |     Function (F(X))      |\n");
    print_border_line();

    getchar();

    int page_size = 10;
    double prev_x = x1;
    double prev_y = f(x1);

    double root_a[100];
    double root_b[100];
    int sign_changes = 0;

    for (unsigned int i = 0; i < n_points; i++)
    {
        double current_x = x1 + i * delta;
        double current_y = f(current_x);

        // Перевірка зміни знака
        if (i > 0)
        {
            if (prev_y * current_y <= 0.)
            {
                root_a[sign_changes] = prev_x;
                root_b[sign_changes] = current_x;
                sign_changes++;
            }
        }

        // Виведення рядка
        printf("|%10u |%21.6lf |%25.6lf |\n", i + 1, current_x, current_y);
        print_border_line();

        prev_x = current_x;
        prev_y = current_y;

        // Посторінкове виведення
        if ((i + 1) % page_size == 0 && (i + 1) < n_points)
        {
            printf("Press ENTER to continue");
            getchar();
        }
    }

    // Виведення результатів пошуку коренів
    printf("\n=========================================================\n");
    printf("  Root isolation intervals:\n");
    printf("=========================================================\n");
    if (sign_changes == 0)
    {
        printf("  No sign change detected on the interval [%.2lf; %.2lf].\n", x1, x2);
    } 
    else {
        for (int var = 0; var < sign_changes; var++)
        {
            printf("  [%d] Root is between X = %.2lf and X = %.6lf\n", var + 1, root_a[var], root_b[var]);
        }
    }
    printf("=========================================================\n");

    return 0;
}