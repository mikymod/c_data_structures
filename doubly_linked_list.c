#include <stddef.h> // required for NULL
#include <stdlib.h>

#define PPCAST(x) (struct list_node **)(x)
#define PCAST(x) (struct list_node *)(x)

struct list_node
{
    struct list_node *prev;
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

struct list_node *list_get_node(struct list_node **head, const unsigned int index)
{
    // FIXME: check bounds
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
    item->prev = tail;
    item->next = NULL;
    return item;
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

void list_insert_after(struct list_node **head, struct list_node *item, struct list_node *after)
{
    if (item == NULL)
    {
        return;
    }

    struct list_node *curr_next = item->next;
    item->next = after;
    after->next = curr_next;
}

// struct list_node *list_insert_before(struct list_node **head, struct list_node *item, struct list_node *before)
// {
// }

// struct list_node *list_shuffle(struct list_node **head)
// {
// }

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

    list_insert_after(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 10), PCAST(string_item_new("Test003")));

    struct string_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}