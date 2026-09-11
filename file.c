// Include required header files

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

// Save all contacts to a CSV file

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;

    // Check whether there are any contacts to save
    if(addressBook->contactCount == 0)
    {
        printf("No contacts are saved\n");
        return;
    }

    // Open the contacts file in write mode
    fp = fopen("contacts.csv", "w");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    // Store the total number of contacts in the file
    fprintf(fp, "#%d\n", addressBook->contactCount);

    // Write each contact's details to the file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close the file after saving
    fclose(fp);

    printf("Contacts saved successfully\n");
}


// Load contacts from CSV file

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
    int count;

    // Open the contacts file in read mode
    fp = fopen("contacts.csv", "r");

    if(fp == NULL)
    {
        return;
    }

    // Read the total number of contacts
    fscanf(fp, "#%d\n", &count);

    // Reset contact count before loading
    addressBook->contactCount = 0;

    // Read contacts from the file
    while(addressBook->contactCount < count &&
      fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
             addressBook->contacts[addressBook->contactCount].name,
             addressBook->contacts[addressBook->contactCount].phone,
             addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    // Close the file
    fclose(fp);
}

