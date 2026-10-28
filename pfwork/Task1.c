
#include <stdio.h>

int main()
{
    int seats[100][100];
    int rows, cols, k;
    int i, j, d, r;
    int mid, count, start, found = 0;
    int bookedRow = -1, bookedSeat = -1;
    int total = 0;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter seats per row: ");
    scanf("%d", &cols);

    if (rows < 1 || rows > 100 || cols < 1 || cols > 100)
    {
        printf("Invalid size");
        return 0;
    }

    printf("Enter seating plan:\n");

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            do
            {
                scanf("%d", &seats[i][j]);
            } while (seats[i][j] != 0 && seats[i][j] != 1);
        }
    }

    printf("\nSeating Arrangement:\n");

    printf("   ");
    for (j = 0; j < cols; j++)
        printf("%d ", j);
    printf("\n");

    for (i = 0; i < rows; i++)
    {
        printf("R%d ", i);

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("\nAvailable seats:\n");

    for (i = 0; i < rows; i++)
    {
        count = 0;

        for (j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
                count++;
        }

        printf("Row %d: %d\n", i, count);
        total += count;
    }

    printf("Total available seats: %d\n", total);

    printf("\nEnter group size: ");
    scanf("%d", &k);

    if (k <= 0 || k > cols)
    {
        printf("Invalid group size");
        return 0;
    }

    mid = rows / 2;

    for (d = 0; d < rows && found == 0; d++)
    {
        for (r = 0; r < rows && found == 0; r++)
        {
            if (r == mid - d || r == mid + d)
            {
                count = 0;

                for (j = 0; j < cols; j++)
                {
                    if (seats[r][j] == 0)
                        count++;
                    else
                        count = 0;

                    if (count == k)
                    {
                        start = j - k + 1;
                        bookedRow = r;
                        bookedSeat = start;
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    if (found == 1)
    {
        for (j = bookedSeat; j < bookedSeat + k; j++)
            seats[bookedRow][j] = 1;

        printf("\nBooking successful!\n");
        printf("Row: %d\n", bookedRow);
        printf("Seats: ");

        for (j = bookedSeat; j < bookedSeat + k; j++)
            printf("%d ", j);

        printf("\n\nUpdated Seating Plan:\n");

        printf("   ");
        for (j = 0; j < cols; j++)
            printf("%d ", j);
        printf("\n");

        total = 0;

        for (i = 0; i < rows; i++)
        {
            printf("R%d ", i);

            for (j = 0; j < cols; j++)
            {
                if (seats[i][j] == 0)
                {
                    printf("_ ");
                    total++;
                }
                else
                    printf("X ");
            }
            printf("\n");
        }

        printf("Remaining available seats: %d\n", total);
    }
    else
    {
        printf("No consecutive seats available.\n");
    }

    return 0;
}
