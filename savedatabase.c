#include "main.h"

int save_database(main_node *head[], char *filename)
{
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Invalid file name\n");
        return FAILURE;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error in opening file\n");
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        main_node *temp = head[i];
        while (temp != NULL)
        {
           
            fprintf(fp, "#%d;%d;%s;", i, temp->file_count, temp->word);
           
            sub_node *temp1 = temp->sublink;
            while (temp1 != NULL)
            {
                fprintf(fp, "%s;%d;", temp1->filename, temp1->word_count);
                temp1 = temp1->next_link;
            }

          
            fprintf(fp, "#\n");

            temp = temp->next_link;
        }
    }

    fclose(fp);
    return SUCCESS;
}
