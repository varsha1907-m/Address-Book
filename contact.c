#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    // // Bubble sort

    system("clear");
    
    printf("\n============================================================\n");
    printf("                    CONTACT LIST\n");
    printf("============================================================\n\n");
    int i,j;
    int choice;

    if(addressBook->contactCount == 0)
    {
        printf("No contacts found\n");
        return;
    }

    printf("Sort by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice\n");

    scanf("%d",&choice);

    if(choice < 1 || choice > 3)
    {
        printf("Invalid sorting choice\n");
        return;
    }

    for(i=0; i<addressBook->contactCount-1; i++)
    {
        for(j=0; j<addressBook->contactCount-1-i; j++)
        {
            if(choice==1)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp;
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
            else if(choice==2)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp;
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
            else if(choice==3)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp;
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
    }
    
    printf("%-5s %-20s %-12s %s\n","No.", "Name", "Phone", "Email");
    
    printf("------------------------------------------------------------\n");
    
    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-12s %s\n",i + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
    }
    printf("------------------------------------------------------------\n");

    pressEnterToContinue();
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  //  populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *str1)
{
    int i;
    if(str1[0] == '\0')
    {
        return 0;
    }
    for(i=0; str1[i] != 0; i++)
    {
        if(!(str1[i]>='a' && str1[i]<='z' || 
            str1[i]>='A' && str1[i]<='Z' || 
            str1[i]==' ' || str1[i]=='.'))
        {
            return 0;
        }
    }
    return 1;
}

int validate_number(char *str2)
{
    int i=0;
    while(str2[i] != 0)
    {
        i++;
    }
    if(i != 10)
    {
        return 0;
    }

    int j=0;
    while(str2[j] != 0)
    {
        if(!(str2[j]>='0' && str2[j]<='9'))
        {
            return 0;
        }
        j++;
    }
    return 1;
}

int validate_email(char *str3)
{
    if(str3[0]>='0' && str3[0]<='9')
    {
        return 0;
    }
    int i=0;
    int found=0;
    while(str3[i] != 0)
    {
        if(str3[i]=='@')
        {
            found=1;
        }
        if(!(str3[i]>=65 && str3[i]<=90 ||
            str3[i]>=97 && str3[i]<=122 ||
            str3[i]>=47 && str3[i]<=58 ||
             str3[i]=='@' || str3[i]=='.'))
        {
            return 0;
        }
        i++;
    }
    if(found==0)
    {
        return 0;
    }
    if(i < 4)
    {
        return 0;
    }

    if(str3[i-4] != '.' || str3[i-3] != 'c' || str3[i-2] != 'o' || str3[i-1] != 'm')
    {
        return 0;
    }
    return 1;
}

int phone_exists(AddressBook *addressBook, char *phone)
{
    int i;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 1;
        }
    }

    return 0;
}


int email_exists(AddressBook *addressBook, char *email)
{
    int i;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void pressEnterToContinue()
{
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress Book is full. Cannot add more contacts.\n");
        pressEnterToContinue();
        return;
    }

    system("clear");
    
    printf("\n============================================================\n");
    printf("                    CREATE CONTACT\n");
    printf("============================================================\n\n");

    char str1[30], str2[11], str3[30];
    int res1,res2,res3;

    do
    {
        printf("Enter Name  : ");
        scanf(" %[^\n]", str1);

        res1 = validate_name(str1);
        if(res1==0)
        {
            printf("Invalid name please use only uppercase,lowercase,space,dot...\n");
        }

    }while(res1 == 0); // 0 means invalid
    
    do
    {
        printf("Enter Phone : ");
        scanf("%s", str2);
        
        res2 = validate_number(str2);
        if(res2 == 0)
        {
            printf("Invalid phone number. Please enter 10 digits only...\n");
        }
        else if(phone_exists(addressBook, str2))
        {
            printf("Phone number already exists. Please enter another number.\n");
            res2 = 0;
        }
    }while(res2 == 0);
    
    do
    {
        printf("Enter Email : ");
        scanf("%s", str3);
        
        res3 = validate_email(str3);
        
        if(res3 == 0)
        {
            printf("Invalid Email. Please enter a valid email...\n");
        }
        else if(email_exists(addressBook, str3))
        {
            printf("Email already exists. Please enter another email.\n");
            res3 = 0;
        }
    }while(res3 == 0);


    int ind = addressBook->contactCount;
    strcpy(addressBook->contacts[ind].name, str1);
    strcpy(addressBook->contacts[ind].phone, str2);
    strcpy(addressBook->contacts[ind].email, str3);
    
    addressBook->contactCount++;
    
    printf("\n------------------------------------------------------------\n");
    printf("           Contact created successfully!\n");
    printf("------------------------------------------------------------\n");

    pressEnterToContinue();

}

