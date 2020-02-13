#include "democrasafe_parser.h"

#include<string.h>
#include<stdio.h>

int main()
{
    char text[] = "ID: x355sYE\nVote 1: ABC\nVote 2:   XYZ";
    parsed_node* head = NULL;
    parse_text(&head, text, strlen(text));

    if(print_nodes(&head) == -1)
    {
        printf("No nodes in list\n");
    }

}