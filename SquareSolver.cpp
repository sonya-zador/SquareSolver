#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-9

enum number_of_roots {ZERO_ROOTS = 0, ONE_ROOT = 1, TWO_ROOTS = 2, INFINITE_NUMBER_OF_ROOTS = 100};
const int NUMBEROFTESTS = 5;

struct coefficient{
    double a;
    double b;
    double c;
};

struct roots{
    double p;
    double q;
    number_of_roots num_roots;
};

struct tests{
    struct coefficient coef;
    struct roots root;
    int test_number;
};


void input(coefficient * coef_ptr);
void Clean();
int Counting_the_coefficient(double * coef_counting);
number_of_roots solve(const coefficient coef, roots * root_ptr);
void output(roots root);
bool is_zero(const double a);
void test();
void solve_test(coefficient coef, roots root, int test_number);
bool double_are_equal(const double double_1, const double double_2);


int main (void)
{
    struct coefficient coef = {};
    struct roots root = {};
    input(&coef);
    root.num_roots = solve(coef, &root);
    output(root);

    test();

    return 0;
}

void input(coefficient * coef_ptr)
{
    assert(coef_ptr != NULL);

    printf("Введите коэффициенты каждый с новой строки\n");

    int right_coefficient = Counting_the_coefficient(&(*coef_ptr).a) +
                            Counting_the_coefficient(&(*coef_ptr).b) +
                            Counting_the_coefficient(&(*coef_ptr).c);

    assert(right_coefficient == 3);
    ;
}

void Clean()
{
    while (getchar() != '\n')
    ;
}



int Counting_the_coefficient(double * coef_counting)
{
    int number_of_attempts = 3;
    while (number_of_attempts > 0)
    {
        if (scanf("%lf", &(*coef_counting)) == 1)
        {
            if (getchar() == '\n')
            {
                return 1;
            }
            else
            {
                Clean();
                number_of_attempts--;
                printf("Коэффициент введен неверно, попробуйте ввести его снова. Осталось попыток: %d.\n", number_of_attempts);
            }
        }
        else
        {
            Clean();
            number_of_attempts--;
            printf("Коэффициент введен неверно, попробуйте ввести его снова. Осталось попыток: %d.\n", number_of_attempts);
        }
    }
    assert(number_of_attempts > 0);
    return 0;

}

number_of_roots solve(const coefficient coef, roots * root_ptr)
{
    if (is_zero(coef.a))
    {
        if (is_zero(coef.b))
        {
            if (is_zero(coef.c))
            {
                return INFINITE_NUMBER_OF_ROOTS;
            }
            else
                return ZERO_ROOTS;
        }
        else
        {
            (*root_ptr).p = -coef.c / coef.b;
            return ONE_ROOT;
        }
    }

    else
    {
        const double D = coef.b * coef.b - 4 * coef.a * coef.c;
        if (D > EPS)
        {
            double sqrt_D = sqrt(D);
            (*root_ptr).q = (-coef.b + sqrt_D) / (2 * coef.a);
            (*root_ptr).p = (-coef.b - sqrt_D) / (2 * coef.a);
            return TWO_ROOTS;
        }
        else if (is_zero(D))
        {
            (*root_ptr).p = (-coef.b) / (2 * coef.a);
            return ONE_ROOT;
        }
        else
            return ZERO_ROOTS;
    }
}

void output(roots root)
{
    if (root.num_roots == 0)
    {
        printf("Корней нет\n");
    }
    else if (root.num_roots == 1)
    {
        printf("%lf\n", root.p);
    }
    else if (root.num_roots == 2)
    {
        printf("%lf %lf\n", root.p, root.q);
    }
    else if (root.num_roots == 100)
    {
        printf("Бесконечное множество корней\n");
    }
    return;
}
bool is_zero(const double a)
{
    if (fabs(a) < EPS)
        return true;
    else
        return false;
}

void test()
{
    const struct tests root_tests[NUMBEROFTESTS] =
    {  // a,   b,    c,   x1, x2, num_roots,  #
        {{1,   2,   -3}, {-3, 1, TWO_ROOTS},  1},
        {{0,   2,  -10}, { 5, 0, ONE_ROOT},   2},
        {{0,   0,  -10}, { 0, 0, ZERO_ROOTS}, 3},
        {{3.6, 2, 10.4}, { 0, 0, ZERO_ROOTS}, 4},
        {{-1,  7,  -10}, { 5, 2, TWO_ROOTS},  5}
    };
    for (int i = 0; i < NUMBEROFTESTS; i++)
        solve_test(root_tests[i].coef, root_tests[i].root, root_tests[i].test_number);
    return;
}

void solve_test(const coefficient coef, const roots root_correct, const int test_number)
{
    struct roots root_test = {};

    number_of_roots num_roots_test = solve(coef, &root_test);

    if (double_are_equal(root_correct.num_roots, num_roots_test) && double_are_equal(root_test.p, root_correct.p) && double_are_equal(root_test.q, root_correct.q))
        printf("Тест %d пройден успешно.\n", test_number);
    else
        printf("Тест %d не пройден.\n", test_number);
    return;
}
bool double_are_equal(const double double_1, const double double_2)
{
    if (fabs(double_1 - double_2) < EPS)
        return true;
    else
        return false;
}
