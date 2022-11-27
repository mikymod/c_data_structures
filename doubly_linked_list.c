#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>

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
    if (item == NULL)
    {
        printf("Item is NULL");
        return *head;
    }

    if (item == *head)
    {
        *head = item->next;
        (*head)->prev = NULL;
    }
    else if (item->next == NULL)
    {
        struct list_node *previous = item->prev;
        previous->next = NULL;
    }
    else
    {
        struct list_node *previous = item->prev;
        struct list_node *next = item->next;
        previous->next = next;
        next->prev = previous;
    }

    free(item);
    return *head;
}

void list_insert_after(struct list_node *item, struct list_node *after)
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

void list_insert_before(struct list_node **head, struct list_node *item, struct list_node *before)
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

struct list_node *list_shuffle(struct list_node **head)
{
    // TODO
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

void list_string_print(struct string_item **head)
{
    struct string_item *string_item = *head;
    while (string_item)
    {
        printf("value: %s, curr: %p, prev: %p, next: %p\n", string_item->string, string_item, string_item->node.prev, string_item->node.next);
        string_item = (struct string_item *)string_item->node.next;
    }
    printf("---------\n");
}

int main(int argc, char **argv)
{
    struct string_item *my_linked_list = NULL;

    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Hello World")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test001")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test002")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Last Item of the Linked List")));
    list_string_print(PPCAST(&my_linked_list));

    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 2));
    list_string_print(PPCAST(&my_linked_list));

    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 0));
    list_string_print(PPCAST(&my_linked_list));

    list_remove(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 1));
    list_string_print(PPCAST(&my_linked_list));

    list_insert_after(list_get_node(PPCAST(&my_linked_list), 0), PCAST(string_item_new("After001")));
    list_string_print(PPCAST(&my_linked_list));

    list_insert_after(list_get_node(PPCAST(&my_linked_list), 0), PCAST(string_item_new("After002")));
    list_string_print(PPCAST(&my_linked_list));

    list_insert_before(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 0), PCAST(string_item_new("Before001")));
    list_string_print(PPCAST(&my_linked_list));

    list_insert_before(PPCAST(&my_linked_list), list_get_node(PPCAST(&my_linked_list), 2), PCAST(string_item_new("Before002")));
    list_string_print(PPCAST(&my_linked_list));

    return 0;
}
