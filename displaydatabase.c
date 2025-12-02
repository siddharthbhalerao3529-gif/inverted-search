#include "main.h"

void display_database(main_node *headM[], file_node *headF)
{
    int check = 0;
    printf("==========================================================================================\n");
    printf("%-7s %-15s %-10s %s\n", "Index", "Word", "FileCount", "Files (No: Name, Count)");
    printf("==========================================================================================\n");

    for (int i = 0; i < 27; i++)
    {
        main_node *temp = headM[i];
        if (temp == NULL)
            continue;

        while (temp != NULL)
        {
            printf("%-7d %-15s %-10d ", i, temp->word, temp->file_count);

            sub_node *tempS = temp->sublink;
            int first = 1;
            while (tempS != NULL)
            {
                // Find file number by searching file_node list
                int file_no = -1;
                int index = 1;
                file_node *tempF = headF;
                while (tempF != NULL)
                {
                    if (strcmp(tempF->file_name, tempS->filename) == 0)
                    {
                        file_no = index;
                        break;
                    }
                    tempF = tempF->link;
                    index++;
                }

                if (!first)
                    printf(" | ");
                printf("File : %s ( %d ) ", tempS->filename, tempS->word_count);

                first = 0;
                tempS = tempS->next_link;
                check = 1;
            }
            printf("\n");
            temp = temp->next_link;
        }
    }

    if (!check)
    {
        printf("Database is empty\n");
    }
    printf("==========================================================================================\n");
}
