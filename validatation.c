#include "main.h"

int check_main_node_files_validate(main_node *main_head[], file_node **fhead)
{
    file_node **currF = fhead;
    while (*currF != NULL)
    {
        int found = 0;
        for (int i = 0; i < 27 && !found; i++)
        {
            main_node *mtemp = main_head[i];
            while (mtemp != NULL && !found)
            {
                sub_node *stemp = mtemp->sublink;
                while (stemp != NULL)
                {
                    if (strcmp(stemp->filename, (*currF)->file_name) == 0)
                    {
                        found = 1;
                        break;
                    }
                    stemp = stemp->next_link;
                }
                mtemp = mtemp->next_link;
            }
        }

        if (found)
        {
            // Remove from file list
            file_node *remove_node = *currF;
            *currF = (*currF)->link;
            free(remove_node);
        }
        else
        {
            currF = &(*currF)->link;
        }
    }

    // If no files left in headF, all were already in DB
    return (*fhead == NULL) ? SUCCESS : FAILURE;
}


int checking_main_node_duplicate(char **file, main_node *main_head[])
{
    for (int i = 0; i < 27; i++) // loop through all alphabet buckets
    {
        main_node *mtemp = main_head[i];
        if (mtemp == NULL)
        {
            continue;
        }
        while (mtemp != NULL)
        {

            if (mtemp->file_count == 1)
            {
                for (int j = 0; file[j] != NULL; j++)
                {
                    if (strcmp(mtemp->sublink->filename, file[j]) == 0)
                    {
                        return SUCCESS; // duplicate found
                    }
                }
            }
            if (mtemp->file_count > 1)
            {
                sub_node *stemp = mtemp->sublink;
                while (stemp != NULL)
                {
                    for (int j = 0; file[j] != NULL; j++)
                    {
                        if (strcmp(stemp->filename, file[j]) == 0)
                        {
                            return SUCCESS; // duplicate found
                        }
                    }
                    stemp = stemp->next_link;
                }
            }
            mtemp = mtemp->next_link;
        }
    }
    return FAILURE; // no duplicates found
}

int validate_file_argument(file_node **head, char **files)
{
    int i = 0;
    FILE *fp = NULL;
    for (i = 0; files[i] != NULL; i++)
    {
        if (strstr(files[i], ".txt") == NULL)
        {
            printf("Error : File %s is not a text file\n", files[i]);
            continue;
        }

        for (int j = i + 1; files[j] != NULL; j++)
        {
            if (strcmp(files[i], files[j]) == 0)
            {
                printf("Error : File %s is repeated\n", files[i]);
                continue;
            }
        }

        fp = fopen(files[i], "r");
        if (fp == NULL)
        {
            printf("Error : File %s not found\n", files[i]);
        }
        else
        {
            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);
            rewind(fp);
            if (size == 0)
            {
                printf("Error : File %s is empty\n", files[i]);
            }
            else
            {
                file_node *new = malloc(sizeof(file_node));
                if (new == NULL)
                {
                    printf("Error : Memory allocation failed\n");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(new->file_name, files[i]);
                new->link = NULL;
                if (*head == NULL)
                {
                    *head = new;
                    //  new->link = *head;
                }
                else
                {
                    file_node *temp = *head;
                    while (temp->link != NULL)
                    {
                        temp = temp->link;
                    }
                    temp->link = new;
                }
            }
            fclose(fp);
        }
    }
    return SUCCESS;
}