#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "doubly_linked_list.h"

struct dlist_node *list_get_tail(struct dlist_node **head)
{
    struct dlist_node *current_node = *head;
    struct dlist_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct dlist_node *list_get_node(struct dlist_node **head, const unsigned int index)
{
    // FIXME: check bounds
    struct dlist_node *current = *head;

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

struct dlist_node *list_append(struct dlist_node **head, struct dlist_node *item)
{
    struct dlist_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct dlist_node *list_pop(struct dlist_node **head)
{
    struct dlist_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }

    if ((*head)->next == NULL)
    {
        *head = NULL;
        return current_head;
    }

    *head = (*head)->next;
    current_head->next = NULL;
    (*head)->prev = NULL;
    return current_head;
}

struct dlist_node *list_remove(struct dlist_node **head, struct dlist_node *item)
{
    if (item == NULL)
    {
        printf("Remove: Item is NULL");
        return NULL;
    }

    if (item == *head)
    {
        *head = item->next;
        (*head)->prev = NULL;
    }
    else if (item->next == NULL)
    {
        struct dlist_node *previous = item->prev;
        previous->next = NULL;
    }
    else
    {
        struct dlist_node *previous = item->prev;
        struct dlist_node *next = item->next;
        previous->next = next;
        next->prev = previous;
    }

    return item;
}

void list_insert_after(struct dlist_node *item, struct dlist_node *after)
{
    if (item == NULL)
    {
        printf("Item is NULL");
        return;
    }

    after->next = item->next;
    after->prev = item;

    if (item->next != NULL)
    {
        item->next->prev = after;
    }

    item->next = after;
}

void list_insert_before(struct dlist_node **head, struct dlist_node *item, struct dlist_node *before)
{
    if (item == NULL)
    {
        printf("Item is NULL");
        return;
    }

    if (item == *head)
    {
        *head = before;
        item->prev = before;
        before->next = item;
        before->prev = NULL;
    }
    else
    {
        before->prev = item->prev;
        before->next = item;
        item->prev->next = before;
        item->prev = before;
    }
}

size_t list_size(struct dlist_node **head)
{
    struct dlist_node *item = *head;

    if (item == NULL)
    {
        return 0;
    }

    size_t size = 1;
    while (item->next)
    {
        size++;
        item = item->next;
    }

    return size;
}

void list_shuffle(struct dlist_node **head)
{
    int size = list_size(head);

    // TODO: make list_copy(ptr)
    struct dlist_node **copy = malloc(size * sizeof(struct dlist_node));
    memcpy(copy, head, size * sizeof(struct dlist_node));

    // Generates new order
    int *index_array = malloc(size * sizeof(int));
    memset(index_array, -1, size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        int index_unique = 0;
        int index = 0;
        do
        {
            index = rand() % size;
            index_unique = 1;
            for (int j = 0; j < size; j++)
            {
                if (index_array[j] == index)
                {
                    index_unique = 0;
                }
            }
        } while (!index_unique);

        index_array[i] = index;
        printf("index: %d\n", index_array[i]);
    }

    // Stores pointers in array
    for (int i = 0; i < size; i++)
    {
        head[i] = list_get_node(copy, index_array[i]);
    }

    // Restores links
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            head[i]->prev = NULL;
            head[i]->next = head[i + 1];
        }
        else if (i == size - 1)
        {
            head[i]->prev = head[i - 1];
            head[i]->next = NULL;
        }
        else
        {
            head[i]->prev = head[i - 1];
            head[i]->next = head[i + 1];
        }
    }

    free(copy);
    free(index_array);
}