int startsWithIgnoreCase(char *input, char *name)
{
    int i = 0;

    while(input[i] != '\0')
    {
        if(tolower(input[i]) != tolower(name[i]))
        {
            return 0;
        }

        i++;
    }

    return 1;
}

int search_by_name(AddressBook *addressBook)
{
    char name[30];
    int i;
    int count = 0;
    int choice;

    printf("Enter name: ");
    scanf(" %[^\n]", name);

    printf("\n------------------------------------------------------------\n");
    printf("                    MATCHING CONTACTS\n");
    printf("------------------------------------------------------------\n");
    printf("%-5s %-20s %-12s %s\n",
           "No.", "Name", "Phone", "Email");
    printf("------------------------------------------------------------\n");

    // Display all matching contacts
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(startsWithIgnoreCase(name, addressBook->contacts[i].name))
        {
            count++;

            printf("%-5d %-20s %-12s %s\n",
                   count,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }
    }

    if(count == 0)
    {
        printf("\nNo contact found.\n");
        return -1;
    }

    printf("------------------------------------------------------------\n");

    printf("\nEnter serial number to select contact: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > count)
    {
        printf("Invalid serial number\n");
        return -1;
    }
    
    count = 0;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(startsWithIgnoreCase(name, addressBook->contacts[i].name))
        {
            count++;

            if(count == choice)
            {
                printf("\n------------------------------------------------------------\n");
                printf("                    SELECTED CONTACT\n");
                printf("------------------------------------------------------------\n");

                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);

                printf("------------------------------------------------------------\n");

                return i;
            }
        }
    }

    return -1;
}
int search_by_phone(AddressBook *addressBook,char *phone)
{
    int i;
    for(i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("\n------------------------------------------------------------\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("------------------------------------------------------------\n");
            return i;
        }
    }
    printf("No contacts found\n");
    return -1;
}

