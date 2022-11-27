#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PPCAST(x) (struct list_node **)(x)
#define PCAST(x) (struct list_node *)(x)

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

struct list_node *list_get_node(struct list_node **head, const unsigned int index)
{
    struct list_node *current = *head;

    int i = 0;
    while (current)
    {
        if (i == index)
        {
            return current;
        }

        current = current->next;
        i++;
    }

    return NULL;
}

struct list_node *list_remove(struct list_node **head, struct list_node *item)
{
    struct list_node *current = *head;
    struct list_node *previous = NULL;

    while (current)
    {
        if (current == item)
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
            return *head;
        }

        previous = current;
        current = current->next;
    }

    return NULL;
}

struct list_node *list_reverse(struct list_node **head)
{
    struct list_node *current = *head;
    struct list_node *next = NULL;
    struct list_node *prev = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
    return *head;
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

int main()
{
    struct string_item *my_linked_list = NULL;

    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Hello World")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test001")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test002")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Last Item of the Linked List")));

    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 2));
    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 1));
    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 0));

    list_reverse(PPCAST(&my_linked_list));

    struct string_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}