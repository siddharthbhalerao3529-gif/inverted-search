/*
name - siddharth bhalerao
date - 13-8-25
description - Creates an inverted index from a list of files by reading each word, normalizing it to lowercase, 
              and removing punctuation. Uses 26 buckets (A–Z) based on the first letter to store words in main nodes.
              Each main node links to sub nodes that store file names and occurrence counts.
              Skips entire files already processed to avoid duplication.
              Ensures each word appears only once per bucket, updating counts if repeated.
*/
#include "main.h"

int main(int argc, char *argv[])
{
	/* Define the main function here */
	if (argc == 1)
	{
		printf("invalid arguments\n");
		return 1;
	}

	file_node *head = NULL;
	if (validate_file_argument(&head, argv + 1) == FAILURE) // example like file t1.txt t2.txt t3.txt validation
	{
		printf("invalid argument\n");
		return 1;
	}
	printf("file validation sussessfully completed\n");

	int choice = 0;
	main_node *main_head[27] = {NULL};
	while (1)
	{
		printf("Enter your choice for database operation \n");
		printf("1. Create Database\n");
		printf("2. Display Database\n");
		printf("3. Search Database\n");
		printf("4. Save Database\n");
		printf("5. Update Database\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (check_main_node_files_validate(main_head, &head) == SUCCESS)
			{
				printf("All files already present in database\n");
				break; // skip create_database()
			}

			if (head != NULL)
			{
				if (create_database(main_head, head) != SUCCESS)
				{
					printf("Database creation failed\n");
				}
				else
				{
					printf("Database created successfully\n");
				}
			}
			break;
		case 2:
			printf("Displaying Database\n");
			display_database(main_head, head);
			break;
		case 3:
			char word[20];
			printf("Enter the word to search: \n");
			scanf("%s", word);
			printf("Searching Database\n");
			if (search_database(main_head, word) != SUCCESS)
			{
				printf("word not found\n");
			}
			else
			{
				printf("word found\n");
			}

			break;
		case 4:
			char filename[20];
			printf("Enter the filename to save: \n");
			scanf(" %s", filename);
			if (save_database(main_head, filename) != SUCCESS)
			{
				printf("DATABASE saving failed\n");
			}
			else
			{
				printf("database saved SUCCESSfully in  %s\n", filename);
			}
			break;
		case 5:
			char file_name[20];
			printf("Updating Database\n");

			if (checking_main_node_duplicate(argv + 1, main_head) == SUCCESS)
			{
				printf("file already exist , cant load \n");
				break;
			}
			printf("Enter the filename to load: \n");
			scanf("%s", file_name);
			if (update_database(main_head, file_name) != SUCCESS)
			{
				printf("DATABASE updation failed\n");
			}
			else
			{
				printf("database updated SUCCESSfully\n");
			}
			break;
		case 6:
			printf("Exiting\n");
			return 1;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
	return 0;
}
