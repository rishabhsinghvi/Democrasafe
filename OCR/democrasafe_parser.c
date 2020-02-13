#include "democrasafe_parser.h"

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef enum
{
    pc_key, pc_value
} parse_context;

void insert_node(parsed_node** head, parsed_node* node)
{
    if(*head==NULL)
    {
        *head = node;
    }
    else
    {
        node->_next = *head;
        *head = node;
    }
}

int parse_line(parsed_node** head, char* line, size_t length)
{

    if(line == NULL || line[0]=='\0')
        return -1;
    
    parse_context p_context = pc_key; 
    //int w_bool = 0; // keeps track of whether we're currently "in" word, 1 means we're in word
    char temp[MAX_LENGTH];
    memset(temp, 0, MAX_LENGTH);
    size_t count = 0;

    parsed_node* node = (parsed_node*)malloc(sizeof(parsed_node));

    for(size_t i = 0; i < length; i++)
    {
        if(line[i] == ':' && p_context == pc_key) // if we're currently parsing key and get ':' 
        {
            if(temp[0]=='\0') // if key is empty, invalid input
            {  
                free(node);
                return -1;
            }
            
            temp[count] = '\0';
            strcpy(node->_key, trim_whitespace(temp)); // copy from temp array to node
            memset(temp, 0, MAX_LENGTH);// reset temp array
            count = 0;
            p_context = pc_value;
        }
        else
        {
            temp[count++] = line[i];
        }
        
    }
    // Finally, we copy from temp array to node for value
    if(p_context == pc_key) // Haven't encountered : yet, something is wrong
    {  
        free(node);
        return -1;
    }
    
    strcpy(node->_value, trim_whitespace(temp));

    insert_node(head, node);

    return 0;
}

int parse_text(parsed_node** head, char* text, size_t length)
{
    if(text == NULL || text[0] == '\0')
        return -1;
    
    
    char *tok = text;
    while((tok = strtok(tok, "\n")) != NULL)
    {
        parse_line(head, tok, strlen(tok));
        tok = NULL;
    }

    return 0;
}


void clean_up(parsed_node** head)
{
    parsed_node* cur = *head;

    while(cur != NULL)
    {
        parsed_node* ptr = cur;
        cur = cur->_next;
        free(ptr);
    }
}

int print_nodes(parsed_node** head)
{
    if(*head == NULL)
        return -1;

    parsed_node* cur = *head;

    while(cur != NULL)
    {
        printf("%s: %s\n", cur->_key, cur->_value);
        cur = cur->_next;
    }
    return 0;
}

char* trim_whitespace(char* str)
{
    if(str == NULL)
        return str;

    char *end;
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

  // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}