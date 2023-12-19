#include <stdio.h>
#include <string.h>
#include <conio.h>

void getPassword(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == '\r') {
            password[i] = '\0'; // removing null from the array
            break;
        } else if (ch == '\b' && i > 0) { //removing backspace if pressed
            i--;
            printf("\b \b");
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
}
struct contact // storing name, phone and email in phonebook
{
    char name[50];
    char phone[20];
    char email[50];
};

struct contact phonebook[1000]; // global variable for accessing
int numContacts = 0; // global variable for accessing

void displayMenu()
{
    printf("\nSelect an option:\n");
    printf("1. Add a contact\n");
    printf("2. Delete a contact\n");
    printf("3. Search for a contact\n");
    printf("4. Print phonebook\n");
    printf("0. Exit\n");
    printf("\nPlease Enter Your Choice: ");
    return ;
}

void addContact(struct contact newContact) // function to add contact
{
    phonebook[numContacts] = newContact; // storing contacts in a structure array
    numContacts++;
    printf("Contact added successfully!\n");

    // Write new contact to file
    FILE* fp = fopen("PhoneBook.txt", "a"); // saving new contact to file
    if (fp != NULL)
    {
        fprintf(fp, "%s\t%s\t%s\n", newContact.name, newContact.phone, newContact.email);
        fclose(fp);
    }
    else
    {
        printf("Failed to open file for writing.\n");
    }
}

void deleteContact(char* name) {
    int i, j;
    int found = 0;

    for (i = 0; i < numContacts; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            found = 1;
            for (j = i; j < numContacts - 1; j++) {
                phonebook[j] = phonebook[j + 1];
            }
            numContacts--;
            printf("Contact deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
        return;
    }

    FILE* fp = fopen("PhoneBook.txt", "w");
    if (fp != NULL) {
        for (i = 0; i < numContacts; i++) {
            fprintf(fp, "%s\t%s\t%s\n", phonebook[i].name, phonebook[i].phone, phonebook[i].email);
        }
        fclose(fp);
    } else {
        printf("Failed to open file for writing.\n");
    }
}

struct contact searchContact(char* name)
{
    FILE* fp = fopen("PhoneBook.txt", "r");
    struct contact foundContact = {"", "", ""};
    while (fscanf(fp, "%s %s %s", foundContact.name, foundContact.phone, foundContact.email) == 3)
    {
        if (strcmp(foundContact.name, name) == 0)
        {
            fclose(fp);
            return foundContact;
        }
    }
    fclose(fp);
    printf("Contact not found!\n");
    return foundContact;
}

void print_phonebook()
{
    if (numContacts == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    printf("Phonebook Entries:\n");
    printf("Name\tPhone\tEmail\n");
    for (int i = 0; i < numContacts; i++)
    {
        printf("%s\t%s\t%s\n", phonebook[i].name, phonebook[i].phone, phonebook[i].email);
    }
}

int comparePasswords(const char *enteredPassword, const char *correctPassword) {
    return strcmp(enteredPassword, correctPassword);
}

int main()
{
    const char *correctPassword = "1234"
    char enteredPassword[5];

    printf("Welcome to Your Phonebook\n\n");
    printf("Enter 4 digit Password to access Phonebook: ");
    getPassword(enteredPassword);

    while (comparePasswords(enteredPassword, correctPassword) != 0)
    {
        printf("\nInvalid Password.\n"); // showing prompt messages
        printf("Please enter the Password to try again.\n\n");
        printf("Enter Password to Continue: ");
        getPassword(enteredPassword);
    }

    system("cls"); // clearing output for fresh phonebook look
    printf("\n\n******Welcome to Phonebook******\n\n");
    int choice;

    FILE *fp = fopen("PhoneBook.txt", "r");
    if (fp == NULL)
    {
        printf("Failed to open file for reading.\n");
        return 1;
    }

    // read contacts from file
    while (numContacts < 1000 && fscanf(fp, "%s %s %s", phonebook[numContacts].name, phonebook[numContacts].phone, phonebook[numContacts].email) != EOF)
    {
        numContacts++;
    }
    fclose(fp);

    do
    {

        displayMenu(); // calling display function to show prompt

        scanf("%d", &choice);

        switch(choice)
        {
        case 1: // for adding contacts
        {
            if (numContacts < 1000)
            {
                struct contact newContact;
                printf("Enter contact name: ");
                scanf("%s", newContact.name);
                printf("Enter contact phone: ");
                scanf("%s", newContact.phone);
                printf("Enter contact email: ");
                scanf("%s", newContact.email);
                addContact(newContact);
            }
            else
            {
                printf("Phonebook is full!\n");
            }
            break;
        }
        case 2: // for deleting contacts
        {
            char name[50];
            printf("Enter name of contact to delete: ");
            scanf("%s", name);
            deleteContact(name);
            break;
        }
        case 3: // for searching contacts
        {
            char name[50];
            printf("Enter name of contact to search: ");
            scanf("%s", name);
            struct contact result = searchContact(name);
            if (strlen(result.name) > 0)
            {
                printf("%s | %s | %s\n", result.name, result.phone, result.email);
            }
            break;
        }
        case 4: // for printing phonebook
        {
            print_phonebook();
            break;
        }
        case 0: // for exiting phonebook
        {
            printf("Exiting phonebook...\n");
            break;
        }
        default: // if any invalid key is pressed
        {
            printf("Invalid option!\n");
            break;
        }
        }
    }
    while (choice != 0);

    return 0;
}
