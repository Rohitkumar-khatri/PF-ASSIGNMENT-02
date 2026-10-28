
#include <stdio.h>
#include <string.h>

void displayMenu()
{
    printf("\n===== LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do
    {
        printf("1. Student\n");
        printf("2. Faculty\n");
        printf("Enter membership type: ");
        scanf("%d", memberType);

        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type.\n");

    } while (*memberType != 1 && *memberType != 2);

    printf("Registration successful.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks)
{
    int i;

    printf("\nID\tTitle\t\t\tCopies\n");

    for (i = 0; i < totalBooks; i++)
    {
        printf("%d\t%-24s%d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50],
                int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int id, days, i, found = -1;

    if (*borrowedCount >= 3)
    {
        printf("You cannot borrow more than 3 books.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    printf("Enter intended number of days: ");
    scanf("%d", &days);

    if (days <= 0)
    {
        printf("Invalid number of days.\n");
        return;
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[found] == 0)
    {
        printf("Book is not available.\n");
        return;
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[found]--;

    printf("Book borrowed successfully.\n");

    if (memberType == 1)
        printf("Allowed borrowing period: 14 days\n");
    else
        printf("Allowed borrowing period: 30 days\n");

    printf("Book: %s\n", bookTitles[found]);
}

float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id, days, i, bookIndex = -1;
    int borrowIndex = -1, allowedDays;
    float fine = 0, payable;
    char code[30];

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            borrowIndex = i;
            break;
        }
    }

    if (borrowIndex == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            bookIndex = i;
            break;
        }
    }

    do
    {
        printf("Enter actual number of days: ");
        scanf("%d", &days);

        if (days <= 0)
            printf("Days must be positive.\n");

    } while (days <= 0);

    if (memberType == 1)
        allowedDays = 14;
    else
        allowedDays = 30;

    if (days > allowedDays)
    {
        if (memberType == 1)
            fine = (days - allowedDays) * 20;
        else
            fine = (days - allowedDays) * 10;
    }

    *totalFine += fine;
    payable = fine;

    printf("Fine before waiver: Rs. %.2f\n", fine);

    printf("Enter membership code: ");
    scanf("%29s", code);

    if (strcmp(code, "LIB2026") == 0)
    {
        payable = fine * 0.5;
        printf("50 percent waiver applied.\n");
    }
    else
    {
        printf("No waiver applied.\n");
    }

    availableCopies[bookIndex]++;

    for (i = borrowIndex; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];

    (*borrowedCount)--;

    printf("Book returned successfully.\n");
    printf("Fine payable: Rs. %.2f\n", payable);

    return payable;
}

void displayMemberRecord(char name[], int studentID,
                         int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine,
                         float fineAfterWaiver)
{
    int i;

    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1)
        printf("Membership Type: Student\n");
    else
        printf("Membership Type: Faculty\n");

    printf("Currently Borrowed Books: %d\n", borrowedCount);

    if (borrowedCount == 0)
        printf("No books borrowed.\n");
    else
    {
        for (i = 0; i < borrowedCount; i++)
            printf("Book ID: %d\n", borrowedBookIDs[i]);
    }

    printf("Total fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[4] = {101, 102, 103, 104};

    char bookTitles[4][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };

    int availableCopies[4] = {5, 3, 0, 4};

    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    int choice, registered = 0;
    float totalFine = 0;
    float fineAfterWaiver = 0;
    float currentFine;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (borrowedCount > 0)
                {
                    printf("Return borrowed books before new registration.\n");
                }
                else
                {
                    registerMember(name, &studentID, &memberType);
                    registered = 1;
                    totalFine = 0;
                    fineAfterWaiver = 0;
                }
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, 4);
                break;

            case 3:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    borrowBook(bookIDs, bookTitles, availableCopies,
                               4, borrowedBookIDs, &borrowedCount,
                               memberType);
                break;

            case 4:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                {
                    currentFine = returnBook(bookIDs, availableCopies,
                                             4, borrowedBookIDs,
                                             &borrowedCount,
                                             memberType, &totalFine);

                    fineAfterWaiver += currentFine;
                }
                break;

            case 5:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    displayMemberRecord(name, studentID, memberType,
                                        borrowedBookIDs, borrowedCount,
                                        totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("Exiting Library System.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}
