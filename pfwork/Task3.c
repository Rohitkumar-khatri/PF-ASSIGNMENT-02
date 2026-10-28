
#include <stdio.h>

void inputReadings(int temp[][100], int sensors, int hours)
{
    int i, j;

    for (i = 0; i < sensors; i++)
    {
        printf("\nSensor %d:\n", i + 1);

        for (j = 0; j < hours; j++)
        {
            printf("Hour %d: ", j + 1);
            scanf("%d", &temp[i][j]);
        }
    }
}

void analyzeSensor(int readings[], int hours, int sensor)
{
    int i, total = 0;
    int highest = readings[0];
    int lowest = readings[0];
    int critical = 0, warning = 0;
    int streak = 0, longest = 0;
    float average;

    for (i = 0; i < hours; i++)
    {
        total += readings[i];

        if (readings[i] > highest)
            highest = readings[i];

        if (readings[i] < lowest)
            lowest = readings[i];

        if (readings[i] >= 40)
            critical++;
        else if (readings[i] >= 35 && readings[i] <= 39)
            warning++;

        if (readings[i] >= 35)
        {
            streak++;

            if (streak > longest)
                longest = streak;
        }
        else
        {
            streak = 0;
        }
    }

    average = (float)total / hours;

    printf("\nSensor %d Report\n", sensor);
    printf("Total: %d\n", total);
    printf("Average: %.2f\n", average);
    printf("Highest: %d\n", highest);
    printf("Lowest: %d\n", lowest);
    printf("Critical: %d\n", critical);
    printf("Warning: %d\n", warning);
    printf("Longest hot streak: %d\n", longest);
}

int highestAverage(int temp[][100], int sensors, int hours)
{
    int i, j, total;
    int highestSensor = 0;
    float average, maxAverage = 0;

    for (i = 0; i < sensors; i++)
    {
        total = 0;

        for (j = 0; j < hours; j++)
            total += temp[i][j];

        average = (float)total / hours;

        if (i == 0 || average > maxAverage)
        {
            maxAverage = average;
            highestSensor = i;
        }
    }

    return highestSensor;
}

int main()
{
    int temp[100][100];
    int sensors, hours;
    int i, j, best, total = 0;
    float average;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);

    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    if (sensors < 1 || sensors > 100 || hours < 1 || hours > 100)
    {
        printf("Invalid input");
        return 0;
    }

    inputReadings(temp, sensors, hours);

    for (i = 0; i < sensors; i++)
        analyzeSensor(temp[i], hours, i + 1);

    best = highestAverage(temp, sensors, hours);

    for (j = 0; j < hours; j++)
        total += temp[best][j];

    average = (float)total / hours;

    printf("\nHighest Average Sensor: %d\n", best + 1);
    printf("Average Temperature: %.2f\n", average);

    return 0;
}
