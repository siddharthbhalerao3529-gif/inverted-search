#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FAILURE 0
#define SUCCESS 1

typedef struct file_node
{
    char file_name[20];
    struct file_node *link;
} file_node;

typedef struct main_node
{
    int file_count;
    char word[100];
    struct sub_node *sublink;
    struct main_node *next_link;
}main_node;

typedef struct sub_node
{
    int word_count;
    char filename[20];
    struct sub_node*next_link;
}sub_node;

int validate_file_argument(file_node **head, char **files);
int create_database(main_node *headM[] , file_node *headF);
void display_database(main_node *headM[], file_node *headF);
int get_file_index(file_node *headF, const char *filename);
int search_database(main_node *headM[], char *word);
int save_database(main_node *headM[], char *filename);
int update_database(main_node *headM[], char *filename);
int checking_main_node_duplicate(char **file , main_node *main_head[]);
int check_main_node_files_validate(main_node *main_head[] , file_node **fhead);
int word_file_exists(main_node *main_head[], const char *word, const char *filename);


#endif