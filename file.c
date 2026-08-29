#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s|%s|%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.txt", "r");

    if(fp == NULL)
    {
        return;
    }

    while(fscanf(fp, " %49[^|]|%19[^|]|%49[^\n]",
                 addressBook->contacts[addressBook->contactCount].name,
                 addressBook->contacts[addressBook->contactCount].phone,
                 addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}