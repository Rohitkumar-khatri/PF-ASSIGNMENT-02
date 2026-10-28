
#include <stdio.h>

int sumDivisors(int num)
{
    int i, sum = 0;

    for (i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)
            sum += i;
    }

    return sum;
}

int main()
{
    int n, i, a, b, count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for (i = 2; i <= n; i++)
    {
        a = sumDivisors(i);

        if (a > i && a <= n)
        {
            b = sumDivisors(a);

            if (b == i)
            {
                printf("(%d, %d)\n", i, a);
                count++;
            }
        }
    }

    if (count == 0)
        printf("No amicable pairs found.\n");

    printf("Total pairs: %d\n", count);

    return 0;
}
