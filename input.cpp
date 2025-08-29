#include <assert.h>
#include <stdio.h>
#include "square_solver.h"
/*!
Принимает коэффициенты из стандартного ввода и загружает их в структуру
\param[in] coefficients - указатель на структуру для коэффициентов
\return void-функция
*/
void input_coefficients(coefficients_data* coefficients)
{
    assert (coefficients);

    input_coefficient(&coefficients->coefficient_a, "Input X^2 coefficient: ");

    input_coefficient(&coefficients->coefficient_b, "Input X coefficient: ");

    input_coefficient(&coefficients->coefficient_c, "Input free coefficient: ");

    return;
}
/*!
Выводит текст, указывающий, какой нужно ввести коэффициент, и вводит его, проверяя, число это или нет
\param[in] coefficient - указатель на структуру для коэффициента
\param[in] output - постоянный указатель на строку, в который написано, какой нужно ввести коэффициент
\return - void-функция
*/
void input_coefficient(double* coefficient, const char* const output)
{
    assert (coefficient);
    assert (output);

    printf("%s", output);

    int is_number = -1;

    while ((is_number = scanf("%lf", coefficient)) != 1 || check_buffer_not_clear())
    {
        printf("Input number!\n");
        clean_buffer();
    }

    return;
}
/*!
Чистит буфер
return - void-функция
*/
void clean_buffer(void)
{
    while (getchar() != '\n')
    {
        continue;
    }

    return;
}
/*!
Проверяет, есть ли в буфере что-то кроме пробельных символов
return: true если есть непробельный символ
        false если только пробельные символы
*/
bool check_buffer_not_clear(void)
{
    int symbol = ' ';
    while ((symbol = getchar()) != '\n')
    {
        if  (symbol != '\n' && symbol != ' ' && symbol != EOF)
        {
            return true;
        }
    }

    return false;
}
