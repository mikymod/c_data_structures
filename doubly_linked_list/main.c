#include <stddef.h> // required for NULL
#include <time.h>
#include "doubly_linked_list.h"

struct string_item
{
    struct dlist_node node;
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
    srand(time(NULL));

    struct string_item *my_linked_list = NULL;

    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Hello World")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test001")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Test002")));
    list_append(PPCAST(&my_linked_list), PCAST(string_item_new("Last Item of the Linked List")));
    list_string_print(PPCAST(&my_linked_list));

    list_pop(PPCAST(&my_linked_list));
    list_pop(PPCAST(&my_linked_list));
    list_pop(PPCAST(&my_linked_list));
    list_pop(PPCAST(&my_linked_list));
    list_string_print(PPCAST(&my_linked_list));

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

    list_shuffle(PPCAST(&my_linked_list));
    list_string_print(PPCAST(&my_linked_list));

    return 0;
}
