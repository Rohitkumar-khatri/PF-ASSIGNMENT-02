
#include <stdio.h>

int getValidDays()
{
    int days;

    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);

        if (days < 1 || days > 7)
            printf("Invalid number of days.\n");

    } while (days < 1 || days > 7);

    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0;
    float highest = 0, average;

    printf("\nDay %d\n", dayNumber);

    printf("Enter number of orders: ");
    scanf("%d", &orders);

    for (i = 1; i <= orders; i++)
    {
        do
        {
            printf("Enter amount for order %d: ", i);
            scanf("%f", &amount);

            if (amount <= 0)
                printf("Amount must be greater than zero.\n");

        } while (amount <= 0);

        total += amount;

        if (amount > highest)
            highest = amount;
    }

    average = total / orders;

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", average);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, highestDay = 0;

    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[highestDay])
            highestDay = i;
    }

    return highestDay + 1;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;

    printf("\nDAILY SALES BAR CHART\n");

    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);

        printf("Day %d: ", i + 1);

        for (j = 0; j < stars; j++)
            printf("*");

        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main()
{
    float dailySales[7];
    float festivalTotal = 0;
    int days, i, highestDay;

    days = getValidDays();

    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    highestDay = findHighestSalesDay(dailySales, days);

    printf("\nFESTIVAL SUMMARY\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n",
           dailySales[highestDay - 1]);

    displayBarChart(dailySales, days);

    return 0;
}
