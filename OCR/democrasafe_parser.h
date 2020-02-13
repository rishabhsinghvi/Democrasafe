#ifndef _DEMOCRASAFE_PARSER_H
#define _DEMOCRASAFE_PARSER_H

#define MAX_LENGTH 30

#include <stddef.h>

struct parsed_node
{
    char _key[MAX_LENGTH];
    char _value[MAX_LENGTH];
    struct parsed_node* _next;
};

typedef struct parsed_node parsed_node;

void insert_node(parsed_node** head, parsed_node* node);

int parse_line(parsed_node** head, char* line, size_t length);

int parse_text(parsed_node** head, char* text, size_t length);

void clean_up(parsed_node** head);

int print_nodes(parsed_node** head);

char* trim_whitespace(char* ptr);

#endif