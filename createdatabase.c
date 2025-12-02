#include "main.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Remove leading/trailing non-alphabetic characters */
void clean_word(char *word)
{
    int start = 0;
    int end = strlen(word) - 1;

    // Trim start
    while (start <= end && !isalpha((unsigned char)word[start]))
        start++;

    // Trim end
    while (end >= start && !isalpha((unsigned char)word[end]))
        end--;

    // Shift and null terminate
    int j = 0;
    for (int i = start; i <= end; i++)
        word[j++] = word[i];
    word[j] = '\0';
}

/* Convert word to lowercase */
void to_lower_str(char *word)
{
    for (int i = 0; word[i]; i++)
        word[i] = tolower((unsigned char)word[i]);
}

/* Check if a file is already present in the database */
int file_already_in_db(main_node *headM[], const char *filename)
{
    for (int i = 0; i < 26; i++)
    {
        main_node *tempM = headM[i];
        while (tempM)
        {
            sub_node *tempS = tempM->sublink;
            while (tempS)
            {
                if (strcmp(tempS->filename, filename) == 0)
                    return 1; // Found file in DB
                tempS = tempS->next_link;
            }
            tempM = tempM->next_link;
        }
    }
    return 0; // File not found in DB
}

int create_database(main_node *headM[], file_node *headF)
{
    if (!headF)
        return FAILURE;

    file_node *tempF = headF;
    while (tempF)
    {
        // Skip if file already processed
        if (file_already_in_db(headM, tempF->file_name))
        {
            tempF = tempF->link;
            continue;
        }

        FILE *fp = fopen(tempF->file_name, "r");
        if (!fp)
        {
            printf("Error opening file: %s\n", tempF->file_name);
            return FAILURE;
        }

        char str[100];
        while (fscanf(fp, "%99s", str) != EOF)
        {
            clean_word(str); // Remove punctuation
            if (strlen(str) == 0) // Skip empty after cleaning
                continue;

            to_lower_str(str); // Convert to lowercase

            int index = tolower(str[0]) - 'a';
            if (index < 0 || index >= 26)
                continue;

            main_node *currM = headM[index];
            main_node *prevM = NULL;
            int word_found = 0;

            while (currM)
            {
                if (strcmp(currM->word, str) == 0)
                {
                    word_found = 1;

                    // Check sublist for file entry
                    sub_node *currS = currM->sublink;
                    sub_node *prevS = NULL;
                    int file_found = 0;

                    while (currS)
                    {
                        if (strcmp(currS->filename, tempF->file_name) == 0)
                        {
                            currS->word_count++;
                            file_found = 1;
                            break;
                        }
                        prevS = currS;
                        currS = currS->next_link;
                    }

                    if (!file_found)
                    {
                        sub_node *newS = malloc(sizeof(sub_node));
                        strcpy(newS->filename, tempF->file_name);
                        newS->word_count = 1;
                        newS->next_link = NULL;
                        prevS->next_link = newS;
                        currM->file_count++;
                    }
                    break;
                }
                prevM = currM;
                currM = currM->next_link;
            }

            // Add new word if not found
            if (!word_found)
            {
                main_node *newM = malloc(sizeof(main_node));
                strcpy(newM->word, str);
                newM->file_count = 1;
                newM->next_link = NULL;

                sub_node *newS = malloc(sizeof(sub_node));
                strcpy(newS->filename, tempF->file_name);
                newS->word_count = 1;
                newS->next_link = NULL;

                newM->sublink = newS;

                if (!headM[index])
                    headM[index] = newM;
                else
                    prevM->next_link = newM;
            }
        }

        fclose(fp);
        tempF = tempF->link;
    }

    return SUCCESS;
}
