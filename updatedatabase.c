#include "main.h"

int update_database(main_node *headM[], char *filename)
{
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Invalid file name\n");
        return FAILURE;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Could not open backup file %s\n", filename);
        return FAILURE;
    }

    // Clear existing database before updating
    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = headM[i];
        while (mtemp)
        {
            sub_node *stemp = mtemp->sublink;
            while (stemp)
            {
                sub_node *sdel = stemp;
                stemp = stemp->next_link;
                free(sdel);
            }
            main_node *mdel = mtemp;
            mtemp = mtemp->next_link;
            free(mdel);
        }
        headM[i] = NULL;
    }

    int index, file_count;
    char word[100];
    char file[20];
    int wcount;

    while (fscanf(fp, "#%d;%d;%99[^;];", &index, &file_count, word) == 3)
    {
        // Create main node
        main_node *mnew = malloc(sizeof(main_node));
        strcpy(mnew->word, word);
        mnew->file_count = file_count;
        mnew->sublink = NULL;
        mnew->next_link = NULL;

        // Read subnodes
        sub_node *slast = NULL;
        for (int i = 0; i < file_count; i++)
        {
            if (fscanf(fp, "%19[^;];%d;", file, &wcount) != 2)
                break;

            sub_node *snew = malloc(sizeof(sub_node));
            strcpy(snew->filename, file);
            snew->word_count = wcount;
            snew->next_link = NULL;

            if (slast == NULL)
                mnew->sublink = snew;
            else
                slast->next_link = snew;

            slast = snew;
        }

        // Skip ending '#'
        fscanf(fp, " #");

        // Insert into hash table
        if (headM[index] == NULL)
        {
            headM[index] = mnew;
        }
        else
        {
            main_node *temp = headM[index];
            while (temp->next_link)
                temp = temp->next_link;
            temp->next_link = mnew;
        }
    }

    fclose(fp);
    printf("Database updated from file: %s\n", filename);
    return SUCCESS;
}
