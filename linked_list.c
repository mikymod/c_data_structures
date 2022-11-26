#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list_node
{
    struct list_node *next;
};

struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

void string_item_remove(struct list_node **head, struct string_item *item)
{
    struct list_node *current = *head;
    struct list_node *previous = NULL;

    while (current)
    {
        struct string_item *current_item = (struct string_item *)current;
        if (strcmp(current_item->string, item->string) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            break;
        }

        previous = current;
        current = current->next;
    }
}

int main()
{
    struct string_item *my_linked_list = NULL;
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Last Item of the Linked List"));

    string_item_remove((struct list_node **)&my_linked_list, string_item_new("Last Item of the Linked List"));

    struct string_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}