#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
uint32_t Least_common_multiple_euklides_extended(uint32_t a, uint32_t b, int32_t *x, int32_t *y);
int i_rand(int min, int max);
bool prime_number(uint32_t n);
uint32_t Least_common_multiple_euklides(uint32_t p, uint32_t q);
uint32_t mod_inverse(uint32_t e, uint32_t phi_n);
uint32_t finding_e(uint32_t lambda_n);
uint32_t carmichael_function(uint32_t a, uint32_t b);
int main(void)
{
    // we are picking the prime numbers (p i q)
    // we have to check, if is it a primie number so we write a function (prime_numer(int)), inside our function
    srand(time(NULL));
    uint32_t p;
    uint32_t q;
    do
    {
        p = i_rand(1000, UINT32_MAX);
    } while (!prime_number(p));

    do
    {

        q = i_rand(1000, UINT32_MAX);
    } while (!prime_number(q));
    printf("Sprawdzenie pobranych liczb p=%d oraz q=%d \n", p, q);
    uint32_t n = p * q;
    uint32_t lambda = carmichael_function(p, q);
    uint32_t e = finding_e(lambda);
    uint32_t d = mod_inverse(e, lambda);
    // klucz publiczny (n,e)
    // klucz prywatny (n,d)
    printf("Klucz publiczny (n,e)=(%d,%d) \n", n, e);
    printf("Klucz prywatny (n,d)=(%d,%d) \n", n, d);
    return 0;
}

int i_rand(int min, int max)
{
    return min + (rand() % (max - min + 1));
}
bool prime_number(uint32_t n)
{
    if (n < 2)
    {
        return true;
    }
    else
    {
        for (int i = 2; i < sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}
uint32_t Least_common_multiple_euklides(uint32_t a, uint32_t b)
{
    while (b != 0)
    {
        uint32_t c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int hamming_weight(int number) // is the number of symbols that are different from the zero-symbol
{
    int weight;
    while (number)
    {
        weight += number & 1;
        number >>= 1;
    }

    return weight;
}
uint32_t carmichael_function(uint32_t a, uint32_t b)
{
    uint32_t lambda_p = a - 1;
    uint32_t lambda_q = b - 1;
    return lambda_p * lambda_q / Least_common_multiple_euklides(lambda_p, lambda_q);
}
uint32_t finding_e(uint32_t lambda_n)
{
    uint32_t min_e = 64;
    uint32_t best_e = 0;
    for (uint32_t i = 3; i < lambda_n; i += 2)
    {
        if (Least_common_multiple_euklides(i, lambda_n) == 1)
        {
            int weight = hamming_weight(i);
            if (weight < min_e)
            {
                min_e = weight;
                best_e = i;
            }
        }
    }

    return best_e;
}
uint32_t Least_common_multiple_euklides_extended(uint32_t a, uint32_t b, int32_t *x, int32_t *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int32_t x1, y1; // zmienne pomocnicze
    uint32_t gcd = Least_common_multiple_euklides_extended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
uint32_t mod_inverse(uint32_t e, uint32_t phi_n)
{
    int32_t x, y;
    uint32_t gcd = Least_common_multiple_euklides_extended(e, phi_n, &x, &y);

    if (gcd != 1)
    {
        printf("Odwrotność modularna nie istnieje.(błąd)\n");
        return 0;
    }
    else
    {
        // Sprawdzenie, czy x>0.
        uint32_t result = (x % phi_n + phi_n) % phi_n;
        return result;
    }
}