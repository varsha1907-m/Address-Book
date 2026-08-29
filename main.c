#include <stdio.h>
#include "contact.h"
#include <stdlib.h>


int main() 
{
    int choice;
    AddressBook addressBook;

    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book

    do
    {
        system("clear");
        
        printf("\n============================================================\n");
        printf("                     ADDRESS BOOK\n");
        printf("============================================================\n\n");
        
        printf("                 1. Create Contact\n");
        printf("                 2. Search Contact\n");
        printf("                 3. Edit Contact\n");
        printf("                 4. Delete Contact\n");
        printf("                 5. List All Contacts\n");
        printf("                 6. Save & Exit\n");
        printf("                 7. Exit\n");
        
        printf("\n------------------------------------------------------------\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                system("clear");
                printf("\n============================================================\n");
                printf("                     SAVE & EXIT\n");
                printf("============================================================\n\n");
            
                saveContactsToFile(&addressBook);
            
                printf("\nThank you for using Address Book!\n");
                printf("============================================================\n");
                return 0;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