int search_by_email(AddressBook *addressBook,char *email)
{
    int i;
    for(i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            printf("\n------------------------------------------------------------\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            printf("------------------------------------------------------------\n");
            return i;
        }
    }
    printf("No contacts found\n");
    return -1;
}


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    // print promt

    system("clear");
    
    printf("\n============================================================\n");
    printf("                    SEARCH CONTACT\n");
    printf("============================================================\n\n");

    int choice;
    char phone[11];
    char email[30];
    
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Back\n");
    
    printf("\n------------------------------------------------------------\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            pressEnterToContinue();
            break;
        case 2:
            printf("Enter phone number:\n");
            scanf("%s",phone);
            search_by_phone(addressBook,phone);
            pressEnterToContinue();
            break;
        case 3:
            printf("Enter Email:\n");
            scanf("%s",email);
            search_by_email(addressBook,email);
            pressEnterToContinue();
            break;
        case 4:
            return;
        default:
            printf("Invalid choice");
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    system("clear");
    
    printf("\n============================================================\n");
    printf("                     EDIT CONTACT\n");
    printf("============================================================\n\n");

    int choice;
    int ind;
    char phone[11];
    char email[30];

    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Back\n");
    
    printf("\n------------------------------------------------------------\n");
    printf("Enter your choice: ");
    
    scanf("%d",&choice); 
    
    if(choice < 1 || choice > 4)
    {
        printf("Invalid choice\n");
        return;
    }

    switch(choice)
    {
        case 1:
        ind = search_by_name(addressBook);
        break;

        case 2:
        printf("Enter phone number: ");
        scanf("%s", phone);
        ind = search_by_phone(addressBook,phone);
        break;

        case 3:
        printf("Enter email: ");
        scanf("%s", email);
        ind = search_by_email(addressBook,email);
        break;

        case 4:
        return;
    }
    if(ind == -1)
    {
        return;
    }

    int edit;

    printf("\n------------------------------------------------------------\n");
    printf("                    WHAT TO EDIT?\n");
    printf("------------------------------------------------------------\n");
    
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    
    printf("\n------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &edit);

    if(edit < 1 || edit > 3)
    {
        printf("Invalid choice\n");
        return;
    }

    switch(edit)
    {
        case 1:
        {
            char new_name[100];
            
            do
            {
                printf("\nEnter New Name : ");
                scanf(" %[^\n]", new_name);
                
                if(validate_name(new_name) == 0)
                {
                    printf("Invalid name. Please use alphabets, space and dot only.\n");
                }
            }while(validate_name(new_name) == 0);

            strcpy(addressBook->contacts[ind].name, new_name);
            
            printf("\n------------------------------------------------------------\n");
            printf("           New name edited successfully!\n");
            printf("------------------------------------------------------------\n");
            
            pressEnterToContinue();
            break;
        }

        case 2:
        {
            char new_phone[11];
            
            do
            {
                printf("\nEnter New Name : ");
                scanf("%s", new_phone);
                
                if(validate_number(new_phone) == 0)
                {
                    printf("Invalid phone number. Please enter 10 digits only...\n");
                }
                else if(phone_exists(addressBook, new_phone))
                {
                    if(strcmp(addressBook->contacts[ind].phone, new_phone) != 0)
                    {
                        printf("Phone number already exists. Please enter another number.\n");
                        continue;
                    }
                }
                if(validate_number(new_phone))
                {
                    strcpy(addressBook->contacts[ind].phone, new_phone);
                    
                    printf("\n------------------------------------------------------------\n");
                    printf("           New phone number edited successfully!\n");
                    printf("------------------------------------------------------------\n");
                    
                    pressEnterToContinue();
                    break;
                }
            }while(1);
            break;
        }

        case 3:
        {
            char new_email[100];
            
            do
            {
                printf("\nEnter New Email : ");
                scanf("%s", new_email);
                
                if(validate_email(new_email) == 0)
                {
                    printf("Invalid Email. Please enter a valid email...\n");
                }
                else if(email_exists(addressBook, new_email))
                {
                    if(strcmp(addressBook->contacts[ind].email, new_email) != 0)
                    {
                        printf("Email already exists. Please enter another email.\n");
                        continue;
                    }
                }
                if(validate_email(new_email))
                {
                    strcpy(addressBook->contacts[ind].email, new_email);
                    
                    printf("\n------------------------------------------------------------\n");
                    printf("           New email edited successfully!\n");
                    printf("------------------------------------------------------------\n");
                    
                    pressEnterToContinue();
                    break;
                }
            }while(1);
            break;
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    system("clear");
    
    printf("\n============================================================\n");
    printf("                    DELETE CONTACT\n");
    printf("============================================================\n\n");

    int choice;
    int ind;

    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Back\n");
    
    printf("\n------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
        {
            ind = search_by_name(addressBook);
            break;
        }

        case 2:
        {
            char phone[11];
            printf("Enter phone number: ");
            scanf("%s", phone);
            ind = search_by_phone(addressBook, phone);
            break;
        }

        case 3:
        {
            char email[30];
            printf("Enter email: ");
            scanf("%s", email);
            
            ind = search_by_email(addressBook, email);
            break;
        }
        case 4:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            return;
        }
    }
        if(ind == -1)
        {
            return;
        }
        char confirm;

        printf("\n------------------------------------------------------------\n");
        printf("Are you sure you want to delete this contact? (y/n): ");
        scanf(" %c", &confirm);

        if(confirm == 'n' || confirm == 'N')
        {
        printf("\n------------------------------------------------------------\n");
        printf("              Deletion cancelled.\n");
        printf("------------------------------------------------------------\n");
        
        pressEnterToContinue();
        return;
        }
        else if(confirm != 'y' && confirm != 'Y')
        {
        printf("\n------------------------------------------------------------\n");
        printf("       Invalid choice. Please enter y or n.\n");
        printf("------------------------------------------------------------\n");

        pressEnterToContinue();
        return;
        }

        int i;
        for(i=ind; i<addressBook->contactCount-1; i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf("\n------------------------------------------------------------\n");
        printf("           Contact deleted successfully!\n");
        printf("------------------------------------------------------------\n");

        pressEnterToContinue();
}
