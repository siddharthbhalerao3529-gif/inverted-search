#include "main.h"

int search_database(main_node *headM[], char *word)
{
    int index = word[0] - 'a';
    main_node *temp = headM[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) != 0)
        {
            temp = temp->next_link;
        }
        else
        {
            printf("========================================\n");
            printf("Word Found: \"%s\"\n", temp->word);
            printf("Appears in %d file%s:\n", temp->file_count, (temp->file_count > 1) ? "s" : "");
            printf("----------------------------------------\n");

            sub_node *temp1 = temp->sublink;
            while (temp1 != NULL)
            {
                printf("File: %-20s | Occurrences: %d\n", temp1->filename, temp1->word_count);
                temp1 = temp1->next_link;
            }
            printf("========================================\n");

            return SUCCESS;
        }
    }
    printf("Word \"%s\" not found in the database.\n", word);
    return FAILURE;
}
