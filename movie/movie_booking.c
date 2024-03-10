#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie
{
    char name[50];
    char director[50];
    char genre[20];
    int rating;
    int release_year;
};

struct booking
{
    char name[50];
    char email[50];
    char phone[20];
    char movie_name[50];
    int num_tickets;
    int total_price;
};

void display_movies();
void register_user();
void book_ticket();
void cancel_ticket();
void display_bookings();
void add_movie();

int main()
{
    int choice;

    while (1)
    {
        printf("Welcome to Movie Ticket Booking System\n");
        printf("1. Display Movies\n");
        printf("2. Register User\n");
        printf("3. Book Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Display Bookings\n");
        printf("6. Add Movie\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_movies();
            break;
        case 2:
            register_user();
            break;
        case 3:
            book_ticket();
            break;
        case 4:
            cancel_ticket();
            break;
        case 5:
            display_bookings();
            break;
        case 6:
            add_movie();
            break;

        case 7:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

void display_movies()
{
    FILE *fp;
    struct movie m;

    fp = fopen("movies.txt", "rb");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Movie Name\t\tDirector\t\tGenre\t\tRating\tRelease Year\n");

    while (fread(&m, sizeof(struct movie), 1, fp))
    {
        printf("%-24s%-22s%-18s%-12d%d\n", m.name, m.director, m.genre, m.rating, m.release_year);
    }

    fclose(fp);
}

void register_user()
{
    FILE *fp;
    char name[50], email[50], phone[20];

    fp = fopen("users.txt", "ab");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your phone: ");
    scanf("%s", phone);

    fwrite(name, sizeof(char), strlen(name) + 1, fp);
    fwrite(email, sizeof(char), strlen(email) + 1, fp);
    fwrite(phone, sizeof(char), strlen(phone) + 1, fp);

    printf("User registered successfully!\n");

    fclose(fp);
}

void book_ticket()
{
    FILE *fp1, *fp2;
    char name[50], email[50], phone[20], movie_name[50];
    int num_tickets, total_price;
    struct movie m;
    struct booking b;

    fp1 = fopen("movies.txt", "rb");

    if (fp1 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fp2 = fopen("booking.txt", "ab");

    if (fp2 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter your name: ");
    scanf("%s", b.name);
    printf("Enter your email: ");
    scanf("%s", b.email);
    printf("Enter your phone: ");
    scanf("%s", b.phone);
    printf("Enter movie name: ");
    scanf("%s", b.movie_name);
    printf("Enter number of tickets: ");
    scanf("%d", &b.num_tickets);
    while (fread(&m, sizeof(struct movie), 1, fp1))
    {
        if (strcmp(m.name, b.movie_name) == 0)
        {
            total_price = b.num_tickets * 100; // Assuming ticket price to be 100
            printf("Total Price: %d\n", total_price);

            strcpy(b.name, name);
            strcpy(b.email, email);
            strcpy(b.phone, phone);
            b.total_price = total_price;

            fwrite(&b, sizeof(struct booking), 1, fp2);
            printf("Ticket booked successfully!\n");
            break;
        }
    }

    if (feof(fp1))
    {
        printf("Movie not found!\n");
    }

    fclose(fp1);
    fclose(fp2);
}
void add_movie() {
    FILE *fp;
    struct movie m;

    fp = fopen("movies.txt", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter movie name: ");
    scanf("%s", m.name);
    printf("Enter director name: ");
    scanf("%s", m.director);
    printf("Enter genre: ");
    scanf("%s", m.genre);
    printf("Enter rating (out of 10): ");
    scanf("%d", &m.rating);
    printf("Enter release year: ");
    scanf("%d", &m.release_year);

    fwrite(&m, sizeof(struct movie), 1, fp);

    printf("Movie added successfully!\n");

    fclose(fp);
}

void cancel_ticket()
{
    FILE *fp1, *fp2;
    char name[50], email[50], phone[20], movie_name[50];
    int num_tickets, total_price;
    struct booking b;
    fp1 = fopen("booking.txt", "rb");
    if (fp1 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fp2 = fopen("temp.txt", "wb");

    if (fp2 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your phone: ");
    scanf("%s", phone);
    printf("Enter movie name: ");
    scanf("%s", movie_name);
    printf("Enter number of tickets: ");
    scanf("%d", &num_tickets);

    while (fread(&b, sizeof(struct booking), 1, fp1))
    {
        if (strcmp(b.name, name) == 0 && strcmp(b.email, email) == 0 && strcmp(b.phone, phone) == 0 && strcmp(b.movie_name, movie_name) == 0 && b.num_tickets == num_tickets)
        {
            total_price = b.total_price;
            printf("Total Refund Amount: %d\n", total_price);
        }
        else
        {
            fwrite(&b, sizeof(struct booking), 1, fp2);
        }
    }

    if (feof(fp1))
    {
        printf("Ticket not found!\n");
    }

    fclose(fp1);
    fclose(fp2);

    remove("booking.txt");
    rename("temp.txt", "booking.txt");
}

void display_bookings()
{
    FILE *fp;
    struct booking b;
    fp = fopen("booking.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Name\t\tEmail\t\t\tPhone\t\tMovie Name\t\tNum Tickets\tTotal Price\n");

    while (fread(&b, sizeof(struct booking), 1, fp))
    {
        printf("%-15s%-25s%-20s%-20s%-12d%d\n", b.name, b.email, b.phone, b.movie_name, b.num_tickets, b.total_price);
    }

    fclose(fp);
}
